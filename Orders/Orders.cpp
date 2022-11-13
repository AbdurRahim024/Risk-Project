#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;



///// to do add notify and stringToLog when part 5 is set up
///// to do double check calling parent (check all copy constructors)
///// to do finish testing and cleaning
///// to do github



//////////////////////////////    ORDER    //////////////////////////////
///// CONSTRUCTORS
Order::Order() {
//    set data member orderName as blank by default
    this->setOrderName(new string(""));
//    set data member orderEffect as blank by default
    this->setOrderEffect(new string(""));
//    set data member executable as false by default
    this->setExecutable(new bool(false));
//    set data member player as NULL by default
    this->player = NULL;
};

Order::Order(string* orderName) {
//    set data member orderName as value passed into constructor
    this->setOrderName(orderName);
//    set data member orderEffect as blank by default
    this->setOrderEffect(new string(""));
//    set data member executable as false by default
    this->setExecutable(new bool(false));
//    set data member player as NULL by default
    this->player = NULL;
};

Order::Order(Order* order) {
//    set data member orderName as orderName of object passed into constructor
    this->setOrderName(order->getOrderName());
//    set data member orderEffect as orderEffect of object passed into constructor
    this->setOrderEffect(order->getOrderEffect());
//    set data member executable as executable of object passed into constructor
    this->setExecutable(new bool(order->getExecutable()));
//    set data member player as executable of object passed into constructor
    this->setPlayer(order->getPlayer());
};

///// DESTRUCTOR
Order::~Order() {
    delete this->orderName;
    delete this->orderEffect;
    delete this->executable;
    delete this->player;
    this->orderName = nullptr;
    this->orderEffect = nullptr;
    this->executable = nullptr;
    this->player = nullptr;
};

///// GETTERS
string* Order::getOrderName() {
    return this->orderName;
};

string* Order::getOrderEffect() {
    return this->orderEffect;
};

bool* Order::getExecutable() {
    return this->executable;
};

Player* Order::getPlayer() {
    return this->player;
};

///// SETTERS
void Order::setOrderName(string* orderName) {
    this->orderName = orderName;
};

void Order::setOrderEffect(string* orderEffect) {
    this->orderEffect = orderEffect;
};

void Order::setExecutable(bool* exec) {
    this->executable = exec;
};

void Order::setPlayer(Player* player) {
    this->player = player;
};


///// METHODS
bool* Order::equals(Order* order) {
    return new bool(false);
};

bool* Order::validate() {
    return new bool(false);
};

void Order::execute() {};

Order* Order::createSubtype(string s) {
//    create string str
    string* str = new string(s);
//    compare str to each subtype name and return an object of the subtype
    if(str->compare("DEPLOY") == 0) {
        return (Deploy*)new Order(str);
    } else if(str->compare("ADVANCE") == 0) {
        return (Advance*)new Order(str);
    } else if(str->compare("BOMB") == 0) {
        return (Bomb*)new Order(str);
    } else if(str->compare("BLOCKADE") == 0) {
        return (Blockade*)new Order(str);
    } else if(str->compare("AIRLIFT") == 0) {
        return (Airlift*)new Order(str);
    } else {
        return (Negotiate*)new Order(str);
    }
}

Order* Order::createSubtype(Order* order) {
//    take orderName as a string to compare
    string* name = order->getOrderName();
//    compare str to each subtype name and return an object of the subtype
    if(name->compare("DEPLOY") == 0) {
        return new Deploy((Deploy*)order);
    } else if(name->compare("ADVANCE") == 0) {
        return new Advance((Advance*)order);
    } else if(name->compare("BOMB") == 0) {
        return new Bomb((Bomb*)order);
    } else if(name->compare("BLOCKADE") == 0) {
        return new Blockade((Blockade*)order);
    } else if(name->compare("AIRLIFT") == 0) {
        return new Airlift((Airlift*)order);
    } else {
        return new Negotiate((Negotiate*)order);
    }
};





//////////////////////////////    DEPLOY    //////////////////////////////
///// CONSTRUCTORS
Deploy::Deploy(int* unitsToSend, string* targetName, Player* player) : Order(new string("DEPLOY")) {
//    call parent constructor using order type "Deploy"
//    set parameters in attributes
    this->setPlayer(player);
    this->setUnitsAtStart(this->player->getReinforcements());
    this->setUnitsToSend(unitsToSend);
    this->setTargetName(targetName);
    this->setTargetTerritory(NULL);
};

