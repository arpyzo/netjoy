#if !defined ( NETJOY_MAIN_H )
#define NETJOY_MAIN_H

#define WPCAP
#define HAVE_REMOTE

#include <wx/wx.h>
#include <wx/splitter.h>
#include <pcap.h>

enum {
    MENU_ABOUT,
    MENU_QUIT
};

/************************** Frame **********************************/
class Frame: public wxFrame {
    public:
        Frame();
        void Setup_Menu();

        void Menu_About(wxCommandEvent &event);
        void Menu_Quit(wxCommandEvent &event);

    DECLARE_EVENT_TABLE()
};

/**************************** App **********************************/
class App: public wxApp {
    public:
        virtual bool OnInit();

    private:
        bool Init_NIC();
};

#endif