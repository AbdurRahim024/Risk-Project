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

class CommandProcessor
{
private:
    vector <Command*> commandsList;
protected:
    string readCommand();
    Command* saveCommand(string* command, string* effect);
public:
    Command* getCommand();
    vector <Command*> getCommandsList();
    bool validate(string command);
    ~CommandProcessor();

};

class Command
{
private:
    string* command;
    string* effect;

public:
    Command* saveEffect(string *effect);

    //Constructor for command object
    Command();
    Command(string *command, string *effect);

    //Getters
    string* getEffect();
    string* getCommandString();

    //destructor
    ~Command();


};

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
    FileLineReader* flr;
    static int* counter;
public:
    FileCommandProcessorAdapter();
    string readCommand();
    Command* passCommand();

    //destructor
    ~FileCommandProcessorAdapter();




};

class FileLineReader
{
private:
    vector <string*> rawCommands;
public:
    void readLineFromFile();
    FileLineReader();

    // Getters
    vector<string*> getRawCommands();

    //destructor
    ~FileLineReader();

};


#endif //RISK_PROJECT_COMMANDPROCESSING_H
