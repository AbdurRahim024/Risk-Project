#include "GameEngine.h"
#include <vector>

//
// Created by Emma on 2022-10-06.
//

int zeroState = 0;
int *GameEngine::state = &zeroState;
LogObserver *GameEngine::obs = NULL;

GameEngine::GameEngine() {
    intToStringState[0] = new string("start");
    intToStringState[1] = new string("map loaded");
    intToStringState[2] = new string("map validated");
    intToStringState[3] = new string("players added");
    intToStringState[4] = new string("assign reinforcement");
    intToStringState[5] = new string("issue orders");
    intToStringState[6] = new string("execute orders");
    intToStringState[7] = new string("win");
    intToStringState[8] = new string("end");


    allowedStates[0].push_back(new int(1));

    allowedStates[1].push_back(new int(1)); // mapLoadedCommands
    allowedStates[1].push_back(new int(2)); // mapLoadedCommands

    allowedStates[2].push_back(new int(3)); // mapValidatedCommands

    allowedStates[3].push_back(new int(3)); // playersAddedCommands
    allowedStates[3].push_back(new int(4)); // playersAddedCommands

    allowedStates[4].push_back(new int(5)); // AssignReinforcementCommands

    allowedStates[5].push_back(new int(5)); // IssueOrdersCommands
    allowedStates[5].push_back(new int(10000)); // IssueOrdersCommands

    allowedStates[6].push_back(new int(6)); // executeOrdersCommands
    allowedStates[6].push_back(new int(1000)); // executeOrdersCommands
    allowedStates[6].push_back(new int(7)); // executeOrdersCommands

    allowedStates[7].push_back(new int(100)); // winCommands
    allowedStates[7].push_back(new int(8)); // winCommands

}

// COPY CONSTRUCTOR
GameEngine::GameEngine(const GameEngine &ge) {
    cout << "Copy constructor of Game Engine called" << endl;
    allowedStates = ge.allowedStates;
    intToStringState = ge.intToStringState;

}

// ASSIGNMENT OPERATOR
GameEngine &GameEngine::operator=(const GameEngine &ge) {
    cout << "Copy assignment operator of Game Engine" << endl;
    this->state = ge.state;
    this->allowedStates = ge.allowedStates;
    this->intToStringState = ge.intToStringState;
    return *this;
}

// STREAM INSERTION OPERATOR
ostream &operator<<(ostream &os, GameEngine &ge) {
    cout << "current state: " << endl;
    cout << "<" + *(ge.intToStringState[*ge.state]) + ">" << endl;
    return os;
}

// GETTERS
int *GameEngine::getState() {
    return state;
}

string *GameEngine::getStateAsString() {
    return intToStringState[*state];
}

unordered_map<int, string *> GameEngine::getIntToStringState() {
    return intToStringState;
}

// OTHER

void GameEngine::gameFlow(string userInput) {
    // this method handles state transitions


    // convert user input from string to int
    int moveInt = userInputToInt(userInput);

    // if user move is valid, transition state by incrementing the state variable by the appropriate amount
    if (validateMove(moveInt)) {
        int advance = moveInt - *state;
        int nextState = *state + advance;

        // edge cases: these special values handle the loop transitions
        if (nextState == 10000) {
            *state = 6;
        } else if (nextState == 1000) {
            *state = 4;
        } else if (nextState == 100) {
            *state = 0;
        } else {
            *state = nextState;
        }

    } else {
        // invalid move
        cout << "Invalid move! Try again" << endl << endl;
    }

    transitionLog = new string("New state: " + *intToStringState[*state] + "\n");
    Notify();
}

bool GameEngine::validateMove(int move) {
    // check that the user's move is part of the allowed moves at a specific state
    for (int *validMove: allowedStates[*state]) {
        if (move == *validMove) {
            return true;
        }
    }

    return false;
}

