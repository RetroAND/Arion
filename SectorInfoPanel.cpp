#include <vector>
#include "SectorInfoPanel.h"
#include "AppId.h"

using namespace std;

SectorInfoPanel::SectorInfoPanel(wxWindow* parent, Disk* disk) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(270, 150))
{
	this->disk = disk;
	this->head = 0;
	this->cylinder = 0;
	this->sector = 0;

	this->nothingPanel = new wxPanel(this, wxID_ANY);
	wxStaticText* nothing = new wxStaticText(nothingPanel, wxID_ANY, wxT("Nothing to display"));
	wxBoxSizer* nothingSizer = new wxBoxSizer(wxVERTICAL);
	nothingSizer->Add(nothing);
	nothingPanel->SetSizer(nothingSizer);

	this->infoPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
	infoPanel->SetSizer(infoSizer);
	
	wxPanel* comboPanel = new wxPanel(infoPanel, wxID_ANY, wxPoint(0,0), wxSize(640,64));
	wxStaticText* headLabel = new wxStaticText(comboPanel, wxID_ANY, wxT("Head:"));
	this->headComboBox = new wxComboBox(comboPanel, ID_HeadComboBox);
	this->GenerateHeads(1);
	this->headComboBox->SetSelection(this->head);

	wxStaticText* cylinderLabel = new wxStaticText(comboPanel, wxID_ANY, wxT("Cylinder:"));
	this->cylinderComboBox = new wxComboBox(comboPanel, ID_CylinderComboBox);
	this->GenerateTracks(77);
	this->cylinderComboBox->SetSelection(this->cylinder);

	wxStaticText* sectorLabel = new wxStaticText(comboPanel, wxID_ANY, wxT("Sector:"));
	this->sectorComboBox = new wxComboBox(comboPanel, ID_SectorComboBox);
	this->GenerateSectors(26);
	this->sectorComboBox->SetSelection(this->sector);

	wxBoxSizer* comboSizer = new wxBoxSizer(wxHORIZONTAL);
	comboSizer->Add(headLabel);
	comboSizer->Add(this->headComboBox);
	comboSizer->Add(cylinderLabel);
	comboSizer->Add(this->cylinderComboBox);
	comboSizer->Add(sectorLabel);
	comboSizer->Add(this->sectorComboBox);

	comboPanel->SetSizer(comboSizer);

	this->hexPanel = new SectorHexPanel(infoPanel);
	infoSizer->Add(comboPanel, wxEXPAND | wxLEFT | wxRIGHT);
	infoSizer->Add(this->hexPanel);

	wxBoxSizer* pageSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(pageSizer);
	pageSizer->Add(nothingPanel, wxEXPAND | wxALL);
	pageSizer->Add(infoPanel, wxEXPAND | wxALL);


	this->UpdateInfo(this->disk);
}

void SectorInfoPanel::UpdateInfo(Disk* disk)
{
	this->disk = disk;
	if (this->disk == nullptr)
	{
		this->nothingPanel->Show();
		this->infoPanel->Hide();
	}
	else
	{
		this->GenerateHeads(disk->GetHeads());
		this->GenerateTracks(disk->GetTracksByHead(this->head).size());
		this->GenerateSectors(disk->GetTrack(this->cylinder, this->head).GetSectors().size());
		//update visor
		this->nothingPanel->Hide();
		this->infoPanel->Show();
	}
	this->GetSizer()->Layout();
}

void SectorInfoPanel::GenerateHeads(char heads)
{
	this->headComboBox->Clear();
	for (int i = 0; i < heads; i++)
	{
		this->headComboBox->Append(wxString::Format("%d", i));
	}
	if (heads < this->head)
	{
		this->head = heads - 1;
	}
	this->headComboBox->SetSelection(this->head);
}

void SectorInfoPanel::GenerateTracks(char tracks)
{
	this->cylinderComboBox->Clear();
	for (int i = 0; i < tracks; i++)
	{
		this->cylinderComboBox->Append(wxString::Format("%d", i));
	}
	if (tracks < this->cylinder)
	{
		this->cylinder = tracks - 1;
	}
	this->cylinderComboBox->SetSelection(this->cylinder);
}

void SectorInfoPanel::GenerateSectors(char sectors)
{
	this->sectorComboBox->Clear();
	for (int i = 1; i <= sectors; i++)
	{
		this->sectorComboBox->Append(wxString::Format("%d", i));
	}
	if (sectors < this->sector)
	{
		this->sector = sectors - 1;
	}
	this->sectorComboBox->SetSelection(this->sector);
}

char SectorInfoPanel::GetHead()
{
	return this->head;
}

char SectorInfoPanel::GetCylinder()
{
	return this->cylinder;
}

char SectorInfoPanel::GetSector()
{
	return this->sector;
}

void SectorInfoPanel::SetHead(char head)
{
	this->head = head;
}

void SectorInfoPanel::SetCylinder(char cylinder)
{
	this->cylinder = cylinder;
}

void SectorInfoPanel::SetSector(char sector)
{
	this->sector = sector;
}