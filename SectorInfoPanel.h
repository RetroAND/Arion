#pragma once

#include <wx/wx.h>
#include <wx/combobox.h>
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include "SectorHexPanel.h"

class SectorInfoPanel : public wxPanel
{
	private:
		char head;
		char cylinder;
		char sector;
		Disk* disk;
		wxPanel* nothingPanel;
		wxPanel* infoPanel;
		SectorHexPanel* hexPanel;
		
	public:
		wxComboBox* cylinderComboBox;
		wxComboBox* headComboBox;
		wxComboBox* sectorComboBox;
		SectorInfoPanel(wxWindow* parent, Disk* disk);
		void UpdateInfo(Disk* disk);
		void GenerateHeads(char heads);
		void GenerateTracks(char tracks);
		void GenerateSectors(char sectors);
		char GetHead();
		char GetCylinder();
		char GetSector();
		void SetHead(char head);
		void SetCylinder(char cylinder);
		void SetSector(char sector);
};