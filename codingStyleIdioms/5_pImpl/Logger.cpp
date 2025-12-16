#include "Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex> 
#include <sstream>
#include <iomanip>

using namespace std;


class LoggerImpl{
public:
    LoggerImpl(const string& name):filename_(name),log_level_(1),file_stream_(name,std::ios::app){
        if(!file_stream_.is_open()){
            cout<<"Error: Could not open log file: " << name << "\n";
        }
        log_message("Logger initialized.");
    }

    void log_message(const string& message) const{
        lock_guard<mutex> lock(mut_);

        time_t now = time(nullptr);
        tm tm_struct = *localtime(&now);

        file_stream_<<"["
                    << put_time(&tm_struct, "%Y-%m-%d %H:%M:%S") 
                    << "] [LEVEL " << log_level_ << "] " 
                    << message << "\n";
        file_stream_.flush();
        cout<<"[LOG]" << message << "\n";
    }

    void set_level(int level){
        log_level_ =level;
    }


private:
    string filename_;
    int log_level_;
    mutable ofstream file_stream_;
    mutable std::mutex mut_;
};

Logger::Logger(const string& filename):pImpl(new LoggerImpl(filename)){

}

Logger::~Logger(){

}


void Logger::log_message(const std::string& message) const {
    if (pImpl) {
        pImpl->log_message(message);
    }
}

void Logger::set_level(int level) {
    if (pImpl) {
        pImpl->set_level(level);
    }
}