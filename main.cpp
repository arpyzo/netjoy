#include "debug.h"
#include "main.h"

IMPLEMENT_APP(App)

/***************************** Frame ******************************/
BEGIN_EVENT_TABLE(Frame,wxFrame)
    EVT_MENU    (MENU_ABOUT, Frame::Menu_About)
    EVT_MENU    (MENU_QUIT,  Frame::Menu_Quit)
    EVT_BUTTON  (PANEL_CAPTURE, Frame::Panel_Capture)
END_EVENT_TABLE()

Frame::Frame() 
: wxFrame((wxFrame *)NULL, -1, "wxWidgets Template", wxPoint(100,100), wxSize(300,200)) {
    SetIcon(wxIcon("NetJoy.ico"));

    Setup_Netdriver();

    Setup_Menu();

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    wxBoxSizer *main_vsizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *panel_hsizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxChoice *nic_choice = new wxChoice(panel, wxID_ANY);
    //nic_choice->Append(netdriver->Get_NIC_List());
    nic_choice->Append("Item 1");
    nic_choice->Append("Item 2");
    nic_choice->SetSelection(0);

    wxButton *capture_button = new wxButton(panel, PANEL_CAPTURE, "Start");
    
    panel_hsizer->Add(nic_choice, 0, wxALL, 10);
    panel_hsizer->Add(capture_button, 0, wxALL, 10);
    panel->SetSizer(panel_hsizer);
    main_vsizer->Add(panel, 0, wxEXPAND);
    
    wxTextCtrl *textctrl = new wxTextCtrl(this, wxID_ANY);
    main_vsizer->Add(textctrl, 1, wxEXPAND);
    SetSizer(main_vsizer);
}

void Frame::Setup_Netdriver() {
    netdriver = new Netdriver();
    //if (!Init_NIC()) {
    //    return FALSE;
    //}
    netdriver->Init_NIC();
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

void Frame::Menu_About(wxCommandEvent &WXUNUSED(event)) {
    wxMessageBox("wxWidgets Template\nRobert Pyzalski 2014", "About..", wxICON_INFORMATION);
}

void Frame::Menu_Quit(wxCommandEvent &WXUNUSED(event)) {
    Close(TRUE);
}

void Frame::Panel_Capture(wxCommandEvent &WXUNUSED(event)) {
    netdriver->Toggle_Capture();
}

/*************************** App_Class ****************************/
bool App::OnInit() {
    Frame *main_frame = new Frame();
    main_frame->Show(TRUE);
    return TRUE;
}

