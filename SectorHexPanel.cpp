#include "SectorHexPanel.h"

SectorHexPanel::SectorHexPanel(wxWindow* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(640, 480))
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	this->hexPanel = new wxGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(640, 480));
	this->hexPanel->CreateGrid(512, 16);
	mainSizer->Add(this->hexPanel, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM);
	this->SetSizer(mainSizer);
}

void SectorHexPanel::UpdateSector(Sector* sector)
{
	this->hexPanel->ClearGrid();
	if (sector == nullptr)
	{
		//this->nothingPanel->Show();
		//this->errorPanel->Hide();
		this->hexPanel->Hide();
	}
	else if (sector->IsEmpty())
	{
		//this->nothingPanel->Hide();
		//this->errorPanel->Show();
		this->hexPanel->Hide();
	}
	else
	{
		this->PrepareCells(sector->GetData());
		//this->nothingPanel->Hide();
		//this->errorPanel->Hide();
		this->hexPanel->Show(true);
	}
	this->GetSizer()->Layout();
}

void SectorHexPanel::PrepareCells(std::vector<char> data)
{
	int columns = 16;
	int rows = data.size() / columns;
	int maxRows = 8192 / columns;
	for (int column = 0; column < columns; column++)
	{
		this->hexPanel->SetColLabelValue(column, wxString::Format("%02x", column));
	}
	int offset = 0;
	for (int currentRow = 0; currentRow < rows; currentRow++)
	{
		this->hexPanel->SetRowLabelValue(currentRow, wxString::Format("%04x", offset));
		this->hexPanel->ShowRow(currentRow);
		for (int currentColumn = 0; currentColumn < columns; currentColumn++)
		{
			this->hexPanel->SetCellValue(currentRow, currentColumn, wxString::Format("%02x", data[currentRow * columns + currentColumn] & 0xff));
			this->hexPanel->SetReadOnly(currentRow, currentColumn);
			this->hexPanel->SetCellAlignment(currentRow, currentColumn, wxALIGN_CENTER, wxALIGN_CENTER);
		}
		offset += columns;
	}
	for (int currentRow = rows; currentRow < maxRows; currentRow++)
	{
		this->hexPanel->HideRow(currentRow);
	}
	this->hexPanel->AutoSize();
}