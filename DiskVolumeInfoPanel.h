#pragma once

#include "dependencies/FloppyLib/include/InterchangeVolume.h"
#include "wx/wx.h"

class DiskVolumeInfoPanel : public wxPanel
{
	private:
		InterchangeVolume* volume;
		wxPanel* nothingPanel;
		wxPanel* volumePanel;
		wxStaticText* identifierLabel;
		wxStaticText* accessibilityLabel;
		wxStaticText* machineLabel;
		wxStaticText* ownerLabel;
		wxStaticText* surfaceIndicatorLabel;
		wxStaticText* extentArrangementConstraintLabel;
		wxStaticText* nonSequentialRecordingLabel;
		wxStaticText* sectorSizeLabel;
		wxStaticText* sectorSequenceCodeLabel;
		wxStaticText* standardLabel;
	public:
		DiskVolumeInfoPanel(wxWindow* parent, InterchangeVolume* volume);
		void UpdateVolumeInfo(InterchangeVolume* volume);
};