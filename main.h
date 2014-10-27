#if !defined ( NETJOY_MAIN_H )
#define NETJOY_MAIN_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/timer.h>   
#include "netdriver.h"
#include "logger.h"

enum {
    MENU_ABOUT,
    MENU_QUIT,
    PANEL_CAPTURE,
    TIMER
};

/************************** Frame **********************************/
class Frame: public wxFrame {
    public:
        Frame();
        ~Frame();

        void OnMenuAbout(wxCommandEvent &event);
        void OnMenuQuit(wxCommandEvent &event);
        void OnPanelCapture(wxCommandEvent &event);
        void OnTimerCapture(wxTimerEvent &event);

    private:
		void SetupMenu();
		void SetupLogger(wxTextCtrl *logger_text_ctrl);
		void SetupNetInterface();

        NetDriver *net_driver;

        wxChoice *nic_choice;
        wxButton *capture_button;
        wxTimer *capture_timer;

    DECLARE_EVENT_TABLE()
};

/**************************** App **********************************/
class App: public wxApp {
    public:
        virtual bool OnInit();
};

#endif