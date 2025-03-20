#pragma once

#include <vector>
#include <wx/wx.h>
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include <wx/generic/grid.h>

class SectorHexPanel : public wxPanel
{
	private:
		int length;
		std::vector<wxStaticText*> cells;
		void PrepareCells(std::vector<char> data);
		wxPanel* nothingPanel;
		wxPanel* errorPanel;		
	public:
		wxGrid* hexPanel;
		SectorHexPanel(wxWindow* parent);
		void UpdateSector(Sector* sector);
};