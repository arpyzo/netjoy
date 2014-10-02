#if !defined ( NETJOY_MAIN_H )
#define NETJOY_MAIN_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include "netdriver.h"

enum {
    MENU_ABOUT,
    MENU_QUIT
};

/************************** Frame **********************************/
class Frame: public wxFrame {
    public:
        Frame();
        void Setup_Netdriver();
        void Setup_Menu();

        void Menu_About(wxCommandEvent &event);
        void Menu_Quit(wxCommandEvent &event);

    private:
        Netdriver *netdriver;

    DECLARE_EVENT_TABLE()
};

/**************************** App **********************************/
class App: public wxApp {
    public:
        virtual bool OnInit();
};

#endif