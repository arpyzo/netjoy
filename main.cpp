#include "debug.h"
#include "main.h"

IMPLEMENT_APP(App)

/***************************** Frame ******************************/
BEGIN_EVENT_TABLE(Frame,wxFrame)
    EVT_MENU    (MENU_ABOUT, Frame::Menu_About)
    EVT_MENU    (MENU_QUIT,  Frame::Menu_Quit)
    EVT_BUTTON  (PANEL_CAPTURE, Frame::Panel_Capture)
    EVT_TIMER   (TIMER, Frame::Timer_Capture)
END_EVENT_TABLE()

Frame::Frame() 
: wxFrame((wxFrame *)NULL, -1, "NetJoy", wxPoint(200,200), wxSize(500,200)) {
    SetIcon(wxIcon("NetJoy.ico"));

	wxTextCtrl *text_ctrl = Setup_Logger();

	Setup_Netdriver();

    Setup_Menu();

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    wxBoxSizer *main_vsizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *panel_hsizer = new wxBoxSizer(wxHORIZONTAL);
    
    nic_choice = new wxChoice(panel, wxID_ANY);
	nic_choice->Append(wxArrayString(2, (const char **)netdriver->Get_NIC_Names()));
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

void Frame::Setup_Netdriver() {
    netdriver = new Netdriver();
}

void Frame::Setup_Menu() {
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
	wxTextCtrl *text_ctrl = new wxTextCtrl(this, wxID_ANY);

	Logger::Get_Instance()->Set_Output(text_ctrl);

	return text_ctrl;
}

void Frame::Menu_About(wxCommandEvent &WXUNUSED(event)) {
    wxMessageBox("wxWidgets Template\nRobert Pyzalski 2014", "About..", wxICON_INFORMATION);
}

void Frame::Menu_Quit(wxCommandEvent &WXUNUSED(event)) {
    Close(TRUE);
}

void Frame::Panel_Capture(wxCommandEvent &WXUNUSED(event)) {
    //netdriver->Toggle_Capture(nic_choice->GetString(nic_choice->GetCurrentSelection()).char_str());
    // TODO: check for timer success
    capture_timer->Start(10, true);
    Logger::Get_Instance()->Debug("Timer started.\n");
}

void Frame::Timer_Capture(wxTimerEvent &WXUNUSED(event)) {
    Logger::Get_Instance()->Debug("Timer fired!\n");
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