Deploy::Deploy(Deploy* deploy) : Order(deploy) {
    this->setUnitsAtStart(new int(deploy->getUnitsAtStart()));
    this->setUnitsToSend(new int(deploy->getUnitsToSend()));
    this->setTargetName(deploy->getTargetName());
    this->setTargetTerritory(deploy->getTargetTerritory());
};

///// DESTRUCTOR
Deploy::~Deploy() {
    delete this->unitsAtStart;
    delete this->unitsToSend;
    delete this->targetName;
    delete this->targetTerritory;
    this->unitsAtStart = nullptr;
    this->unitsToSend = nullptr;
    this->targetName = nullptr;
    this->targetTerritory = nullptr;
};

///// GETTERS
int Deploy::getUnitsAtStart() {
    return *this->unitsAtStart;
};

int Deploy::getUnitsToSend() {
    return *this->unitsToSend;
};

string* Deploy::getTargetName() {
    return this->targetName;
};

Territory* Deploy::getTargetTerritory() {
    return this->targetTerritory;
};

///// SETTERS
void Deploy::setUnitsAtStart(int* unitsAtStart) {
    this->unitsAtStart = unitsAtStart;
};

void Deploy::setUnitsToSend(int* unitsToSend) {
    this->unitsToSend = unitsToSend;
};

void Deploy::setTargetName(string* targetName) {
    this->targetName = targetName;
};

void Deploy::setTargetTerritory(Territory* targetTerritory) {
    this->targetTerritory = targetTerritory;
};

///// METHODS
bool* Deploy::equals(Order* order) {
//    if the two orders have similar attributes, return true
    if(
            this->getOrderName()->compare(*((Deploy*)order)->getOrderName()) == 0 &&
            this->getPlayer()->getName()->compare(*((Deploy*)order)->getPlayer()->getName()) == 0 &&
            *this->unitsAtStart == ((Deploy*)order)->getUnitsAtStart() &&
            *this->unitsToSend == ((Deploy*)order)->getUnitsToSend() &&
            this->targetName->compare(*((Deploy*)order)->getTargetName()) == 0
            ) {
        return new bool(true);
    }
//    else, return false
    return new bool(false);
};

bool* Deploy::validate() {
//    order invalid if there are insufficient units to send
    if(*this->unitsToSend <= 0 || *this->unitsAtStart < *this->unitsToSend) {
        return new bool(false);
    }
//    get list of player's owned territories
    vector<Territory*> playerTerritories = this->player->getTerritories();
//    parse through playerTerritories
    for(int i = 0; i < playerTerritories.size(); i++) {
//        if targetName is found, update necessary attributes and return true
        if(playerTerritories[i]->getTerritoryName().compare(*this->targetName) == 0) {
//            set conditional attribute
            this->targetTerritory = playerTerritories[i];
            return new bool(true);
        }
    }
//    else, return false
    return new bool(false);
};

void Deploy::execute() {
//    call validate to see if Order is executable
    bool* boolean = this->validate();
//    if statement to verify if the order was valid
    if(!*boolean) {
        return;
    }
//    update player's reinforcements using the setter method
    this->player->setReinforcements(this->unitsAtStart - this->unitsToSend);
//    update target territory's number of armies
    this->targetTerritory->setNoOfArmies(this->targetTerritory->getNoOfArmies() + *this->unitsToSend);
//    calling setter to set orderEffect
    string effect = to_string(*this->unitsToSend) + " troops are deployed to " + *this->targetName + ". There are now " +
                    to_string(this->targetTerritory->getNoOfArmies()) + " armies.";
    this->setOrderEffect(new string(effect));
//    calling setters to influence friend operator
    this->setExecutable(boolean);
};





//////////////////////////////    ADVANCE    //////////////////////////////
///// CONSTRUCTORS
Advance::Advance(int* unitsToSend, string* targetName, string* sourceName, Player* player) : Order(new string("ADVANCE")) {
//    call parent constructor using order type "Advance"
//    set parameters in attributes
    this->setPlayer(player);
    this->setUnitsAtStart(new int(0));
    this->setUnitsToSend(unitsToSend);
    this->setTargetName(targetName);
    this->setSourceName(sourceName);
    this->setTargetTerritory(NULL);
    this->setSourceTerritory(NULL);
};

