#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

///////////////////////////////// PLAYER /////////////////////////////////////

// Setting static variables
int zero = 0;
int* Player::playerCount = &zero;


// CONSTRUCTOR
Player::Player(string* pName) {
    this->name = new string(*pName);

    // Use the player count as the player's id then increment the count
    this->id = new int(*playerCount);
    *playerCount += 1;

    this->hand = new Hand();
    this->orders = new OrdersLists;
    this->reinforcements = new int(0);

    this->receivedCard = new bool(false);

}

// COPY CONSTRUCTOR
Player::Player(const Player& copyPlayer) {
    cout << "Copy constructor of Player called" << endl;
    this->id = copyPlayer.id;
    this->name = copyPlayer.name;
    this->hand = copyPlayer.hand;
    this->deck = copyPlayer.deck;
    this->orders = copyPlayer.orders;
    this->territories = copyPlayer.territories;
    this->negotiations = copyPlayer.negotiations;
    this->receivedCard = copyPlayer.receivedCard;
}

// ASSIGNMENT OPERATOR
Player& Player::operator=(const Player& copyPlayer) {
    cout << "Copy assignment operator of Player" << endl;

    this->id = copyPlayer.id;
    this->name = copyPlayer.name;
    this->hand = copyPlayer.hand;
    this->deck = copyPlayer.deck;
    this->orders = copyPlayer.orders;
    this->territories = copyPlayer.territories;
    this->negotiations = copyPlayer.negotiations;
////receiveCard here?

    return *this;
}

// STREAM INSERTION OPERATOR
ostream &operator<<(ostream &out, const Player& p) {
    cout << "Player name: " << *p.name <<  endl;
    cout << "Player id: " << *p.id << endl;
    cout << *p.hand;

    if (p.orders->getListSize() == 0) {
        cout << "No orders yet" << endl;
    } else {
        cout << "Orders: " << endl;
        for(Order* order : p.orders->getOrders()) {
            cout << *order << endl;
        }
    }

    if (p.territories.empty()) {
        cout << "No territories yet" << endl;
    } else {
        cout << "Territories: " << endl;
        for(Territory* ter : p.territories) {
            cout << *ter << endl;
        }
    }

    cout << "" << endl;
    return out;
}

// GETTERS
int* Player::getId() {
    return id;
}

string* Player::getName() {
    return this->name;
}

Hand* Player::getHand() {
    return hand;
}

OrdersLists* Player::getOrders() {
    return orders;
}

vector<Territory*> Player::getTerritories() {
    return territories;
}
int* Player::getReinforcements(){
    return reinforcements;
}
vector<Player*> Player::getNegotiations() {
    return this->negotiations;
};

bool* Player::getReceivedCard() {
    return this->receivedCard;
};


// SETTERS

void Player::setId(int newId) {
    *id = newId;
}

void Player::setName(string* newName) {
    name = newName;
}

void Player::setHand(Hand* newHand) {
    hand = newHand;
}

void Player::setDeck(Deck *newDeck) {
    deck = newDeck;
}

void Player::setOrders(OrdersLists* newOrders) {
    orders = newOrders;
}

void Player::setTerritories(vector<Territory*> newTerritories) {
    territories = newTerritories;
}
void Player::setReinforcements(int noOfReinforcements) {
    reinforcements = new int(noOfReinforcements);
}


void Player::setNegotiations(vector<Player *> negotiations) {
    this->negotiations = negotiations;
};

void Player::setReceivedCard(bool* receivedCard) {
    this->receivedCard = receivedCard;
};


// OTHER

void Player::addTerritory(Territory* newTerr) {
    this->territories.push_back(newTerr);
}

//// The toAttack method returns the list of territories that can be attacked by the user
//vector<Territory*> Player::toAttack(Territory* source) {
//    vector<Territory*> attTerritories;
//    for (int i = 0; i < source->getAdjacentTerritories().size(); ++i) {
//        if (source->getAdjacentTerritories()[i]->getPlayerName() != source->getPlayerName()) {
//            attTerritories.push_back(source->getAdjacentTerritories()[i]);
//        }
//    }
//    return attTerritories;
//}
//
//
//// The toDefend method returns the list of territories that can be defended by the user
//vector<Territory*> Player::toDefend(Territory* source) {
//    vector<Territory*> defTerritories;
//    for (int i = 0; i < source->getAdjacentTerritories().size(); ++i) {
//        if (source->getAdjacentTerritories()[i]->getPlayerName() == source->getPlayerName()) {
//            defTerritories.push_back(source->getAdjacentTerritories()[i]);
//        }
//    }
//    return defTerritories;
//}


// The issue order method creates and returns an order with the help of toAttack and to Defend methods
vector<Order*> Player::issueOrder() {
    return this->ps->issueOrder();
}

void Player::removeTerritory(Territory* removeTerr) {
    vector<Territory*> territorySet;
    string sadas = removeTerr->getTerritoryName();
     for (int i = 0; i < this->territories.size(); ++i) {
        string gog = this->territories[i]->getTerritoryName();
        if(this->territories[i] != removeTerr){
            territorySet.push_back(this->territories[i]);
        }
    }    this->setTerritories(territorySet);
}

void Player::setPlayerStrategy(PlayerStrategy* playerStrategy){
    this->ps = playerStrategy;
}
PlayerStrategy* Player::getPlayerStrategy(){
    return this->ps;
}






Player::~Player() {
    delete id;
    id = nullptr;

    delete name;
    name = nullptr;

    delete hand;
    hand = nullptr;

    deck = nullptr;

    delete orders;
    orders = nullptr;

    for (Territory* ter : territories) {
        delete ter;
        ter = nullptr;
    }
}