#pragma once

#include <vector>
#include <wx/wx.h>
#include "dependencies/FloppyLib/include/FloppyLib.h"

class DiskFilePanel : public wxPanel
{
	private:
		int selected;
		std::vector<InterchangeFile> files;
		wxPanel* nothingPanel;
		wxPanel* listPanel;
		wxPanel* emptyPanel;
		wxButton* exportAllButton;
		wxStaticText* fileIdentifier;
		wxStaticText* blockLength;
		wxStaticText* recordAttribute;
		wxStaticText* beginningOfExtent;
		wxStaticText* physicalRecordLength;
		wxStaticText* endOfExtent;
		wxStaticText* fixedLengthRecord;
		wxStaticText* bypassIndicator;
		wxStaticText* datasetSecurity;
		wxStaticText* writeProtect;
		wxStaticText* exchangeTypeIndicator;
		wxStaticText* multiVolumeIndicator;
		wxStaticText* volumeSequence;
		wxStaticText* creationDate;
		wxStaticText* recordLength;
		wxStaticText* offsetToNextRecordSpace;
		wxStaticText* expirationDate;
		wxStaticText* verifyCopyIndicator;
		wxStaticText* datasetOrganization;
		wxStaticText* endOfData;
		wxStaticText* creatingMachine;
		wxPanel* listContainerPanel;
	public:
		wxListBox* fileList;
		DiskFilePanel(wxWindow* parent);
		void UpdateFiles(std::vector<InterchangeFile>* files);
		void SelectFile(int file);

};