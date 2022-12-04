//
// Created by Marin on 11/6/2022.
//

#include "CommandProcessing.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class LogObserver;
class Tournament;
class PlayerStrategy;
class Player;

int zro = 0;
int* FileCommandProcessorAdapter::counter = &zro;
LogObserver* Command::obs = NULL;
LogObserver* CommandProcessor ::obs = NULL;

//----------------OVERLOADING INSERTION STREAM OPERATORS----------------------
ostream &operator << (ostream &output, Command &obj) {
    output << "command is being processed." <<endl;
    return output;
}
ostream &operator << (ostream &output, CommandProcessor &obj) {
    output << "Command Processor processing the command." <<endl;
    return output;
}
ostream &operator << (ostream &output, FileCommandProcessorAdapter &obj) {
    output << "File Command Processor adapter is processing the command." <<endl;
    return output;
}
ostream &operator << (ostream &output, FileLineReader &obj){
    output << "File is being read to fetch the command." <<endl;
    return output;
}

//==================COMMANDPROCESSOR CLASS=====================
//------------------OVERLOADING ASSIGNMENT OPERATORS------------
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &commandProcessor){
    for (int i = 0; i < commandProcessor.commandsList.size(); i++){
        this->commandsList[i] = commandProcessor.commandsList[i] ;
    }
}

//---------------CONSTRUCTORS-------------------
//Default
CommandProcessor::CommandProcessor() {};

//Copy Constructor
CommandProcessor::CommandProcessor(CommandProcessor &commandProcessor) {
    this->commandsList = commandProcessor.commandsList;

}

//----------------Getters & Setters ------------
vector <Command*> CommandProcessor::getCommandsList(){
    return this->commandsList;
}
int CommandProcessor::getListCommand() {
    return commandsList.size();
}
void CommandProcessor::setObserver(Observer* o) {
    CommandProcessor::obs = (LogObserver*)o;
};
//-----------------DESTRUCTORS-------------------
CommandProcessor::~CommandProcessor() {
    for (Command* command: commandsList) {
        delete command;
        command = nullptr;
    }
}
//-----------------METHODS------------------------

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
    this->Notify();

    return command;

};

//Called from Game Engine to receive command from user
//First reads a command from the user in readCommand
//Saves the command as a Command object
Command* CommandProcessor::getCommand(){
    bool loop = true;
    while (loop) {
        string c = readCommand();
        string effect = "";

        Command* coms = saveCommand(new string(c),new string (effect));

        //check command is tournament, if so return early
        vector<string> inputArr = Tournament::tokenize(c, ' ');

        if (inputArr[0] == "tournament") {
            string isValidTournament = Tournament::tournamentStrValidate(inputArr);

            if(isValidTournament != "valid") {
                cout << isValidTournament << endl;
                coms->saveEffect(new string (isValidTournament));
                continue;
            }
            else {
                return coms;
            }
        }

        //if it's a valid command, the loop will terminate and the effect is saved in the GameEngine
        //else reporting to the user they have entered an invalid move at that stage of the game, saved the input as an invalid move
        if (validate(c)){
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

//validate method to ensure the user is entering and following the correct schema of the game
//game engine called to retrieve game state for comparison
bool CommandProcessor::validate(string command) {
    GameEngine* trial = new GameEngine();
    vector<string> commandElements = trial->split(command);
    int currentState = trial->userInputToInt(commandElements.at(0));
    return trial->validateMove(currentState);
}



//====================COMMAND CLASS========================
//------------------OVERLOADING ASSIGNMENT OPERATORS--------------
Command &Command::operator=(const Command &t){
    command = t.command;
    effect = t.effect;
}
//---------------CONSTRUCTORS-------------------
Command::Command(){};
Command::Command(std::string *command, std::string *effect){
    this->command = command;
    this->effect = effect;
}
//Copy constructor
Command::Command(Command &command) {
    this->command = command.command;
    this->effect = command.effect;
}
//----------------Getters & Setters -------------
string* Command::getEffect(){
    return this->effect;
}
string* Command::getCommandString(){
    return this->command;
}
void Command::setObserver(Observer* o) {
    Command::obs = (LogObserver*)o;
};
//-----------------DESTRUCTORS-------------------
Command::~Command(){
    delete command;
    command = nullptr;

    delete effect;
    effect = nullptr;
}
//-------------METHODS-----------------
void Command::Notify() {
    string effectAdded = this->stringToLog();
    Command::obs->update(effectAdded);
}
string Command::stringToLog() {
    string effectAdded = "Effect: " + *this->getEffect() + " has been added.";
            return effectAdded;
}

//when command is executed, effect stored as string in Command object
Command* Command::saveEffect(string *effect) {
    this->effect = effect;
    this->Notify();
}


//================FILE COMMAND PROCESSOR ADAPTER CLASS===============
//------------------OVERLOADING ASSIGNMENT OPERATORS-------------
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &t){
    this->flr = t.flr;
    this->counter = t.counter;
}

//---------------CONSTRUCTORS-------------------
FileCommandProcessorAdapter ::FileCommandProcessorAdapter() {
    this->flr = new FileLineReader();
    this->flr->readLineFromFile();
};
//copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter &f){
    this->flr = f.flr;
    this->counter = f.counter;
}
//-----------------DESTRUCTORS-------------------
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
    flr = nullptr;
}

//-----------------METHODS------------------------
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


