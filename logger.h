#if !defined ( NETJOY_LOGGER_H )
#define NETJOY_LOGGER_H

#include <wx/wx.h>

/************************** Logger **********************************/
class Logger {
    public:
        Logger();
        void Debug(char *message);
        void Info(char *message);
        void Error(char *message);

};

#endif