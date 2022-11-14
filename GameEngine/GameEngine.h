#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Player.h"
#include "map.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"

using namespace std;

class GameEngine: public Subject, public ILoggable{
private:
    Map* gameMap;
    vector<Player*> players;

    unordered_map<int,vector<int*>> allowedStates;
    unordered_map<int,string*> intToStringState;
    static int* state;
    string* transitionLog;

    //ILoggable
    static LogObserver* obs;

public:
    // CONSTRUCTOR
    GameEngine();

    // COPY CONSTRUCTOR
    GameEngine(const GameEngine& ge);

    // ASSIGNMENT OPERATOR
    GameEngine& operator=(const GameEngine& ge);

    // STREAM INSERTION OPERATOR
    friend ostream& operator <<(ostream& os, GameEngine& ge);

    // GETTERS
    int* getState();
    string* getStateAsString();
    unordered_map<int,string*> getIntToStringState();

    void gameFlow(string userInput);
    bool validateMove(int move);
    int userInputToInt(string userInput);

    // DESTRUCTOR
    ~GameEngine();

    // START UP PHASE METHODS
    void startupPhase();
    string* execute(string* command);

    string* loadMap(string mapName);
    string* validateMap();
    string* addPlayer(string* name);
    string* gameStart();
    void shufflePlayerOrder();

    vector<string> split(string cmd);
    Map* testMap();


    //Part 3 Abdur & Nauar
    void mainGameLoop();
    void reinforcementPhase(vector<Player*> listOfPlayers,Map* map);
    OrdersLists* issueOrdersPhase(vector<Player*> listOfPlayers,Map* map);
    void executeOrdersPhase(OrdersLists* list );
    int continentBonus(Player* player, Map* map);

    //ILoggable
    static void setObserver(LogObserver* o);
    void Notify() override;
    string stringToLog() override;
};
