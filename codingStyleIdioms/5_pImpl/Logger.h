#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <string>
using namespace std;

class LoggerImpl;

class Logger{
public:
    Logger(const string& filename);

    ~Logger();

    // Logger(const Logger&) = delete;
    // Logger& operator=(const Logger&) = delete;

    void log_message(const string& message) const;
    void set_level(int level);

private:
    unique_ptr<LoggerImpl> pImpl;
};


#endif