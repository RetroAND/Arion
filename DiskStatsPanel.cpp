#include "DiskStatsPanel.h"

using namespace std;

DiskStatsPanel::DiskStatsPanel(wxPanel* parent, DiskStatistics* statistics) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(270, 150))
{
	this->statistics = statistics;
	this->InitStats();
	this->UpdateStats(statistics);
}

void DiskStatsPanel::InitStats()
{
	this->header = new wxStaticText(this, wxID_ANY, wxT("Disk Statistics"));
	this->nothing = new wxStaticText(this, wxID_ANY, wxT("Nothing to display"));
	this->statsPanel = new wxPanel(this);
	wxFlexGridSizer* grid = new wxFlexGridSizer(4,2,0,0);
	this->tracksLabel = new wxStaticText(statsPanel, wxID_ANY, wxT("Tracks:"));
	this->tracks = new wxStaticText(statsPanel, wxID_ANY, wxString::Format(wxT("%d"), 9999));
	this->headsLabel = new wxStaticText(statsPanel, wxID_ANY, wxT("Heads:"));
	this->heads = new wxStaticText(statsPanel, wxID_ANY, wxString::Format(wxT("%d"), 9999));
	this->sectorsLabel = new wxStaticText(statsPanel, wxID_ANY, wxT("Sectors:"));
	this->sectors = new wxStaticText(statsPanel, wxID_ANY, wxString::Format(wxT("%d"), 9999));
	this->errorsLabel = new wxStaticText(statsPanel, wxID_ANY, wxT("Errors:"));
	this->errors = new wxStaticText(statsPanel, wxID_ANY, wxString::Format(wxT("%d"), 9999));
	grid->Add(this->tracksLabel, 1, wxEXPAND);
	grid->Add(this->tracks, 1, wxEXPAND);
	grid->Add(this->headsLabel, 1, wxEXPAND);
	grid->Add(this->heads, 1, wxEXPAND);
	grid->Add(this->sectorsLabel, 1, wxEXPAND);
	grid->Add(this->sectors, 1, wxEXPAND);
	grid->Add(this->errorsLabel, 1, wxEXPAND);
	grid->Add(this->errors, 1, wxEXPAND);
	this->statsPanel->SetSizer(grid);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(this->header);
	sizer->Add(this->nothing);
	sizer->Add(statsPanel, wxEXPAND);
	this->SetSizer(sizer);
}

void DiskStatsPanel::UpdateStats(DiskStatistics* statistics)
{
	this->statistics = statistics;
	if (statistics == nullptr)
	{
		this->statsPanel->Hide();
		this->nothing->Show();
	}
	else
	{	
		this->tracks->SetLabel(wxString::Format(wxT("%d"), this->statistics->GetTracks()));
		this->heads->SetLabel(wxString::Format(wxT("%d"), this->statistics->GetHeads()));
		this->sectors->SetLabel(wxString::Format(wxT("%d"), this->statistics->GetSectors()));
		this->errors->SetLabel(wxString::Format(wxT("%d"), this->statistics->GetErrors()));
		if (this->statistics->GetErrors() > 0)
		{
			this->errors->SetForegroundColour(wxColour("#ff0000"));
		}
		else
		{
			this->errors->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_INFOTEXT));
		}
		this->nothing->Hide();
		this->statsPanel->Show();
	}
	this->GetSizer()->Layout();
}