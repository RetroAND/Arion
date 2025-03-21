#include <wx/notebook.h>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include "ArionFrame.h"
#include "AppId.h"
#include "DiskStatsPanel.h"
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include "DiskVolumeInfoPanel.h"

using namespace std;

ArionFrame::ArionFrame() : wxFrame(nullptr, wxID_ANY, "Arion")
{
	this->disk = nullptr;

	this->SetMinClientSize(FromDIP(wxSize(800, 600)));
	this->InitMain();

	CreateStatusBar();
	SetStatusText("Arion Floppy Utilities");

	Bind(wxEVT_MENU, &ArionFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &ArionFrame::OnOpenFile, this, ID_OpenFile);
	Bind(wxEVT_MENU, &ArionFrame::OnAutoIdentification, this, ID_AutoIdentification);
	Bind(wxEVT_COMBOBOX, &ArionFrame::OnHeadSelected, this, ID_HeadComboBox);
	Bind(wxEVT_COMBOBOX, &ArionFrame::OnCylinderSelected, this, ID_CylinderComboBox);
	Bind(wxEVT_COMBOBOX, &ArionFrame::OnSectorSelected, this, ID_SectorComboBox);
	Bind(wxEVT_LISTBOX, &ArionFrame::OnFileChosen, this, ID_DiskFileList);
	Bind(wxEVT_BUTTON, &ArionFrame::OnFileExport, this, ID_ExportAllFiles);

	Bind(wxEVT_MENU, &ArionFrame::OnCloseFile, this, ID_CloseFile);
}

void ArionFrame::InitMain()
{
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(ID_OpenFile, "&Open File");
	fileMenu->Append(ID_CloseFile, "&Close File");

	wxMenu* toolsMenu = new wxMenu();
	toolsMenu->Append(ID_AutoIdentification, "&Auto-identification");
	toolsMenu->Append(ID_ManualIdentification, "&Manual identification");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(toolsMenu, "&Tools");

	this->SetMenuBar(menuBar);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	this->stats = new DiskStatsPanel(panel, nullptr);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(this->stats);	

	wxNotebook* mainPanel = new wxNotebook(panel, wxID_ANY, wxPoint(0,0), wxSize(640, 480));

	this->sectorInfoPage = new SectorInfoPanel(mainPanel, this->disk);
	mainPanel->AddPage(sectorInfoPage, "Sectors");

	volumeInfoPage = new DiskVolumeInfoPanel(mainPanel, nullptr);
	mainPanel->AddPage(volumeInfoPage, "Volume");

	this->filePanel = new DiskFilePanel(mainPanel);
	mainPanel->AddPage(filePanel, "Files");

	hbox->Add(mainPanel, 0, wxEXPAND | wxRIGHT | wxBOTTOM, 5);

	panel->SetSizer(hbox);
	this->Centre();
}

void ArionFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void ArionFrame::OnOpenFile(wxCommandEvent& event)
{
	wxFileDialog* openFileDialog = new wxFileDialog(this);
	openFileDialog->SetWildcard("Floppy Images (*.imd)|*.imd");

	if (openFileDialog->ShowModal() == wxID_OK) {
		wxString fileName = openFileDialog->GetPath();
		this->disk = new Disk();
		try
		{
			int state = disk->LoadFromImd(fileName.ToStdString());
		
			if (state == 0)
			{
				DiskStatistics stats = disk->GetStatistics();
				this->stats->UpdateStats(&stats);
				this->sectorInfoPage->UpdateInfo(disk);
				Sector sector = this->disk->GetSector(CylinderHeadSector(this->sectorInfoPage->GetCylinder(), this->sectorInfoPage->GetHead(), this->sectorInfoPage->GetSector()));
				this->sectorInfoPage->hexPanel->UpdateSector(&sector);
				this->IdentifyDisk();
			}
		}
		catch (const exception exception)
		{
			cout << exception.what() << endl;
		}
	}
	delete openFileDialog;
}

void ArionFrame::OnCloseFile(wxCommandEvent& event)
{
	delete this->disk;
	delete this->interchange;
	this->disk = nullptr;
	this->stats->UpdateStats(nullptr);
	this->sectorInfoPage->UpdateInfo(nullptr);
	this->volumeInfoPage->UpdateVolumeInfo(nullptr);
	this->filePanel->UpdateFiles(nullptr);
}

