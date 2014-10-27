#include "debug.h"
#include "main.h"

IMPLEMENT_APP(App)

/***************************** Frame ******************************/
BEGIN_EVENT_TABLE(Frame,wxFrame)
    EVT_MENU    (MENU_ABOUT, Frame::OnMenuAbout)
    EVT_MENU    (MENU_QUIT,  Frame::OnMenuQuit)
    EVT_BUTTON  (PANEL_CAPTURE, Frame::OnPanelCapture)
    EVT_TIMER   (TIMER, Frame::OnTimerCapture)
END_EVENT_TABLE()

Frame::Frame() 
: wxFrame((wxFrame *)NULL, -1, "NetJoy", wxPoint(200,200), wxSize(500,200)) {
    SetIcon(wxIcon("NetJoy.ico"));

	wxTextCtrl *text_ctrl = Setup_Logger();

	SetupNetDriver();

    SetupMenu();

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    wxBoxSizer *main_vsizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *panel_hsizer = new wxBoxSizer(wxHORIZONTAL);
    
    nic_choice = new wxChoice(panel, wxID_ANY);
	nic_choice->Append(wxArrayString(2, (const char **)netdriver->GetNicNames()));
	nic_choice->SetSelection(0);

    wxButton *capture_button = new wxButton(panel, PANEL_CAPTURE, "Start");
    
    panel_hsizer->Add(nic_choice, 0, wxALL, 10);
    panel_hsizer->Add(capture_button, 0, wxALL, 10);
    panel->SetSizer(panel_hsizer);

    main_vsizer->Add(panel, 0, wxEXPAND);    
    main_vsizer->Add(text_ctrl, 1, wxEXPAND);
    SetSizer(main_vsizer);

    capture_timer = new wxTimer(this, TIMER);
}

void Frame::SetupNetDriver() {
    netdriver = new NetDriver();
}

void Frame::SetupMenu() {
    wxMenuBar *menu_bar = new wxMenuBar();
    wxMenu *file_menu = new wxMenu();
    wxMenu *help_menu = new wxMenu();
    
    file_menu->Append(MENU_QUIT, "E&xit");
    menu_bar->Append(file_menu, "&File");

    help_menu->Append(MENU_ABOUT, "&About..");
    menu_bar->Append(help_menu, "&Help");

    SetMenuBar(menu_bar);
}

wxTextCtrl *Frame::Setup_Logger() {
	wxTextCtrl *text_ctrl = new wxTextCtrl(this,wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

	Logger::GetInstance()->SetOutput(text_ctrl);

	return text_ctrl;
}

void Frame::OnMenuAbout(wxCommandEvent &WXUNUSED(event)) {
    wxMessageBox("wxWidgets Template\nRobert Pyzalski 2014", "About..", wxICON_INFORMATION);
}

void Frame::OnMenuQuit(wxCommandEvent &WXUNUSED(event)) {
    Close(TRUE);
}

void Frame::OnPanelCapture(wxCommandEvent &WXUNUSED(event)) {
    netdriver->ToggleCapture(nic_choice->GetString(nic_choice->GetCurrentSelection()).char_str());
    // TODO: check for success acquiring timer
    capture_timer->Start(1, true);
    Logger::GetInstance()->Debug("Timer started.\n");
}

void Frame::OnTimerCapture(wxTimerEvent &WXUNUSED(event)) {
    //Logger::GetInstance()->Debug("Timer fired!\n");
    netdriver->GetPackets();
    capture_timer->Start(100, true);
}

Frame::~Frame() {
    delete capture_timer;
    delete netdriver;
    Logger::Release();
}

/*************************** App_Class ****************************/
bool App::OnInit() {
    Frame *main_frame = new Frame();
    main_frame->Show(TRUE);

    return TRUE;
}

