#if !defined ( NETJOY_LOGGER_H )
#define NETJOY_LOGGER_H

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <string>
using namespace std;

/************************** Logger **********************************/
class Logger {
    public:
        static Logger *GetInstance();
        static void Release();

        void SetOutput(wxTextCtrl *output);

        void Debug(char *message);
        void Info(char *message);
        void Error(char *message);
        void Test(string message);

    private:
        Logger();

        static Logger *logger_instance;

        wxTextCtrl *output;
};

#endif