Advance::Advance(Advance* advance) : Order(advance) {
    this->setUnitsAtStart(new int(advance->getUnitsAtStart()));
    this->setUnitsToSend(new int(advance->getUnitsToSend()));
    this->setTargetName(advance->getTargetName());
    this->setSourceName(advance->getSourceName());
    this->setTargetTerritory(advance->getTargetTerritory());
    this->setSourceTerritory(advance->getSourceTerritory());
};

///// DESTRUCTOR
Advance::~Advance() {
    delete this->unitsAtStart;
    delete this->unitsToSend;
    delete this->targetName;
    delete this->sourceName;
    delete this->targetTerritory;
    delete this->sourceTerritory;
    this->unitsAtStart = nullptr;
    this->unitsToSend = nullptr;
    this->targetName = nullptr;
    this->sourceName = nullptr;
    this->targetTerritory = nullptr;
    this->sourceTerritory = nullptr;
};

///// GETTERS
int Advance::getUnitsAtStart() {
    return *this->unitsAtStart;
};

int Advance::getUnitsToSend() {
    return *this->unitsToSend;
};

string* Advance::getTargetName() {
    return this->targetName;
};

string* Advance::getSourceName() {
    return this->sourceName;
};

Territory* Advance::getTargetTerritory() {
    return this->targetTerritory;
};

Territory* Advance::getSourceTerritory() {
    return this->sourceTerritory;
};

///// SETTERS
void Advance::setUnitsAtStart(int* unitsAtStart) {
    this->unitsAtStart = unitsAtStart;
};

void Advance::setUnitsToSend(int* unitsToSend) {
    this->unitsToSend = unitsToSend;
};

void Advance::setTargetName(string* targetName) {
    this->targetName = targetName;
};

void Advance::setSourceName(string* sourceName) {
    this->sourceName = sourceName;
};

void Advance::setTargetTerritory(Territory* targetTerritory) {
    this->targetTerritory = targetTerritory;
};

void Advance::setSourceTerritory(Territory* sourceTerritory) {
    this->sourceTerritory = sourceTerritory;
};

///// METHODS
bool* Advance::equals(Order* order) {
//    if the two orders have similar attributes, return true
    if(
            this->getOrderName()->compare(*((Advance*)order)->getOrderName()) == 0 &&
            this->getPlayer()->getName()->compare(*((Advance*)order)->getPlayer()->getName()) == 0 &&
            *this->unitsAtStart == ((Advance*)order)->getUnitsAtStart() &&
            *this->unitsToSend == ((Advance*)order)->getUnitsToSend() &&
            this->targetName->compare(*((Advance*)order)->getTargetName()) == 0 &&
            this->sourceName->compare(*((Advance*)order)->getTargetName()) == 0
            ) {
        return new bool(true);
    }
//    else, return false
    return new bool(false);
};

bool* Advance::validate() {
//    get list of player's owned territories
    vector<Territory*> playerTerritories = this->player->getTerritories();
//    parse through playerTerritories
    for(int i = 0; i < playerTerritories.size(); i++) {
//        if sourceName is found, update necessary attributes and break
        if(playerTerritories[i]->getTerritoryName().compare(*this->sourceName) == 0) {
//            set conditional attributes
            this->sourceTerritory = playerTerritories[i];
            *this->unitsAtStart = playerTerritories[i]->getNoOfArmies();
            break;
        }
    }
//    if sourceTerritory was not updated, return false
    if(this->sourceTerritory == NULL) {
        return new bool(false);
    }
//    order invalid if there are insufficient units to send
    if(*this->unitsToSend < 0 || *this->unitsAtStart < *this->unitsToSend) {
        return new bool(false);
    }
//    get list of sourceTerritory's adjacent territories
    vector<Territory*> adjacentTerritories = this->sourceTerritory->getAdjacentTerritories();
//    parse through adjacentTerritories
    for(int i = 0; i < adjacentTerritories.size(); i++) {
//        if targetName is found, update necessary attributes and break
        if(adjacentTerritories[i]->getTerritoryName().compare(*this->targetName) == 0) {
            this->targetTerritory = adjacentTerritories[i];
            break;
        }
    }
//    if targetTerritory was not updated, return false
    if(this->targetTerritory == NULL) {
        return new bool(false);
    }
//    if player has a negotiation with the targetTerritory's player, return false
    vector<Player*> playerNegotiations = this->player->getNegotiations();
    for(int i = 0; i < playerNegotiations.size(); i++) {
        if(playerNegotiations[i]->getName()->compare(*this->targetTerritory->getPlayer()->getName()) == 0) {
            return new bool(false);
        }
    }
//    else, return false
    return new bool(true);
};

