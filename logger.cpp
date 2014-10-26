#include "debug.h"
#include "logger.h"

Logger *Logger::logger_instance = NULL;

/***************************** Logger ******************************/
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

void Logger::Debug(char *message) {
    output->AppendText(wxString::Format("%s\n", message));
}

void Logger::Info(char *message) {
    output->AppendText(wxString::Format("%s\n", message));
}

void Logger::Error(char *message) {
    output->AppendText(wxString::Format("%s\n", message));
}

void Logger::Test(string message) {
    output->AppendText(message);
}