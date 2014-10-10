#include "debug.h"
#include "logger.h"

/***************************** Logger ******************************/
Logger::Logger() {

}

void Logger::Debug(char *message) {
    wxMessageBox(message);
}

void Logger::Info(char *message) {
    wxMessageBox(message);
}

void Logger::Error(char *message) {
    wxMessageBox(message);
}