#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class Subject;
class ILoggable;

class Observer {
    public:
        //-------------- Constructor --------------//
        // Default
        Observer();

        //-------------- Destructor --------------//
        ~Observer();

        //-------------- Others --------------//
        virtual void update(string notifyString) = 0;
};

class Subject {
    private:
        Observer* observer;
    public:
        //-------------- Constructors --------------//
        // Default
        Subject();
        // Copy
        Subject(Subject* sub);

        //-------------- Destructor --------------//
        ~Subject();

        //-------------- Others --------------//
        Observer* getObserver();
        virtual void Notify() = 0;
};

class ILoggable{
    public:
        ILoggable();
        ~ILoggable();
        virtual string stringToLog() = 0;
};

class LogObserver : public Observer {
private:
    ofstream fw;

public:
    LogObserver(string filename);
    LogObserver(LogObserver* log);
    ~LogObserver();
    void update(string status);
    ofstream getFW();

    friend ostream &operator << (ostream &output, LogObserver &obs);

    const LogObserver &operator=(LogObserver *logObserver);
};