#include <wx/wx.h>
#include "ArionApp.h"
#include "ArionFrame.h"

IMPLEMENT_APP_NO_MAIN(ArionApp);
IMPLEMENT_WX_THEME_SUPPORT;

int main(int argc, char* argv[])
{
	wxApp::SetInstance(new ArionApp());
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();
	return 0;
}