void Advance::execute() {
//    call validate to see if Order is executable
    bool* boolean = this->validate();
//    if statement to verify if the order was valid
    if(!*boolean) {
        return;
    }
//    if player owns both targetTerritory and sourceTerritory, add unitsToSend to targetTerritory
    if(this->player->getName()->compare(*this->targetTerritory->getPlayer()->getName()) == 0) {
        this->targetTerritory->setNoOfArmies(this->targetTerritory->getNoOfArmies() + *this->unitsToSend);
    }
//    else, update number of armies in targetTerritory and sourceTerritory
    else {
        int sourceArmies = this->sourceTerritory->getNoOfArmies();
        int targetArmies = this->targetTerritory->getNoOfArmies();
        this->targetTerritory->setNoOfArmies(this->targetTerritory->getNoOfArmies() - (sourceArmies * 0.6));
        this->sourceTerritory->setNoOfArmies(this->sourceTerritory->getNoOfArmies() - (targetArmies * 0.7));
    }
//    if there are no more enemy armies in targetTerritory, update its number of armies, its player, and the player's territories
    if(this->targetTerritory->getNoOfArmies() <= 0) {
        this->targetTerritory->setNoOfArmies(this->sourceTerritory->getNoOfArmies());
        this->targetTerritory->setPlayer(this->player);
        vector<Territory*> oldOwnerTerritories = this->targetTerritory->getPlayer()->getTerritories();
        for(int i = 0; i < oldOwnerTerritories.size(); i++) {
            if(oldOwnerTerritories[i]->getTerritoryName().compare(*targetName) == 0) {
                oldOwnerTerritories.erase(oldOwnerTerritories.begin() + i, oldOwnerTerritories.begin() + i + 1);
                break;
            }
        }
        this->targetTerritory->getPlayer()->setTerritories(oldOwnerTerritories);
        vector<Territory*> newOwnerTerritories = this->player->getTerritories();
        newOwnerTerritories.push_back(this->targetTerritory);
        this->player->setTerritories(newOwnerTerritories);
//        if player has not yet received a card, give player a card and update receivedCard
        if(!this->player->getReceivedCard()) {
            Card* card = deck->draw();
            Hand* playerHand = this->player->getHand();
            playerHand->addToHand(card);
            this->player->setHand(playerHand);
            this->player->setReceivedCard(new bool(true));
        }
    }
//    calling setter to set orderEffect
    string effect = to_string(*this->unitsToSend) + " troops advanced to " + *this->targetName + ". " + *this->targetTerritory->getPlayer()->getName() + " owns the targeted territory with " +
                    to_string(this->targetTerritory->getNoOfArmies()) + " armies.";
    this->setOrderEffect(new string(effect));
//    calling setters to influence friend operator
    this->setExecutable(boolean);
};





//////////////////////////////    BOMB    //////////////////////////////
///// CONSTRUCTORS
Bomb::Bomb(string* targetName, Player* player) : Order(new string("BOMB")) {
//    call parent constructor using order type "bomb"
//    set parameters in attributes
    this->setPlayer(player);
    this->setTargetName(targetName);
    this->setTargetTerritory(NULL);
};

Bomb::Bomb(Bomb* bomb) : Order(bomb) {
    this->setTargetName(bomb->getTargetName());
    this->setTargetTerritory(bomb->getTargetTerritory());
};

///// DESTRUCTOR
Bomb::~Bomb() {
    delete this->targetName;
    delete this->targetTerritory;
    this->targetName = nullptr;
    this->targetTerritory = nullptr;
};

///// GETTERS
string* Bomb::getTargetName() {
    return this->targetName;
};

Territory* Bomb::getTargetTerritory() {
    return this->targetTerritory;
};

///// SETTERS
void Bomb::setTargetName(string* targetName) {
    this->targetName = targetName;
};

void Bomb::setTargetTerritory(Territory* targetTerritory) {
    this->targetTerritory = targetTerritory;
};

///// METHODS
bool* Bomb::equals(Order* order) {
//    if the two orders have similar attributes, return true
    if(
            this->getOrderName()->compare(*((Bomb*)order)->getOrderName()) == 0 &&
            this->getPlayer()->getName()->compare(*((Bomb*)order)->getPlayer()->getName()) == 0 &&
            this->targetName->compare(*((Bomb*)order)->getTargetName()) == 0
            ) {
        return new bool(true);
    }
//    else, return false
    return new bool(false);
};

