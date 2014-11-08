#include "debug.h"
#include "logger.h"

Logger *Logger::logger_instance = NULL;

/********************************** Logger **********************************/
Logger::Logger() {
}

Logger *Logger::GetInstance() {
    if (!logger_instance) {
        logger_instance = new Logger();
    }
    return logger_instance;
}

void Logger::Release() {
    if (logger_instance) {
        delete logger_instance;
    }
}

void Logger::SetOutput(wxTextCtrl *output) {
    this->output = output;
}
//TODO: Set different font colors
//TODO: Add multiple debug levels
void Logger::Debug(string message) {
    output->AppendText(message + "\n");
}

void Logger::Info(string message) {
    output->AppendText(message + "\n");
}

void Logger::Error(string message) {
    output->AppendText(message + "\n");
}