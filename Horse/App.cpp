#include <wx/wx.h>
#include <wx/clipbrd.h>
class MyApp : public wxApp
{
public:
    virtual bool OnInit() {
        if (wxTheClipboard->Open())
        {
            wxTheClipboard->SetData(new wxTextDataObject("Some text"));
            wxTheClipboard->Close();
        }
        return true;
    };
    virtual int OnExit() {
        return true;
    };
};
//
//wxIMPLEMENT_APP(MyApp);

IMPLEMENT_APP_NO_MAIN(MyApp);
IMPLEMENT_WX_THEME_SUPPORT;
int APIENTRY wWinMain(HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] LPTSTR lpCmdLine, int nCmdShow)
{
    wxCmdLineArgType cmdLine = (char*)lpCmdLine;
    int flag = wxEntryStart(hInstance, hPrevInstance, cmdLine, nCmdShow);
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();

    //wxApp* pApp = new MyApp();
    //wxApp::SetInstance(pApp);
    //int flag = wxEntry(hInstance, hPrevInstance, cmdLine, nCmdShow);
    return 0;
}