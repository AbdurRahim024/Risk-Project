#pragma once
#ifndef RISK_PROJECT_COMMANDPROCESSING_H
#define RISK_PROJECT_COMMANDPROCESSING_H
#include <stdio.h>
#include <iostream>
#include <string>
#include "GameEngine.h"
using namespace std;

class Command;
class FileLineReader;
class FileCommandProcessorAdapter;


class CommandProcessor : public ILoggable, public Subject {
private:
    vector <Command*> commandsList;
    static LogObserver* obs;

protected:
    virtual string readCommand();
    Command* saveCommand(string* command, string* effect);

public:


    //stream insertion operator
    friend ostream &operator << (ostream &output, CommandProcessor &obj);

    //assignment operator
    CommandProcessor& operator=(const CommandProcessor &commandProcessor); //dom changed

    //constructors
    CommandProcessor();

    //copy constructor
    CommandProcessor(CommandProcessor &commandProcessor);

    //getters & setters
    vector <Command*> getCommandsList();
    int getListCommand();
    static void setObserver(Observer* o);

    //destructors
    ~CommandProcessor();

    //methods
    Command* getCommand();
    bool validate(string command);

    void Notify() override;
    string stringToLog() override;
};

class Command : public ILoggable, public Subject {
private:
    string* command;
    string* effect;
    static LogObserver* obs;

public:
    //insertion stream operators
    friend ostream &operator << (ostream &output, Command &obj);

    //assignment operator
    Command &operator=(const Command &t); //dom changed

    //Constructor
    Command();
    Command(string *command, string *effect);

    //copy constructor
    Command(Command &command);

    //Getters & Setters
    string* getEffect();
    string* getCommandString();
    static void setObserver(Observer* o);

    //Destructor
    ~Command();

    //Methods
    Command* saveEffect(string *effect);
    void Notify() override;
    string stringToLog() override;
};

class FileCommandProcessorAdapter: public CommandProcessor
{
private:
    FileLineReader* flr;
    static int* counter;

public:
    //insertion stream operators
    friend ostream &operator << (ostream &output, FileCommandProcessorAdapter &obj);

    //assignment operators
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &t);

    //constructors
    FileCommandProcessorAdapter();
    //copy constructor
    FileCommandProcessorAdapter(FileCommandProcessorAdapter &f);

    //Destructor
    ~FileCommandProcessorAdapter();

    //Methods
    string readCommand();
    Command* passCommand();

};

class FileLineReader
{
private:
    vector <string*> rawCommands;

public:
    //Insertion stream operator
    friend ostream &operator << (ostream &output, FileLineReader &obj);

    //Assignment operator
    FileLineReader &operator=(const FileLineReader &t); //dom changed

    //Constructor
    FileLineReader();

    //Copy constructor
    FileLineReader(FileLineReader &lineReader);

    //Getters & Setters
    vector<string*> getRawCommands();

    //Destructor
    ~FileLineReader();

    //Methods
    void readLineFromFile();
};


ostream &operator << (ostream &output, Command &obj);
ostream &operator << (ostream &output, CommandProcessor &obj);
ostream &operator << (ostream &output, FileCommandProcessorAdapter &obj);
ostream &operator << (ostream &output, FileLineReader &obj);


#endif //RISK_PROJECT_COMMANDPROCESSING_H

