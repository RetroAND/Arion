#pragma once

#include <wx/wx.h>
#include <wx/combobox.h>
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include "SectorHexPanel.h"

class SectorInfoPanel : public wxPanel
{
	private:
		unsigned char head;
		unsigned char cylinder;
		unsigned char sector;
		Disk* disk;
		wxPanel* nothingPanel;
		wxPanel* infoPanel;	
	public:
		SectorHexPanel* hexPanel;
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