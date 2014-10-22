#if !defined ( NETJOY_LOGGER_H )
#define NETJOY_LOGGER_H

#include <wx/wx.h>
#include <wx/textctrl.h>

/************************** Logger **********************************/
class Logger {
    public:
        static Logger *Get_Instance();
        static void Release();

        void Set_Output(wxTextCtrl *output);

        void Debug(char *message);
        void Info(char *message);
        void Error(char *message);

    private:
        Logger();
        //~Logger();
        static Logger *logger_instance;

        wxTextCtrl *output;
};

#endif