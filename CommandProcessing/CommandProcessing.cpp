#include "CommandProcessing.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class LogObserver;

//TODO: copy constructor, assignment op, stream insertion

int zro = 0;
int* FileCommandProcessorAdapter::counter = &zro;
LogObserver* Command::obs = NULL;
LogObserver* CommandProcessor ::obs = NULL;

//---------------CONSTRUCTORS-------------------
Command::Command() {};
FileLineReader ::FileLineReader() {};

FileCommandProcessorAdapter ::FileCommandProcessorAdapter() {
    this->flr = new FileLineReader();
    this->flr->readLineFromFile();
};

Command::Command(std::string *command, std::string *effect) {
    this->command = command;
    this->effect = effect;
}


//----------------Getters & Setters -------------

string* Command::getEffect() {
    return this->effect;
}

string* Command::getCommandString(){
    return this->command;
}

vector <Command*> CommandProcessor::getCommandsList(){
    return this->commandsList;
}

vector <string*> FileLineReader::getRawCommands(){
    return this->rawCommands;
}

//-----------------DESTRUCTORS-------------------
Command::~Command() {
    delete command;
    command = nullptr;

    delete effect;
    effect = nullptr;
}
CommandProcessor::~CommandProcessor() {
    for (Command* command: commandsList) {
        delete command;
        command = nullptr;
    }
}
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
    flr = nullptr;
}
FileLineReader::~FileLineReader() {
    for (string* command: rawCommands) {
        delete command;
        command = nullptr;
    }
}

//Getting a string command from the user
string CommandProcessor::readCommand() {
    cout << "Enter your command: " <<endl;
    string command;
    getline(cin, command);
    return command;
};
void CommandProcessor::Notify() {
    string commandAdded = this->stringToLog();
    CommandProcessor::obs->update(commandAdded);
};
string CommandProcessor::stringToLog() {
    string commandAdded = "Command: " + *this->getCommandsList()[this->getListCommand()-1]->getCommandString()+ " has been added.";
            return commandAdded;
};
//Saving a command object that will hold the command and the resulting effect from it
Command* CommandProcessor::saveCommand(string *com, string *effect) {
    Command* command  = new Command(com, effect );
    commandsList.push_back(command);

    return command;

};

//Called from Game Engine to receive command from user
//First reads a command from the user in readCommand
//Saves the command as a Command object
Command* CommandProcessor::getCommand() {
    bool loop = true;
    while (loop) {
        string c = readCommand();
        string effect = "";

        Command* coms = saveCommand(new string(c),new string (effect));

        //if it's a valid command, the loop will terminate and the effect is saved in the GameEngine
        //else reporting to the user they have entered an invalid move at that stage of the game, saved the input as an invalid move
        if (validate(c)) {
            loop = false;
        }
        else
        {
            cout << "invalid move! try again" << endl;
            coms->saveEffect(new string ("invalid move"));
            continue;
        }
        return coms;
    }
}

//when command is executed, effect stored as string in Command object
Command* Command::saveEffect(string *effect) {
    this->effect = effect;
}

//validate method to ensure the user is entering and following the correct schema of the game
//game engine called to retrieve game state for comparison
bool CommandProcessor::validate(string command) {
    GameEngine* trial = new GameEngine();
    vector<string> commandElements = trial->split(command);
    int currentState = trial->userInputToInt(commandElements.at(0));
    return trial->validateMove(currentState);
}

//allows the game engine to read the commands from the file
string FileCommandProcessorAdapter::readCommand() {
    string* cmd =  flr->getRawCommands().at(*counter);
    //counter increments to read the following command one by one
    *counter += 1;
    return *cmd;
}

//method to pass the command from the file to the game engine
Command* FileCommandProcessorAdapter::passCommand() {
    bool loop = true;
    while (loop) {
        string c = FileCommandProcessorAdapter::readCommand();
        string effect = "";

        //saving the command read from the file in a command object
        //initially effect is empty until the game engine sends the effect back, it will be stored with its respective method saveEffect
        Command* coms = saveCommand(new string(c),new string (effect));

        //calling the validate method to ensure the user has entered the correct output at the correct stage of the game
        if (validate(c)) {
            loop = false;
        }
        else
        {
            coms->saveEffect(new string ("invalid move"));
            continue;
        }
        return coms;
    }
}

//method to open a text file the user wishes to read commands from
void FileLineReader::readLineFromFile() {
    bool loopy = true;
    string text;

    //loop to ensure user has entered a txt file and not another file
    while (loopy) {
        cout << "Enter the text file you wish to read commands from: " << endl;
        cin >> text;
        cout << "We are now reading commands from " << text << endl;

        string txt = text.substr (text.length()-4,text.length());
        if (txt != ".txt"){
            cout << "You have not entered a text file, please try again. " << endl;
        }
        else
            loopy = false;
    }

    //opening the file
    ifstream fileReading;
    fileReading.open (text);
    string lineCommand;

    //reads the file until there is nothing else in it
    //it will push into a vector all the commands that it has read from the file
    while (!fileReading.eof()){
        getline(fileReading, lineCommand);
        {
            rawCommands.push_back(new string(lineCommand));
        }
    }
}



