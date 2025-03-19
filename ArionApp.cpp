#include "ArionApp.h"
#include "ArionFrame.h"

bool ArionApp::OnInit()
{
	SetAppearance(Appearance::System);
	ArionFrame* frame = new ArionFrame();
	frame->Show(true);
	return true;
}