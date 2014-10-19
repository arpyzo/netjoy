#if !defined ( NETJOY_MAIN_H )
#define NETJOY_MAIN_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include "netdriver.h"
#include "logger.h"

enum {
    MENU_ABOUT,
    MENU_QUIT,

    PANEL_CAPTURE
};

/************************** Frame **********************************/
class Frame: public wxFrame {
    public:
        Frame();
        ~Frame();

        void Menu_About(wxCommandEvent &event);
        void Menu_Quit(wxCommandEvent &event);
        void Panel_Capture(wxCommandEvent &event);

    private:
		void Setup_Menu();
		wxTextCtrl *Setup_Logger();
		void Setup_Netdriver();

        Netdriver *netdriver;

        wxChoice *nic_choice;

    DECLARE_EVENT_TABLE()
};

/**************************** App **********************************/
class App: public wxApp {
    public:
        virtual bool OnInit();
};

#endif