//=====================FILE LINE READER CLASS===================
//------------------OVERLOADING ASSIGNMENT OPERATORS------------
FileLineReader &FileLineReader::operator=(const FileLineReader &t){
    for (int i = 0; i < t.rawCommands.size(); i++){
        this->rawCommands[i] = t.rawCommands[i] ;
    }
}
//---------------CONSTRUCTORS-------------------
FileLineReader ::FileLineReader() {};

//Copy constructor
FileLineReader::FileLineReader(FileLineReader &lineReader) {
    this->rawCommands = lineReader.rawCommands;
}
//----------------Getters & Setters -------------
vector <string*> FileLineReader::getRawCommands(){
    return this->rawCommands;
}
//-----------------DESTRUCTORS-------------------
FileLineReader::~FileLineReader(){
    for (string* command: rawCommands) {
        delete command;
        command = nullptr;
    }
}

//-----------------METHODS------------------------
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



Tournament::Tournament(vector<string> gameInfo) {
    this->tournamentData = "-------------RISK TOURNAMENT------------\n\n";

    //set maps
    vector<string> m = tokenize(gameInfo[2], ',');
    vector<string*> mPtr;
    for(string s : m) {
        mPtr.push_back(new string(s));
    }
    this->maps = mPtr;
    this->tournamentData += "Tournament Maps : ";
    for(int i = 0; i < m.size(); i++) {
        this->tournamentData += m[i] + "; ";
    }
    this->tournamentData += "\n";

    //set player strategies
    vector<string> players = tokenize(gameInfo[4], ',');
    this->tournamentData += "Players : ";
    vector<PlayerStrategy*> ps;
    for(int i = 0; i < players.size(); i++) {
        string name = players[i] + to_string(i);
        Player* p = new Player(new string(name));

        if (players[i] == "aggressive") {
            ps.push_back(new AggressivePlayerStrategy(p));
        }
        else if (players[i] == "neutral") {
            ps.push_back(new NeutralPlayerStrategy(p));
        }
        else if (players[i] == "benevolent") {
            ps.push_back(new BenevolentPlayerStrategy(p));
        }
        else if (players[i] == "cheater") {
            ps.push_back(new CheaterPlayerStrategy(p));
        }

        this->tournamentData += name + "; ";
    }
    this->playerStrategies = ps;
    this->tournamentData += "\n";

    //set numgames
    this->tournamentData += "Number of games per map: " + gameInfo[6] + "\n";
    int numG = stoi(gameInfo[6]);
    this->numOfGames = new int(numG);

    //set numturns
    this->tournamentData += "Number of turns per game: " + gameInfo[8] + "\n";
    int numT = stoi(gameInfo[8]);
    this->numOfTurns = new int(numT);

    this->tournamentData += "\n\nFINAL RESULTS\n\n";
}

vector<PlayerStrategy*> Tournament::getPlayerStrategies() {
    return this->playerStrategies;
}

vector<string*> Tournament::getMaps(){
    return this->maps;
}
int* Tournament::getNumOfGames(){
    return this->numOfGames;
}
int* Tournament::getNumOfTurns(){
    return this->numOfTurns;
}

void Tournament::setPlayerStrategies(vector<PlayerStrategy*> ps){
    this->playerStrategies = ps;
}
void Tournament::setMaps(vector<string*> m){
    this->maps = m;
}
void Tournament::setNumOfGames(int num){
    this->numOfGames = new int(num);
}
void Tournament::setNumOfTurns(int num){
    this->numOfTurns = new int(num);
}

void Tournament::addGameStat(string map, int gameNumber, string winner) {
    this->tournamentData += map + " || " + to_string(gameNumber) + " - winner: " + winner + "\n";
}

void Tournament::printGameData() {

    //create output file and write to it
    ofstream f;
    f.open("tournamentdata.txt");
//    ofstream f("tournamentdata.txt");
    f << this->tournamentData;
    f.close();
}

string Tournament::tournamentStrValidate(vector<string> inputArr) {
    string message = "valid";

    //check size
    if(inputArr.size() != 9) {
        message = "invalid tournament input";
        return message;
    }

    // check info
    if(inputArr[1] != "-M" || inputArr[3] != "-P" || inputArr[5] != "-G" || inputArr[7] != "-D") {
        message = "invalid tournament input";
        return message;
    }

    // check num of maps is between 1 and 5
    vector<string> maps = tokenize(inputArr[2], ',');
    if (maps.size() < 1 || maps.size() > 5) {
        message = "invalid number of tournament maps";
        return message;
    }

    // check num of players is between 2 and 4 and players are valid strategy
    vector<string> players = tokenize(inputArr[4], ',');
    if (players.size() < 2 || players.size() > 4) {
        message = "invalid number of tournament players";
        return message;
    }

    for(int i = 0; i < players.size(); i++) {
        if (players[i] != "aggressive" && players[i] != "benevolent" && players[i] != "cheater" && players[i] != "neutral") {
            message = "invalid player types";
            return message;
        }
    }

    // check num of games is between 1 and 5
    try {
        int numOfGames = stoi(inputArr[6]);
        if(numOfGames < 1 || numOfGames > 5) {
            message = "invalid number of tournament games";
            return message;
        }
    }
    catch(int n) {
        message = "invalid input for number of games";
        return message;
    }

    // check num of turns is between 10 and 50
    try {
        int numOfTurns = stoi(inputArr[8]);
        if (numOfTurns < 10 || numOfTurns > 50) {
            message = "invalid number of game turns";
            return message;
        }
    }
    catch (int n) {
        message = "invalid input for number of game turns";
        return message;
    }

    return message;

}

vector<string> Tournament::tokenize(string str, char delim)
{
    vector<string> out;

    // construct a stream from the string
    stringstream ss(str);

    string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }
    return out;
}


