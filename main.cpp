#include "debug.h"
#include "main.h"

IMPLEMENT_APP(App)

/***************************** Frame ******************************/
BEGIN_EVENT_TABLE(Frame,wxFrame)
    EVT_MENU    (MENU_ABOUT, Frame::Menu_About)
    EVT_MENU    (MENU_QUIT,  Frame::Menu_Quit)
END_EVENT_TABLE()

Frame::Frame() 
: wxFrame((wxFrame *)NULL, -1, "wxWidgets Template", wxPoint(100,100), wxSize(300,200)) {
    SetIcon(wxIcon("NetJoy.ico"));
    Setup_Menu();

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    wxBoxSizer *main_vsizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *panel_hsizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxChoice *nic_choice = new wxChoice(panel, wxID_ANY);
    //nic_choice->Append(net_card->Get_NIC_List());
    nic_choice->Append("Item 1");
    nic_choice->Append("Item 2");
    nic_choice->SetSelection(0);
    
    panel_hsizer->Add(nic_choice, 0, wxALL, 10);
    panel->SetSizer(panel_hsizer);
    main_vsizer->Add(panel, 0, wxEXPAND);
    
    wxTextCtrl *textctrl = new wxTextCtrl(this, wxID_ANY);
    main_vsizer->Add(textctrl, 1, wxEXPAND);
    SetSizer(main_vsizer);
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

/*************************** App_Class ****************************/
bool App::OnInit() {
    if (!Init_NIC()) {
        return FALSE;
    }

    Frame *main_frame = new Frame();
    main_frame->Show(TRUE);
    return TRUE;
}

bool App::Init_NIC() {
    pcap_if_t *nics, *nic;
	pcap_t *fp;
	char error_buffer[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	int res;

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &nics, error_buffer) == -1) {
		wxMessageBox("Failed to retrieve network card list!");
        return FALSE;
	} else {
		for (nic = nics; nic; nic = nic->next) {
			wxMessageBox(wxString::Format("\"%s\"", nic->name));
			if (nic->description) {
				wxMessageBox(wxString::Format(" (%s)\n", nic->description));
			}
			else {
				wxMessageBox("(No description available)\n");
			}
		}
	}

    return TRUE;

	/*if ((fp = pcap_open(nics->next->name, 100, PCAP_OPENFLAG_PROMISCUOUS, 20, NULL, error_buffer)) == NULL) {
		wxMessageBox(wxString::Format("Error opening source: %s", error_buffer));
	} else {
		// Read the packets
		while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0) {

			if (res == 0)
				// Timeout elapsed
				continue;

			// print pkt timestamp and pkt len
			wxMessageBox(wxString::Format("%ld:%ld (%ld)\n", header->ts.tv_sec, header->ts.tv_usec, header->len));

			// Print the packet
			for (int i = 1; (i < header->caplen + 1); i++) {
				printf("%.2x ", pkt_data[i - 1]);
				if ((i % 16) == 0) printf("\n");
			}

			printf("\n\n");
		}

		if (res == -1) {
			wxMessageBox(wxString::Format("Error reading the packets: %s\n", pcap_geterr(fp)));
		}
	}*/
}