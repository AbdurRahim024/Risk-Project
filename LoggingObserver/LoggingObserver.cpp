#include "LoggingObserver.h"
#include <algorithm>
using namespace std;
Observer::Observer(){

}
Observer::~Observer() {

};

//SUBJECT INTERFACE
Subject::Subject() {

};

Subject::Subject(Subject* sub) {
    this->observer = sub->getObserver();
};

Subject::~Subject() {
    delete this->observer;
    this->observer = nullptr;
};

Observer *Subject::getObserver() {
    return this->observer;
};

//ILOGGABLE INTERFACE
ILoggable::ILoggable(){

};

ILoggable::~ILoggable() {

};


//LOG OBSERVER CLASS
LogObserver::LogObserver(string filename) {
    fw.open(filename);
};

LogObserver::LogObserver(LogObserver* log) {
    this->fw = log->getFW();
};

void LogObserver::update(string status) {
    fw << status << endl;
};

ofstream LogObserver::getFW() {
    return this->getFW();
};

LogObserver::~LogObserver() {
    fw.close();
};


//----------------stream insertion operator---------------
ostream &operator << (ostream &output, LogObserver &obs) {
    output << "logging inputs" << endl;
    return output;
}

//--------------assignment operator----------------
const LogObserver &LogObserver::operator=(LogObserver *logObserver){
    this->fw = logObserver->getFW();
    return *this;
}