void ArionFrame::OnAutoIdentification(wxCommandEvent& event)
{
	if (disk == nullptr)
	{
		this->ShowErrorDialog("ERROR", "An image MUST be loaded to invoke the identification routines.");
		return;
	}
	this->IdentifyDisk();
	cout << this->disk->GetTypeString() << endl;
}

void ArionFrame::ShowErrorDialog(string title, string text)
{
	wxMessageDialog* dialog = new wxMessageDialog(NULL,
		text, title, wxOK | wxICON_ERROR);
	dialog->ShowModal();
}

void ArionFrame::ShowConfirmationDialog(string title, string text)
{
	wxMessageDialog* dialog = new wxMessageDialog(NULL,
		text, title, wxOK | wxICON_INFORMATION);
	dialog->ShowModal();
}

void ArionFrame::IdentifyDisk()
{
	this->disk->SetType(Type_Unknown);
	this->disk->Identify();
	char type = this->disk->GetType();
	if (type == Type_IBM_Interchange)
	{
		this->interchange = new InterchangeDisk(*this->disk);
		this->volumeInfoPage->UpdateVolumeInfo(&this->interchange->GetVolume());
		this->filePanel->UpdateFiles(&this->interchange->GetFiles());
	}
	else
	{
		delete this->interchange;
		this->interchange = nullptr;
		this->volumeInfoPage->UpdateVolumeInfo(nullptr);
		this->filePanel->UpdateFiles(nullptr);
	}
}

void ArionFrame::OnHeadSelected(wxCommandEvent& event)
{
	this->sectorInfoPage->SetHead(this->sectorInfoPage->headComboBox->GetSelection());
	this->sectorInfoPage->GenerateTracks(this->disk->GetTracksByHead(this->sectorInfoPage->GetHead()).size());
	this->sectorInfoPage->GenerateSectors(this->disk->GetTrack(this->sectorInfoPage->GetCylinder(), this->sectorInfoPage->GetHead()).GetSectorNumber());
	Sector sector = this->disk->GetSector(CylinderHeadSector(this->sectorInfoPage->GetCylinder(), this->sectorInfoPage->GetHead(), this->sectorInfoPage->GetSector()));
	this->sectorInfoPage->hexPanel->UpdateSector(&sector);
}

void ArionFrame::OnCylinderSelected(wxCommandEvent& event)
{
	this->sectorInfoPage->SetCylinder(this->sectorInfoPage->cylinderComboBox->GetSelection());
	this->sectorInfoPage->GenerateSectors(this->disk->GetTrack(this->sectorInfoPage->GetCylinder(), this->sectorInfoPage->GetHead()).GetSectorNumber());
	Sector sector = this->disk->GetSector(CylinderHeadSector(this->sectorInfoPage->GetCylinder(), this->sectorInfoPage->GetHead(), this->sectorInfoPage->GetSector()));
	this->sectorInfoPage->hexPanel->UpdateSector(&sector);
}

void ArionFrame::OnSectorSelected(wxCommandEvent& event)
{
	this->sectorInfoPage->SetSector(this->sectorInfoPage->sectorComboBox->GetSelection());
	Sector sector = this->disk->GetSector(CylinderHeadSector(this->sectorInfoPage->GetCylinder(), this->sectorInfoPage->GetHead(), this->sectorInfoPage->GetSector()));
	this->sectorInfoPage->hexPanel->UpdateSector(&sector);
}

void ArionFrame::OnFileChosen(wxCommandEvent& event)
{
	this->filePanel->SelectFile(this->filePanel->fileList->GetSelection());
}

void ArionFrame::OnFileExport(wxCommandEvent& event)
{
	wxDirDialog selectFolderDialog = new wxDirDialog(this, "Choose export directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (selectFolderDialog.ShowModal()==wxID_OK)
	{
		vector<InterchangeFile> files = this->interchange->GetFiles();
		for (int file = 0; file < files.size(); file++)
		{
			files[file].SaveToFile(selectFolderDialog.GetPath().ToStdString());
		}
		this->ShowConfirmationDialog("Operation conducted successfully", "The files have been saved at the specified directory.");
	}
}