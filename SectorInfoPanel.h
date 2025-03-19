#pragma once

#include <wx/wx.h>
#include <wx/combobox.h>
#include "dependencies/FloppyLib/include/FloppyLib.h"

class SectorInfoPanel : public wxPanel
{
	private:
		char head;
		char cylinder;
		char sector;
		Disk* disk;
		wxPanel* nothingPanel;
		wxPanel* infoPanel;
		wxComboBox* cylinderComboBox;
		wxComboBox* headComboBox;
		wxComboBox* sectorComboBox;
	public:
		SectorInfoPanel(wxWindow* parent, Disk* disk);
		void UpdateInfo(Disk* disk);
		void GenerateHeads(char heads);
		void GenerateTracks(char tracks);
		void GenerateSectors(char sectors);
		void OnHeadSelected(wxCommandEvent& event);
		void OnCylinderSelected(wxCommandEvent& event);
		void OnSectorSelected(wxCommandEvent& event);
};