#include <wx/notebook.h>
#include "ArionFrame.h"
#include "AppId.h"
#include "DiskStatsPanel.h"
#include "Types.h"
#include "DiskVolumeInfoPanel.h"

using namespace std;

ArionFrame::ArionFrame() : wxFrame(nullptr, wxID_ANY, "Arion")
{
	this->disk = nullptr;

	this->SetMinClientSize(FromDIP(wxSize(640, 480)));
	this->InitMain();

	CreateStatusBar();
	SetStatusText("Arion Floppy Utilities");

	Bind(wxEVT_MENU, &ArionFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &ArionFrame::OnOpenFile, this, ID_OpenFile);
	Bind(wxEVT_MENU, &ArionFrame::OnAutoIdentification, this, ID_AutoIdentification);
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
	hbox->Add(this->stats, 1, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM, 5);	

	wxNotebook* mainPanel = new wxNotebook(panel, wxID_ANY);

	this->sectorInfoPage = new SectorInfoPanel(mainPanel, this->disk);
	mainPanel->AddPage(sectorInfoPage, "Sectors");

	volumeInfoPage = new DiskVolumeInfoPanel(mainPanel, nullptr);
	mainPanel->AddPage(volumeInfoPage, "Volume");

	wxPanel* filesPage = new wxPanel(mainPanel, wxID_ANY);
	mainPanel->AddPage(filesPage, "Files");

	hbox->Add(mainPanel, 5, wxEXPAND | wxTOP | wxRIGHT | wxBOTTOM, 5);
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
		int state = disk->LoadFromImd(fileName.ToStdString());
		if (state == 0)
		{
			DiskStatistics stats = disk->GetStatistics();
			this->stats->UpdateStats(&stats);
			this->sectorInfoPage->UpdateInfo(disk);
			this->IdentifyDisk();
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

void ArionFrame::IdentifyDisk()
{
	this->disk->SetType(Type_Unknown);
	this->disk->Identify();
	char type = this->disk->GetType();
	if (type == Type_IBM_Interchange)
	{
		this->interchange = new InterchangeDisk(*this->disk);
		this->volumeInfoPage->UpdateVolumeInfo(&this->interchange->GetVolume());
	}
	else
	{
		delete this->interchange;
		this->interchange = nullptr;
		this->volumeInfoPage->UpdateVolumeInfo(nullptr);
	}
}