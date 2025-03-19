#include "DiskFilePanel.h"
#include "AppId.h"

using namespace std;

DiskFilePanel::DiskFilePanel(wxWindow* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(270, 150))
{
	this->files = vector<InterchangeFile>();
	this->selected = 0;
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainSizer);
	this->nothingPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* nothingSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* nothing = new wxStaticText(this->nothingPanel, wxID_ANY, wxT("Nothing to display"));
	nothingSizer->Add(nothing);

	this->emptyPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* emptySizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* empty = new wxStaticText(this->emptyPanel, wxID_ANY, wxT("This disk does not contain any file"));
	emptySizer->Add(empty);

	this->listContainerPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* listContainerSizer = new wxBoxSizer(wxHORIZONTAL);
	listContainerPanel->SetSizer(listContainerSizer);

	this->listPanel = new wxPanel(listContainerPanel, wxID_ANY);
	wxBoxSizer* listSizer = new wxBoxSizer(wxVERTICAL);
	this->fileList = new wxListBox(this->listPanel, ID_DiskFileList);
	listSizer->Add(this->fileList);
	listContainerSizer->Add(this->listPanel);

	wxPanel* fileInfoPanel = new wxPanel(listContainerPanel, wxID_ANY);
	wxFlexGridSizer* fileInfoSizer = new wxFlexGridSizer(20,2,0,0);
	listContainerSizer->Add(fileInfoPanel);
	wxStaticText* fileIdentifierLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("File Identifier: "));
	this->fileIdentifier = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("***********"));
	wxStaticText* blockLengthLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Block Length: "));
	this->blockLength = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("****"));
	wxStaticText* recordAttributeLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Record Attribute: "));
	this->recordAttribute = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* beginningOfExtentLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Beginning of Extent: "));
	this->beginningOfExtent = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("C: ** H: * S:**"));
	wxStaticText* physicalRecordLengthLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Physical Record Length: "));
	this->physicalRecordLength = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* endOfExtentLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("End of Extent: "));
	this->endOfExtent = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("C: ** H: * S: **"));
	wxStaticText* fixedLengthRecordLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Fixed Record Length: "));
	this->fixedLengthRecord = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("false"));
	wxStaticText* bypassIndicatorLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Bypass Indicator: "));
	this->bypassIndicator = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("false"));
	wxStaticText* datasetSecurityLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Dataset Security: "));
	this->datasetSecurity = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* writeProtectLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Write Protect: "));
	this->writeProtect = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("false"));
	wxStaticText* exchangeTypeIndicatorLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Exchange Type Indicator: "));
	this->exchangeTypeIndicator = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* multiVolumeIndicatorLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Multi-Volume Indicator: "));
	this->multiVolumeIndicator = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* volumeSequenceLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Volume Sequence: "));
	this->volumeSequence = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'**'"));
	wxStaticText* creationDateLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Creation Date: "));
	this->creationDate = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'******'"));
	wxStaticText* recordLengthLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Record Length: "));
	this->recordLength = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("****"));
	wxStaticText* offsetToNextRecordSpaceLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Offset to Next Record Space: "));
	this->offsetToNextRecordSpace = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("****"));
	wxStaticText* expirationDateLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Expiration Date: "));
	this->expirationDate = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'******'"));
	wxStaticText* verifyCopyIndicatorLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Verify/Copy Indicator: "));
	this->verifyCopyIndicator = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* datasetOrganizationLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("Dataset Organization: "));
	this->datasetOrganization = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'*'"));
	wxStaticText* endOfDataLabel = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("End of Data: "));
	this->endOfData = new wxStaticText(fileInfoPanel, wxID_ANY, wxT("'C: ** H: * S: **'"));
	fileInfoSizer->Add(fileIdentifierLabel);
	fileInfoSizer->Add(fileIdentifier);
	fileInfoSizer->Add(blockLengthLabel);
	fileInfoSizer->Add(blockLength);
	fileInfoSizer->Add(recordAttributeLabel);
	fileInfoSizer->Add(recordAttribute);
	fileInfoSizer->Add(beginningOfExtentLabel);
	fileInfoSizer->Add(beginningOfExtent);
	fileInfoSizer->Add(physicalRecordLengthLabel);
	fileInfoSizer->Add(physicalRecordLength);
	fileInfoSizer->Add(endOfExtentLabel);
	fileInfoSizer->Add(endOfExtent);
	fileInfoSizer->Add(fixedLengthRecordLabel);
	fileInfoSizer->Add(fixedLengthRecord);
	fileInfoSizer->Add(bypassIndicatorLabel);
	fileInfoSizer->Add(bypassIndicator);
	fileInfoSizer->Add(datasetSecurityLabel);
	fileInfoSizer->Add(datasetSecurity);
	fileInfoSizer->Add(writeProtectLabel);
	fileInfoSizer->Add(writeProtect);
	fileInfoSizer->Add(exchangeTypeIndicatorLabel);
	fileInfoSizer->Add(exchangeTypeIndicator);
	fileInfoSizer->Add(multiVolumeIndicatorLabel);
	fileInfoSizer->Add(multiVolumeIndicator);
	fileInfoSizer->Add(volumeSequenceLabel);
	fileInfoSizer->Add(volumeSequence);
	fileInfoSizer->Add(creationDateLabel);
	fileInfoSizer->Add(creationDate);
	fileInfoSizer->Add(recordLengthLabel);
	fileInfoSizer->Add(recordLength);
	fileInfoSizer->Add(offsetToNextRecordSpaceLabel);
	fileInfoSizer->Add(offsetToNextRecordSpace);
	fileInfoSizer->Add(expirationDateLabel);
	fileInfoSizer->Add(expirationDate);
	fileInfoSizer->Add(verifyCopyIndicatorLabel);
	fileInfoSizer->Add(verifyCopyIndicator);
	fileInfoSizer->Add(datasetOrganizationLabel);
	fileInfoSizer->Add(datasetOrganization);
	fileInfoSizer->Add(endOfDataLabel);
	fileInfoSizer->Add(endOfData);
	fileInfoPanel->SetSizer(fileInfoSizer);
	this->exportAllButton = new wxButton(this->listPanel, ID_ExportAllFiles, wxT("Export All"));
	listSizer->Add(this->exportAllButton);
	this->listPanel->SetSizer(listSizer);
	
	mainSizer->Add(this->nothingPanel);
	mainSizer->Add(this->emptyPanel);
	mainSizer->Add(listContainerPanel);

	this->UpdateFiles(nullptr);
}

