#pragma once

#include <wx/wx.h>
#include "DiskStatsPanel.h"
#include "DiskVolumeInfoPanel.h"
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include "SectorInfoPanel.h"
#include "DiskFilePanel.h"

class ArionFrame : public wxFrame
{
	public:
		ArionFrame();
		DiskStatsPanel* stats;
	private:
		Disk* disk;
		InterchangeDisk* interchange;
		SectorInfoPanel* sectorInfoPage;
		DiskVolumeInfoPanel* volumeInfoPage;
		DiskFilePanel* filePanel;
		void InitMain();
		void OnOpenFile(wxCommandEvent& event);
		void OnCloseFile(wxCommandEvent& event);
		void OnAutoIdentification(wxCommandEvent& event);
		void OnManualIdentification(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void ShowErrorDialog(std::string title, std::string text);
		void IdentifyDisk();
		void OnHeadSelected(wxCommandEvent& event);
		void OnCylinderSelected(wxCommandEvent& event);
		void OnSectorSelected(wxCommandEvent& event);
		void OnFileChosen(wxCommandEvent& event);
		void OnFileExport(wxCommandEvent& event);
		void ShowConfirmationDialog(std::string title, std::string text);
};