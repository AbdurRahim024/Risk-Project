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

string Player::getName() {
    return *this->name;
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


// OTHER

vector<Territory*> Player::toAttack(Territory* source) {
    vector<Territory*> attTerritories;
    for (int i = 0; i < source->getAdjacentTerritories().size(); ++i) {
        if (source->getAdjacentTerritories()[i]->getPlayerName() != source->getPlayerName()) {
            attTerritories.push_back(source->getAdjacentTerritories()[i]);
        }
    }
    return attTerritories;
}

vector<Territory*> Player::toDefend(Territory* source) {
    vector<Territory*> defTerritories;
    for (int i = 0; i < source->getAdjacentTerritories().size(); ++i) {
        if (source->getAdjacentTerritories()[i]->getPlayerName() == source->getPlayerName()) {
            defTerritories.push_back(source->getAdjacentTerritories()[i]);
        }
    }
    return defTerritories;
}

Order* Player::issueOrder(int orderNumber, Map* map) {
    Order *order = nullptr;
    if(orderNumber!=0 && *this->getReinforcements()!=0){
            cout << "You still have " << *this->getReinforcements() << " troops in the reinforcement pool \n";
            cout << "You must exhaust all of them before any other order is done!" << endl;
            return order;
    }
    vector<Territory*> ownTerritories;
    for(int i = 0; i<this->territories.size();i++){
        ownTerritories.push_back(this->territories[i]);
    }
    switch(orderNumber) {
        case 0: {
            //deploy order
            cout << "\n\n------------------ YOU CHOSE TO DEPLOY ARMIES -----------------" << endl;
            cout << "\nYou have: " << *this->getReinforcements() << " troops, please choose one of your territories to place them on!" << endl;
            for (int i = 0; i < ownTerritories.size(); ++i) {
                cout << i + 1  << ". " << ownTerritories[i]->getTerritoryName()<< "\n";
            }
            cout << "You have selected the territory: " << ownTerritories[0]->getTerritoryName()<< endl;
            int armiesToPlace = *this->getReinforcements();
            cout<< "Order has been created to send: " << armiesToPlace << " troops, to territory: " << ownTerritories[0]->getTerritoryName() << endl;
            this->setReinforcements(0);
            order = new Deploy();
            break;
        }
        case 1: {
            //advance order - to atk
            cout << "\n\n---------------- YOU CHOSE TO ADVANCE TO A TERRITORY ---------------------" << endl;
            cout << "\nSelect a source territory for your advance order: " << endl;
            for (int i = 0; i < ownTerritories.size(); ++i) {
                cout << i + 1 << ". " << ownTerritories[i]->getTerritoryName() << "\n";
            }
            cout << "\nYou chose: " << ownTerritories[0]->getTerritoryName() << endl;
            cout << "Would you like to attack or defend?" << " ATTACK" << endl;
            cout << "What territory would you like to attack?" << endl;
            vector<Territory *> toAtk = toAttack(ownTerritories[0]);
            for (int i = 0; i < toAtk.size(); ++i) {
                cout << i + 1 <<". " << toAtk[i]->getTerritoryName() << "\n";
            }
            cout << "\nYou have chosen to attack territory: " << toAtk[0]->getTerritoryName() << endl;
            cout << "Please enter the number of armies to be advanced: " << "8" << endl;
            cout << "Order has been created to advance: 8 army units from " << ownTerritories[0]->getTerritoryName()
                 << " to " << toAtk[0]->getTerritoryName() << endl;
            order = new Advance();
            break;
        }
        case 2: {
            //advance order - toDefend
            cout << "\n\n---------------- YOU CHOSE TO ADVANCE TO A TERRITORY ---------------------" << endl;
            cout << "\nSelect a source territory for your advance order: " << endl;
            for (int i = 0; i < ownTerritories.size(); ++i) {
                cout << i + 1 <<". " << ownTerritories[i]->getTerritoryName() << "\n";
            }
            cout << "\nYou chose: " << ownTerritories[1]->getTerritoryName() << endl;
            cout << "Would you like to attack or defend?" << " DEFEND" << endl;
            cout << "What territory would you like to defend?\n";
            vector<Territory *> toDef = toDefend(ownTerritories[1]);
            for (int i = 0; i < toDef.size(); ++i) {
                cout << i + 1 << ". " << toDef[i]->getTerritoryName() << "\n";
            }
            cout << "\nYou have chosen to defend territory: " << toDef[0]->getTerritoryName() << endl;
            cout << "Please enter the number of armies to be advanced: " << "5" << endl;
            cout << "Order has been created to advance: 5 army units from " << ownTerritories[1]->getTerritoryName()
                 << " to " << toDef[0]->getTerritoryName() << endl;
            order = new Advance();
            break;
        }
        case 3:{
            cout << "\n\n---------------- YOU CHOSE TO BOMB A TERRITORY ---------------------" << endl;
            cout << "\nSelect a territory you would like to Bomb: " << endl;
            vector<Territory*> enemyTerritories;
            int counter = 0;
            for (int i = 0; i < map->getAllTerritories().size(); ++i) {
                if(map->getAllTerritories()[i]->getPlayerName()!=this->getName()){
                    enemyTerritories.push_back(map->getAllTerritories()[i]);
                    cout << counter + 1 << ". " << enemyTerritories[counter]->getTerritoryName() << "\n";
                    counter++;
                }
            }
            cout << "\nYou have chosen to Bomb: "<< enemyTerritories[0]->getTerritoryName() << endl;
            cout << "Order has been created to Bomb: " << enemyTerritories[0]->getTerritoryName() << endl;
            order = new Bomb();
            break;
        }
    }
    return order;
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