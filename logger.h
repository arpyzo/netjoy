#if !defined ( NETJOY_LOGGER_H )
#define NETJOY_LOGGER_H

#include <wx/wx.h>

/************************** Logger **********************************/
class Logger {
    public:
        Logger();
        static void Debug(char *message);
        static void Info(char *message);
        static void Error(char *message);

};

#endif