bool* Bomb::validate() {
//    get list of player's owned territories
    vector<Territory*> playerTerritories = this->player->getTerritories();
//    parse through playerTerritories
    for(int i = 0; i < playerTerritories.size(); i++) {
//        if targetTerritory is found, break
        if(this->targetTerritory != NULL) {
            break;
        }
//        get list of territories adjacent to current player's territory
        vector<Territory*> playerAdjacents = playerTerritories[i]->getAdjacentTerritories();
//        parse through playerAdjacents
        for(int j = 0; j < playerAdjacents.size(); j++) {
//            if targetName is found, update necessary attributes and return true
            if(playerAdjacents[j]->getTerritoryName().compare(*this->targetName) == 0) {
                this->targetTerritory = playerAdjacents[j];
                break;
            }
        }
    }
//    if targetTerritory is not found, return false
    if(this->targetTerritory == NULL) {
        return new bool(false);
    }
//    if player owns targetTerritory, return false
    if(this->targetTerritory->getPlayer()->getName()->compare(*this->player->getName()) == 0) {
        return new bool(false);
    }
//    if player has a negotiation with the targetTerritory's player, return false
    vector<Player*> playerNegotiations = this->player->getNegotiations();
    for(int i = 0; i < playerNegotiations.size(); i++) {
        if(playerNegotiations[i]->getName()->compare(*this->targetTerritory->getPlayer()->getName()) == 0) {
            return new bool(false);
        }
    }
//    get list of player's owned cards
    vector<Card*> playerCards = this->player->getHand()->getCards();
//    parse through playerCards
    for(int i = 0; i < playerCards.size(); i++) {
//        if bomb card is found, return true
        if(playerCards[i]->getCardName()->compare(*new string("BOMB")) == 0) {
            return new bool(true);
        }
    }
//    else, return false
    return new bool(false);
};

void Bomb::execute() {
//    call validate to see if Order is executable
    bool* boolean = this->validate();
//    if statement to verify if the order was valid
    if(!*boolean) {
        return;
    }
//    update targetTerritory's number of armies using the getter and setter methods
    this->targetTerritory->setNoOfArmies(this->targetTerritory->getNoOfArmies() / 2);
//    calling setter to set orderEffect
    string effect = *this->targetName + " was bombed. There remains " + to_string(this->targetTerritory->getNoOfArmies()) + " armies.";
    this->setOrderEffect(new string(effect));
//    calling setters to influence friend operator
    this->setExecutable(boolean);
};





//////////////////////////////    BLOCKADE    //////////////////////////////
///// CONSTRUCTORS
Blockade::Blockade(string* targetName, Player* player) : Order(new string("BLOCKADE")) {
//    call parent constructor using order type "blockade"
//    set parameters in attributes
    this->setPlayer(player);
    this->setTargetName(targetName);
};

Blockade::Blockade(Blockade* blockade) : Order(blockade) {
    this->setTargetName(blockade->getTargetName());
    this->setTargetTerritory(blockade->getTargetTerritory());
};

///// DESTRUCTOR
Blockade::~Blockade() {
    delete this->targetName;
    delete this->targetTerritory;
    this->targetName = nullptr;
    this->targetTerritory = nullptr;
};

///// GETTERS
string* Blockade::getTargetName() {
    return this->targetName;
};

Territory* Blockade::getTargetTerritory() {
    return this->targetTerritory;
};

///// SETTERS
void Blockade::setTargetName(string* targetName) {
    this->targetName = targetName;
};

void Blockade::setTargetTerritory(Territory* targetTerritory) {
    this->targetTerritory = targetTerritory;
};

///// METHODS
bool* Blockade::equals(Order* order) {
//    if the two orders have similar attributes, return true
    if(
            this->getOrderName()->compare(*((Blockade*)order)->getOrderName()) == 0 &&
            this->getPlayer()->getName()->compare(*((Blockade*)order)->getPlayer()->getName()) == 0 &&
            this->targetName->compare(*((Deploy*)order)->getTargetName()) == 0
            ) {
        return new bool(true);
    }
//    else, return false
    return new bool(false);
};

bool* Blockade::validate() {
//    get list of player's owned territories
    vector<Territory*> playerTerritories = this->player->getTerritories();
//    parse through playerTerritories
    for(int i = 0; i < playerTerritories.size(); i++) {
//        if targetName is found, update necessary attributes and return true
        if(playerTerritories[i]->getTerritoryName().compare(*this->targetName) == 0) {
            this->targetTerritory = playerTerritories[i];
            return new bool(true);
        }
    }
//    else, return false
    return new bool(false);
};