int GameEngine::userInputToInt(string userInput) {
    // convert the user input from string to int
    if (userInput == "loadmap") {
        return 1;
    } else if (userInput == "validatemap") {
        return 2;
    } else if (userInput == "addplayer") {
        return 3;
    } else if (userInput == "gamestart") {
        return 4;
    } else if (userInput == "issueorder") {
        return 5;
    } else if (userInput == "endissueorders") {
        return 10000; //edge case
    } else if (userInput == "execorder") {
        return 6;
    } else if (userInput == "endexecorders") {
        return 1000; //edge case
    } else if (userInput == "win") {
        return 7;
    } else if (userInput == "replay") {
        return 100; //edge case
    } else if (userInput == "quit") {
        return 8;
    } else {
        return -1;
    }
}

// START UP PHASE
void GameEngine::startupPhase() {
    cout << "Startup phase" << endl << endl;
    cout << *this << endl;

    cout << "'-console' to read from console" << endl;
    cout << "'-file <filename>' to read from file" << endl;

    string choice;
    cout << "Enter your choice: " << endl;
    getline(cin, choice);

    // reading from the console
    if (choice == "-console") {
        CommandProcessor *cp = new CommandProcessor();

        //while state isn't in assign reinforcement (first step of play phase)
        while (*state != 4) {
            Command *command = cp->getCommand();
            string *effect = execute(command->getCommandString());
            command->saveEffect(effect);
        }

        cout << "Play phase has begun\n" << endl;

        //printing all commands received
        for (Command *command: cp->getCommandsList()) {
            cout << *(command->getCommandString()) << endl;
            cout << *(command->getEffect()) << endl << endl;
        }
    }

        // reading from a text file
    else {
        FileCommandProcessorAdapter *fp = new FileCommandProcessorAdapter();

        //while state isn't in assign reinforcement (first step of play phase)
        while (*state != 4) {
            Command *command = fp->passCommand();
            string *effect = execute(command->getCommandString());
            command->saveEffect(effect);
        }

        cout << "Play phase has begun\n" << endl;

        //printing all commands received
        for (Command *command: fp->getCommandsList()) {
            cout << *(command->getCommandString()) << endl;
            cout << *(command->getEffect()) << endl << endl;
        }
    }
}

// GAME TRANSITION HELPERS

string *GameEngine::execute(string *command) {
    vector<string> commandElements = split(*command);
    string *effect;

    // call appropriate method
    if (commandElements.at(0) == "loadmap") {
        effect = loadMap(commandElements.at(1));
    } else if (commandElements.at(0) == "validatemap") {
        effect = validateMap();
    } else if (commandElements.at(0) == "addplayer") {
        effect = addPlayer(new string(commandElements.at(1)));
    } else if (commandElements.at(0) == "gamestart") {
        effect = gameStart();
    }

    return effect;

}

string *GameEngine::loadMap(string mapName) {

    MapLoader *loader = new MapLoader;
    this->gameMap = loader->loadMap(mapName);

//    this->gameMap = testMap();

    //effect
    cout << "The map " << mapName << " was loaded into the game engine" << endl;

    //transition state
    string effect = "The map " + mapName + " was loaded into the game engine.\n";
    gameFlow("loadmap");
    cout << *this << endl;
    return new string(effect);
}

string *GameEngine::validateMap() {
    string effect = "";

    // invalid map
    if (!this->gameMap->validate()) {
        cout << "Map validation failed" << endl;
        cout << *this << endl;
        effect = "validatemap failed because the current map is invalid";
        return new string(effect);
    }

    // valid map -> transition state
    effect += "The current game map is valid!\n";
    gameFlow("validatemap");
    cout << *this << endl;
    return new string(effect);

}


