#if !defined ( NETJOY_LOGGER_H )
#define NETJOY_LOGGER_H

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <string>
using namespace std;

/********************************** Logger **********************************/
class Logger {
    public:
        static Logger *GetInstance();
        static void Release();

        void SetOutput(wxTextCtrl *output);

        void Debug(string message);
        void Info(string message);
        void Error(string message);

    private:
        Logger();

        static Logger *logger_instance;

        wxTextCtrl *output;
};

#endif