void Blockade::execute() {
//    call validate to see if Order is executable
    bool* boolean = this->validate();
//    if statement to verify if the order was valid
    if(!*boolean) {
        return;
    }
//    update targetTerritory's number of armies using the getter and setter methods
    this->targetTerritory->setNoOfArmies(this->targetTerritory->getNoOfArmies() * 2);
//    update targetTerritory's player using the setter method
    this->targetTerritory->setPlayer(playerN);

    vector<Territory*> oldOwnerTerritories = this->player->getTerritories();
    for(int i = 0; i < oldOwnerTerritories.size(); i++) {
        if(oldOwnerTerritories[i]->getTerritoryName().compare(*targetName) == 0) {
            oldOwnerTerritories.erase(oldOwnerTerritories.begin() + i, oldOwnerTerritories.begin() + i + 1);
            break;
        }
    }
    this->player->setTerritories(oldOwnerTerritories);
//    calling setter to set orderEffect
    string effect = "A blockade was formed on " + *this->targetName + " with " + to_string(this->targetTerritory->getNoOfArmies()) + " armies.";
    this->setOrderEffect(new string(effect));
//    calling setters to influence friend operator
    this->setExecutable(boolean);
};





//////////////////////////////    AIRLIFT    //////////////////////////////
///// CONSTRUCTORS
Airlift::Airlift(int* unitsToSend, string* targetName, string* sourceName, Player* player) : Order(new string("AIRLIFT")) {
//    call parent constructor using order type "airlift"
//    set parameters in attributes
    this->setPlayer(player);
    this->setUnitsAtStart(this->player->getReinforcements());
    this->setUnitsToSend(unitsToSend);
    this->setTargetName(targetName);
    this->setSourceName(sourceName);
    this->setTargetTerritory(NULL);
    this->setSourceTerritory(NULL);
};

Airlift::Airlift(Airlift* airlift) : Order(airlift) {
    this->setUnitsAtStart(new int(airlift->getUnitsAtStart()));
    this->setUnitsToSend(new int(airlift->getUnitsToSend()));
    this->setTargetName(airlift->getTargetName());
    this->setSourceName(airlift->getSourceName());
    this->setTargetTerritory(airlift->getTargetTerritory());
    this->setSourceTerritory(airlift->getSourceTerritory());
};

///// DESTRUCTOR
Airlift::~Airlift() {
    delete this->unitsAtStart;
    delete this->unitsToSend;
    delete this->targetName;
    delete this->sourceName;
    delete this->targetTerritory;
    delete this->sourceTerritory;
    this->unitsAtStart = nullptr;
    this->unitsToSend = nullptr;
    this->targetName = nullptr;
    this->sourceName = nullptr;
    this->targetTerritory = nullptr;
    this->sourceTerritory = nullptr;
};

///// GETTERS
int Airlift::getUnitsAtStart() {
    return *this->unitsAtStart;
};

int Airlift::getUnitsToSend() {
    return *this->unitsToSend;
};

string* Airlift::getTargetName() {
    return this->targetName;
};

string* Airlift::getSourceName() {
    return this->sourceName;
};

Territory* Airlift::getTargetTerritory() {
    return this->targetTerritory;
};

Territory* Airlift::getSourceTerritory() {
    return this->sourceTerritory;
};

///// SETTERS
void Airlift::setUnitsAtStart(int* unitsAtStart) {
    this->unitsAtStart = unitsAtStart;
};

void Airlift::setUnitsToSend(int* unitsToSend) {
    this->unitsToSend = unitsToSend;
};

void Airlift::setTargetName(string* targetName) {
    this->targetName = targetName;
};

void Airlift::setSourceName(string* sourceName) {
    this->sourceName = sourceName;
};

void Airlift::setTargetTerritory(Territory* targetTerritory) {
    this->targetTerritory = targetTerritory;
};

void Airlift::setSourceTerritory(Territory* sourceTerritory) {
    this->sourceTerritory = sourceTerritory;
};