string *GameEngine::addPlayer(string *name) {
    string effect = "";

    //check num of players is less than 6
    if (players.size() >= 6) {
        cout << "Too many players!" << endl;
        effect = "This addplayer command failed because the maximum number of players is reached";
        return new string(effect);
    }

    //add new player
    Player *p = new Player(name);
    players.push_back(p);

    //effect
    cout << *name << " was added to the game" << endl;

    //transition state
    effect += *name + " was added to the game\n";
    gameFlow("addplayer");
    cout << *this << endl;
    return new string(effect);
}


string *GameEngine::gameStart() {
    string effect = "";

    //check num of players is less than 6
    if (players.size() < 2) {
        effect = "This gamestart command failed because there are not enough players to start the game";
        cout << effect << endl;
        return new string(effect);
    }

    //init deck
    Deck *d = new Deck(players);

    //distribute territories to players
    vector<Territory *> territories = gameMap->getAllTerritories();

    for (int i = 0; i < players.size(); i++) {

        //evenly assign territories to players
        for (int j = i; j < territories.size(); j += players.size()) {
            players.at(i)->addTerritory(territories.at(j));
        }

        //give 50 initial army units to each player (add to reinforcement pool)
        players.at(i)->setReinforcements(50);

        //each player draws 2 cards
        players.at(i)->getHand()->addToHand(d->draw());
        players.at(i)->getHand()->addToHand(d->draw());

    }

    //determine random order of players
    shufflePlayerOrder();

    //effect
    cout << "The game has successfully started\n" << endl;
    cout << "Printing current game data..\n" << endl;

    cout << "map info..." << endl;
    cout << *(this->gameMap) << endl;

    cout << "\nplayer info... " << endl;
    for (Player *p: players) {
        cout << *p << endl;
    }

    //transition state
    effect = "The game has successfully started\n";
    gameFlow("gamestart");
    cout << *this << endl;
    return new string(effect);
}

void GameEngine::shufflePlayerOrder() {

    int numOfPlayers = players.size();

    //swap random indices 10 times
    for (int i = 0; i < 10; i++) {
        srand(time(nullptr)); // a new set of random numbers is generated

        //indices to swap
        int randomIndex1 = rand() % (numOfPlayers - 1);
        int randomIndex2 = rand() % (numOfPlayers - 1);

        //swap
        Player *tmp = players.at(randomIndex1);
        players.at(randomIndex1) = players.at(randomIndex2);
        players.at(randomIndex2) = tmp;
    }

}

vector<string> GameEngine::split(string cmd) {
    string delimiter = " ";
    size_t pos = 0;
    string command;
    string name;
    vector<string> elements;
    bool isSpace = false;

    while ((pos = cmd.find(delimiter)) != string::npos) {
        isSpace = true;
        command = cmd.substr(0, pos);
        elements.push_back(command);
        cmd.erase(0, pos + delimiter.length());
        name = cmd.substr(0, pos + 1);
        elements.push_back(name);

        break;
    }
    if (!isSpace) {
        elements.push_back(cmd);
    }

    return elements;
}

Map *testMap() {

    Map *m = new Map();

    Continent *af = new Continent(new string("AFRICA"), new int(5));
    Territory *kenya = new Territory(new string("KENYA"), af);
    Territory *ethiopia = new Territory(new string("ETHIOPIA"), af);
    Territory *sudan = new Territory(new string("SUDAN"), af);


    Continent *as = new Continent(new string("ASIA"), new int(6));
    Territory *india = new Territory(new string("INDIA"), as);
    Territory *pakistan = new Territory(new string("PAKISTAN"), as);
    Territory *china = new Territory(new string("CHINA"), as);

    af->setListofTerritories(kenya);
    af->setListofTerritories(ethiopia);
    af->setListofTerritories(sudan);

    as->setListofTerritories(india);
    as->setListofTerritories(pakistan);
    as->setListofTerritories(china);

    kenya->setAdjacentTerritories(ethiopia);

    ethiopia->setAdjacentTerritories(kenya);
    ethiopia->setAdjacentTerritories(sudan);

    sudan->setAdjacentTerritories(ethiopia);
    sudan->setAdjacentTerritories(india);

    india->setAdjacentTerritories(sudan);
    india->setAdjacentTerritories(pakistan);
    india->setAdjacentTerritories(china);

    pakistan->setAdjacentTerritories(india);
    pakistan->setAdjacentTerritories(china);

    china->setAdjacentTerritories(pakistan);
    china->setAdjacentTerritories(india);

    m->setAllTerritories(kenya);
    m->setAllTerritories(sudan);
    m->setAllTerritories(ethiopia);
    m->setAllTerritories(india);
    m->setAllTerritories(pakistan);
    m->setAllTerritories(china);

    m->setSubgraph(af);
    m->setSubgraph(as);

    return m;

}


