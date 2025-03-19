#pragma once

#include <string>
#include <wx/wx.h>
#include "dependencies/FloppyLib/include/DiskStatistics.h"

class DiskStatsPanel : public wxPanel
{
	private:
		DiskStatistics* statistics;
		wxPanel* statsPanel;
		void InitStats();
	public:
		wxStaticText* header;
		wxStaticText* tracksLabel;
		wxStaticText* tracks;
		wxStaticText* headsLabel;
		wxStaticText* heads;
		wxStaticText* sectorsLabel;
		wxStaticText* sectors;
		wxStaticText* errorsLabel;
		wxStaticText* errors;
		wxStaticText* nothing;
		DiskStatsPanel(wxPanel* parent, DiskStatistics* statistics);
		void UpdateStats(DiskStatistics* Statistics);

};