///// METHODS
bool* Airlift::equals(Order* order) {
//    if the two orders have similar attributes, return true
    if(
            this->getOrderName()->compare(*((Airlift*)order)->getOrderName()) == 0 &&
            this->getPlayer()->getName()->compare(*((Airlift*)order)->getPlayer()->getName()) == 0 &&
            *this->unitsAtStart == ((Airlift*)order)->getUnitsAtStart() &&
            *this->unitsToSend == ((Airlift*)order)->getUnitsToSend() &&
            this->targetName->compare(*((Airlift*)order)->getTargetName()) == 0 &&
            this->sourceName->compare(*((Airlift*)order)->getSourceName()) == 0
            ) {
        return new bool(true);
    }
//    else, return false
    return new bool(false);
};

bool* Airlift::validate() {
//    order invalid if there are insufficient units to send
    if(*this->unitsToSend < 0 || *this->unitsAtStart < *this->unitsToSend) {
        return new bool(false);
    }
//    set integer values to check if targetName and sourceName were found in player's owned territories
    int targetFound = 0;
    int sourceFound = 0;
//    get list of player's owned territories
    vector<Territory*> playerTerritories = this->player->getTerritories();
//    parse through playerTerritories
    for(int i = 0; i < playerTerritories.size(); i++) {
//        if targetName is found, update necessary attributes and return true
        if(playerTerritories[i]->getTerritoryName().compare(*this->targetName) == 0) {
//            set conditional attributes
            this->targetTerritory = playerTerritories[i];
            targetFound = 1;
        }
//        if sourceName is found, update necessary attributes and return true
        if(playerTerritories[i]->getTerritoryName().compare(*this->sourceName) == 0) {
//            set conditional attributes
            this->sourceTerritory = playerTerritories[i];
            sourceFound = 1;
        }
        if(targetFound == 1 && sourceFound == 1) {
            return new bool(true);
        }
    }
//    else, return false
    return new bool(false);
};

void Airlift::execute() {
//    call validate to see if Order is executable
    bool* boolean = this->validate();
//    if statement to verify if the order was valid
    if(!*boolean) {
        return;
    }
//    update targetTerritory's number of armies using the getter and setter methods
    this->targetTerritory->setNoOfArmies(this->targetTerritory->getNoOfArmies() + *this->unitsToSend);
//    calling setter to set orderEffect
    string effect = to_string(*this->unitsToSend) + " armies were airlifted to " + *this->targetName + ". There are now " +
                    to_string(this->targetTerritory->getNoOfArmies()) + " armies.";
    this->setOrderEffect(new string(effect));
//    calling setters to influence friend operator
    this->setExecutable(boolean);
};





//////////////////////////////    NEGOTIATE    //////////////////////////////
///// CONSTRUCTORS
Negotiate::Negotiate(string* targetName, Player* player) : Order(new string("NEGOTIATE")) {
//    call parent constructor using order type "negotiate"
//    set parameters in attributes
    this->setPlayer(player);
    this->setTargetName(targetName);
};

Negotiate::Negotiate(Negotiate* negotiate) : Order(negotiate) {
    this->setTargetName(negotiate->getTargetName());
    this->setTargetPlayer(negotiate->getTargetPlayer());
}

///// DESTRUCTOR
Negotiate::~Negotiate() {
    delete this->targetName;
    delete this->targetPlayer;
    this->targetName = nullptr;
    this->targetPlayer = nullptr;
};

///// GETTERS
string* Negotiate::getTargetName() {
    return this->targetName;
};

Player* Negotiate::getTargetPlayer() {
    return this->targetPlayer;
};

///// SETTERS
void Negotiate::setTargetName(string* targetName) {
    this->targetName = targetName;
};

void Negotiate::setTargetPlayer(Player* targetPlayer) {
    this->targetPlayer = targetPlayer;
};

///// METHODS
bool* Negotiate::equals(Order* order) {
//    if the two orders have similar attributes, return true
    if(
            this->getOrderName()->compare(*((Negotiate*)order)->getOrderName()) == 0 &&
            this->getPlayer()->getName()->compare(*((Negotiate*)order)->getPlayer()->getName()) == 0 &&
            this->targetName->compare(*((Negotiate*)order)->getTargetName()) == 0
            ) {
        return new bool(true);
    }
//    else, return false
    return new bool(false);
};