// MAIN GAME LOOP

// DESTRUCTOR
GameEngine::~GameEngine() {
    for (auto entry: allowedStates) {
        for (int *n: entry.second) {
            delete n;
            n = nullptr;
        }
    }

    for (auto entry: intToStringState) {
        delete entry.second;
        entry.second = nullptr;
    }
}

void mainGameLoop() {
    //first phase of game loop is to calculate number of reinforcement armies
    //reinforcementPhase();
    //if listOfPlayers is equal to 1 call end game screen

}

//This method will loop over all the continents and check if a player owns all the territories in the particular continent
// and return the total bonus value added to players' reinforceement pool
int GameEngine::continentBonus(Player *player, Map *map) {
    int totalBonus = 0;
    for (int i = 0; i < map->getSubgraph().size(); ++i) {
        bool getsTheBonus = true;
        for (int j = 0; j < map->getSubgraph()[i]->getListofTerritories().size(); ++j) {
            if (map->getSubgraph()[i]->getListofTerritories()[j]->getPlayerName() != *player->getName()) {
                getsTheBonus = false;
                break;

            }
        }
        if (getsTheBonus) {
            totalBonus += map->getSubgraph()[i]->getBonusValue();
        }
    }
    return totalBonus;
}

//This method assigns reinforcements to each player depending on the number of territories owned along with the bonus value if any
void GameEngine::reinforcementPhase(vector<Player *> listOfPlayers, Map *map) {
    for (int i = 0; i < listOfPlayers.size(); ++i) {
        int reinforcements = 3;
        int territoryValue = listOfPlayers[i]->getTerritories().size();
        territoryValue = territoryValue / 3;
        int bonusValue = continentBonus(listOfPlayers[i], map);
        if (reinforcements < territoryValue + bonusValue) {
            reinforcements = territoryValue + bonusValue;
        }
//            int *reinforcementPointer = &reinforcements; //might mess up
        listOfPlayers[i]->setReinforcements(reinforcements);
    }
}



// This method created orders using the issue order method and pushes the orders into the orders list
OrdersLists *GameEngine::issueOrdersPhase(vector<Player *> listOfPlayers) {
    OrdersLists *list = new OrdersLists();
    for (int i = 0; i < listOfPlayers.size(); ++i) {
        for (int j = 0; j < listOfPlayers[i]->issueOrder().size(); ++j) {
            list->add(listOfPlayers[i]->issueOrder()[j]);
        }
    }
    return list;
}

void executeOrdersPhase(OrdersLists *list) {
//    print header
    cout << "======= ORDERS NOW EXECUTING =======" << endl << endl;
//    call execute on and print each order
    for (Order *o: list->getOrders()) {
        o->execute();
        cout << *o;
    }
//    print footer
    cout << "===== ORDERS FINISHED EXECUTING =====" << endl << endl << endl << endl << endl;
}

//ILoggable
void GameEngine::Notify() {
    string status = this->stringToLog();
    GameEngine::obs->update(status);
}

string GameEngine::stringToLog() {
    return *transitionLog;
}

void GameEngine::setObserver(LogObserver *o) {
    GameEngine::obs = o;
}

