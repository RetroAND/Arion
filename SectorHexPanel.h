#pragma once

#include <vector>
#include <wx/wx.h>
#include "dependencies/FloppyLib/include/FloppyLib.h"

class SectorHexPanel : public wxPanel
{
	private:
		int length;
		std::vector<wxStaticText*> cells;
		void CreateCells();
		void PrepareCells(std::vector<char> data);
		wxPanel* nothingPanel;
		wxPanel* errorPanel;
		wxPanel* hexPanel;
	public:
		SectorHexPanel(wxWindow* parent);
		void UpdateSector(Sector* sector);
};