bool* Negotiate::validate() {
//    order is invalid if negotiation happens with the same person or with the neutral player
    if(this->player->getName()->compare(*this->targetName) == 0) {
        return new bool(false);
    }
    if(this->targetName->compare("Neutral") == 0) {
        return new bool(false);
    }
//    get list of player's negotiations
    vector<Player*> issuerNegotiations = this->player->getNegotiations();
//    parse through issuerNegotiations
    for(int i = 0; i < issuerNegotiations.size(); i++) {
//        if targetName is found, return false
        if(issuerNegotiations[i]->getName()->compare(*this->targetName) == 0) {
            return new bool(false);
        }
    }
//    create otherPlayer to use for manipulation
    Player* otherPlayer = NULL;
//    parse through players
    for(int i = 0; i < players.size(); i++) {
//        if targetName is found, update otherPlayer
        if(players[i]->getName()->compare(*this->targetName) == 0) {
            otherPlayer = players[i];
        }
    }
//    if otherPlayer was not updated, return false
    if(otherPlayer == NULL) {
        return new bool(false);
    }
//    else, update player negotiation lists and return true
    issuerNegotiations.push_back(otherPlayer);
    this->player->setNegotiations(issuerNegotiations);
    vector<Player*> otherNegotiations = otherPlayer->getNegotiations();
    otherNegotiations.push_back(this->player);
    otherPlayer->setNegotiations(otherNegotiations);
    return new bool(true);
};

void Negotiate::execute() {
//    call validate to see if Order is executable
    bool* boolean = this->validate();
//    if statement to verify if the order was valid
    if(!*boolean) {
        return;
    }
//    calling setters to influence friend operator
    this->setExecutable(boolean);
    this->setOrderEffect(new string("A negotiation was set in place with " + *this->targetName + "."));
};





//////////////////////////////    ORDERSLISTS    //////////////////////////////
///// CONSTRUCTORS
OrdersLists::OrdersLists() {};

OrdersLists::OrdersLists(OrdersLists* list) {
//    call the OrdersLists getter and push each Order into orders by calling the copy constructor
    for(Order* order : list->getOrders()) {
        this->orders.push_back(Order::createSubtype(order));
    }
};

///// DESTRUCTOR
OrdersLists::~OrdersLists() {
    delete &this->orders;
};

///// GETTERS
vector<Order*> OrdersLists::getOrders()  {
    return this->orders;
};

int OrdersLists::getListSize() {
    return orders.size();
}

///// SETTER
void OrdersLists::setOrders(vector<Order*> orders) {
    this->orders = orders;
};

///// METHODS
void OrdersLists::add(Order* order) {
//    push order to list
    this->orders.push_back(order);
};

void OrdersLists::remove(int index) {
//    if index is out of bounds, return
    if(index >= this->orders.size() || index < 0) {
        return;
    }
//    else, erase the order at position index
    this->orders.erase(this->orders.begin() + index);
};

void OrdersLists::remove(Order* order) {
//    create int to use for manipulation
    int index = -1;
//    parse through orders
    for(int i = 0; i < this->getListSize(); i++) {
//        if order is found, update index and break
        if(order->equals(order)) {
            index = i;
            break;
        }
    }
//    if index was updated, remove the element at that index
    if(index != -1) {
        this->remove(index);
    }
};

void OrdersLists::move(int fromIndex, int toIndex) {
//    if fromIndex or toIndex are out of bounds, return
    if(fromIndex >= this->orders.size() || fromIndex < 0) {
        return;
    }
    if(toIndex >= this->orders.size() || toIndex < 0) {
        return;
    }
//    create pointer to use for manipulation
    Order* order;
//    if fromIndex and toIndex are equal, return
    if(fromIndex == toIndex) {
        return;
    }
//    else, insert the order at the toIndex
    order = this->orders[fromIndex];
    this->remove(fromIndex);
    this->orders.insert(this->orders.begin() + toIndex, Order::createSubtype(order));
};

void OrdersLists::execute() {
//    print header
    cout << "======= ORDERS NOW EXECUTING =======" << endl << endl;
//    call execute on and print each Order of orders
    for(Order* o : this->orders) {
        o->execute();
        cout << *o;
    }
//    print footer
    cout << "===== ORDERS FINISHED EXECUTING =====" << endl << endl << endl << endl << endl;
}





//////////////////////////////    FRIENDS    //////////////////////////////
ostream & operator << (ostream &out, Order &order) {
//    cout statement for executable orders
    if(*order.executable) {
        out << "ORDER " << *order.getOrderName() << " EXECUTED SUCCESSFULLY" << endl
            << "Order Issuer: " << *order.getPlayer()->getName() << endl
            << "Effect: " << *order.getOrderEffect() << endl << endl;
    }
//    cout statement for non-executable orders
    else {
        out << "ORDER " << *order.getOrderName() << " EXECUTED UNSUCCESSFULLY" << endl << endl;
    }
//    return statement
    return out;
};