void DiskFilePanel::UpdateFiles(vector<InterchangeFile>* files)
{
	if (files == nullptr)
	{
		this->files.clear();
		this->nothingPanel->Show();
		this->emptyPanel->Hide();
		this->listContainerPanel->Hide();
	}
	else if(files->empty())
	{
		this->files = *files;
		this->nothingPanel->Hide();
		this->emptyPanel->Show();
		this->listContainerPanel->Hide();
	}
	else
	{
		this->files = *files;
		this->fileList->Clear();

		for (vector<InterchangeFile>::iterator it = this->files.begin(); it != this->files.end(); ++it)
		{
			this->fileList->Append(it->GetFileIdentifier());
		}
		if (this->selected >= this->files.size())
		{
			this->selected = this->files.size() - 1;
		}
		this->SelectFile(0);

		this->nothingPanel->Hide();
		this->emptyPanel->Hide();
		this->listContainerPanel->Show();
	}
	this->GetSizer()->Layout();
}

void DiskFilePanel::SelectFile(int file)
{
	this->selected = file;
	this->fileList->SetSelection(this->selected);
	this->fileIdentifier->SetLabel(this->files[this->selected].GetFileIdentifier());
	this->blockLength->SetLabel(wxString::Format("%d",this->files[this->selected].GetBlockLength()));
	this->recordAttribute->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetRecordAttribute()));
	this->beginningOfExtent->SetLabel(wxString::Format("C: %d H: %d S: %d", this->files[this->selected].GetBeginningOfExtent().GetCylinder(), this->files[this->selected].GetBeginningOfExtent().GetHead(), this->files[this->selected].GetBeginningOfExtent().GetSector()));
	this->physicalRecordLength->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetPhysicalRecordLength()));
	this->endOfExtent->SetLabel(wxString::Format("C: %d H: %d S: %d", this->files[this->selected].GetEndOfExtent().GetCylinder(), this->files[this->selected].GetEndOfExtent().GetHead(), this->files[this->selected].GetEndOfExtent().GetSector()));
	this->fixedLengthRecord->SetLabel(wxString::Format("%s", this->files[this->selected].HasFixedRecordLength() ? "true" : "false"));
	this->bypassIndicator->SetLabel(wxString::Format("%s", this->files[this->selected].HasBypassIndicator() ? "true" : "false"));
	this->datasetSecurity->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetDatasetSecurity()));
	this->writeProtect->SetLabel(wxString::Format("%s", this->files[this->selected].IsWriteProtected() ? "true" : "false"));
	this->exchangeTypeIndicator->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetExchangeTypeIndicator()));
	this->multiVolumeIndicator->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetMultiVolumeIndicator()));
	this->volumeSequence->SetLabel(this->files[this->selected].GetVolumeSequence());
	this->creationDate->SetLabel(this->files[this->selected].GetCreationDate());
	this->recordLength->SetLabel(wxString::Format("%d",this->files[this->selected].GetRecordLength()));
	this->offsetToNextRecordSpace->SetLabel(this->files[this->selected].GetOffsetToNextRecordSpace());
	this->expirationDate->SetLabel(this->files[this->selected].GetExpirationDate());
	this->verifyCopyIndicator->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetVerifyCopyIndicator()));
	this->datasetOrganization->SetLabel(wxString::Format("'%c'", this->files[this->selected].GetDatasetOrganization()));
	this->endOfData->SetLabel(wxString::Format("C: %d H: %d S: %d", this->files[this->selected].GetEndOfData().GetCylinder(), this->files[this->selected].GetEndOfData().GetHead(), this->files[this->selected].GetEndOfData().GetSector()));
}
