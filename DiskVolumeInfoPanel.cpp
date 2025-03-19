#include "DiskVolumeInfoPanel.h"

DiskVolumeInfoPanel::DiskVolumeInfoPanel(wxWindow* parent, InterchangeVolume* volume) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(270, 150))
{
	this->volume = volume;
	this->nothingPanel = new wxPanel(this);
	wxBoxSizer* nothingSizer = new wxBoxSizer(wxVERTICAL);
	this->nothingPanel->SetSizer(nothingSizer);

	wxStaticText* nothing = new wxStaticText(nothingPanel, wxID_ANY, wxT("Nothing to display"));
	nothingSizer->Add(nothing);

	this->volumePanel = new wxPanel(this);
	wxFlexGridSizer* volumeSizer = new wxFlexGridSizer(10, 2, 0, 0);
	wxStaticText* identifierLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Volume Identifier: "));
	this->identifierLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("******"));
	wxStaticText * accessibilityLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Accessibility: "));
	this->accessibilityLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("'*'"));
	wxStaticText* machineLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Machine: "));
	this->machineLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("*************"));
	wxStaticText* ownerLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Owner: "));
	this->ownerLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("*************"));
	wxStaticText* surfaceIndicatorLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Surface Indicator: "));
	this->surfaceIndicatorLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("'*'"));
	wxStaticText* extentArrangementConstraintLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Extent Arrangement Constraint: "));
	this->extentArrangementConstraintLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("false"));
	wxStaticText* nonSequentialRecordingLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Non-Sequential Recording: "));
	this->nonSequentialRecordingLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("false"));
	wxStaticText* sectorSizeLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Sector Size: "));
	this->sectorSizeLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("****"));
	wxStaticText* sectorSequenceCodeLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Sector Sequence Code: "));
	this->sectorSequenceCodeLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("'**'"));
	wxStaticText* standardLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("Label Standard: "));
	this->standardLabel = new wxStaticText(volumePanel, wxID_ANY, wxT("'*'"));

	volumeSizer->Add(identifierLabel);
	volumeSizer->Add(this->identifierLabel);
	volumeSizer->Add(accessibilityLabel);
	volumeSizer->Add(this->accessibilityLabel);
	volumeSizer->Add(machineLabel);
	volumeSizer->Add(this->machineLabel);
	volumeSizer->Add(ownerLabel);
	volumeSizer->Add(this->ownerLabel);
	volumeSizer->Add(surfaceIndicatorLabel);
	volumeSizer->Add(this->surfaceIndicatorLabel);
	volumeSizer->Add(extentArrangementConstraintLabel);
	volumeSizer->Add(this->extentArrangementConstraintLabel);
	volumeSizer->Add(nonSequentialRecordingLabel);
	volumeSizer->Add(this->nonSequentialRecordingLabel);
	volumeSizer->Add(sectorSizeLabel);
	volumeSizer->Add(this->sectorSizeLabel);
	volumeSizer->Add(sectorSequenceCodeLabel);
	volumeSizer->Add(this->sectorSequenceCodeLabel);
	volumeSizer->Add(standardLabel);
	volumeSizer->Add(this->standardLabel);

	this->volumePanel->SetSizer(volumeSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(nothingPanel);
	mainSizer->Add(volumePanel);
	this->SetSizer(mainSizer);
	this->UpdateVolumeInfo(volume);
}

void DiskVolumeInfoPanel::UpdateVolumeInfo(InterchangeVolume* volume)
{
	this->volume = volume;
	if (volume == nullptr)
	{
		this->nothingPanel->Show();
		this->volumePanel->Hide();
	}
	else
	{
		this->identifierLabel->SetLabel(this->volume->GetIdentifier());
		this->accessibilityLabel->SetLabel(wxString::Format("'%c'", this->volume->GetAccessibility()));
		this->machineLabel->SetLabel(this->volume->GetMachine());
		this->ownerLabel->SetLabel(this->volume->GetOwner());
		this->surfaceIndicatorLabel->SetLabel(wxString::Format("'%c'", this->volume->GetSurfaceIndicator()));
		this->extentArrangementConstraintLabel->SetLabel(wxString::Format("%s", this->volume->HasExtentArrangementConstraint() ? "true" : "false"));
		this->nonSequentialRecordingLabel->SetLabel(wxString::Format("%s", this->volume->HasNonSequentialRecording() ? "true" : "false"));
		this->sectorSizeLabel->SetLabel(wxString::Format("%d", this->volume->GetSectorSize()));
		this->sectorSequenceCodeLabel->SetLabel("'"+this->volume->GetSectorSequenceCode()+"'");
		this->standardLabel->SetLabel(wxString::Format("'%c'", this->volume->GetLabelStandard()));
		this->volumePanel->Show();
		this->nothingPanel->Hide();
	}
	this->GetSizer()->Layout();
}