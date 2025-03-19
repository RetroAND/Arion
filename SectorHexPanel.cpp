#include "SectorHexPanel.h"

SectorHexPanel::SectorHexPanel(wxWindow* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(270, 150))
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	this->hexPanel = new wxPanel(this, wxID_ANY);
	mainSizer->Add(this->hexPanel);
	this->SetSizer(mainSizer);
	wxGridSizer* grid = new wxGridSizer(128, 64, 2, 2);
	this->hexPanel->SetSizer(grid);
	this->CreateCells();
}

void SectorHexPanel::CreateCells()
{
	wxSizer* sizer = this->hexPanel->GetSizer();
	for (int i = 0; i < 512; i++)
	{
		wxStaticText* cell = new wxStaticText(this->hexPanel, wxID_ANY, wxT("00"));
		//cell->Hide();
		sizer->Add(cell);
		this->cells.push_back(cell);
	}
}

void SectorHexPanel::UpdateSector(Sector* sector)
{
	if (sector == nullptr)
	{
		this->nothingPanel->Show();
		this->errorPanel->Hide();
		this->hexPanel->Hide();
	}
	else if (sector->IsEmpty())
	{
		this->nothingPanel->Hide();
		this->errorPanel->Show();
		this->hexPanel->Hide();
	}
	else
	{
		this->PrepareCells(sector->GetData());
		this->nothingPanel->Hide();
		this->errorPanel->Hide();
		this->hexPanel->Show();
	}
	this->GetSizer()->Layout();
}

void SectorHexPanel::PrepareCells(std::vector<char> data)
{

}