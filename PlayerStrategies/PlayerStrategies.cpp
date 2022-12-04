#include "PlayerStrategies.h"
#include <iostream>
using namespace std;

//----------------OVERLOADING INSERTION STREAM OPERATORS------------------
ostream &operator << (ostream &output, PlayerStrategy &obj){
    output << "Player strategy is being utilized." << endl;
    return output;
};
ostream &operator<<(ostream &out, const HumanPlayerStrategy &human){
    out << "Human Player Strategy is being utilized." << endl;
    return out;
};
ostream &operator<<(ostream &out, const AggressivePlayerStrategy &aggressive){
    out << "Aggressive Player Strategy is being utilized." << endl;
    return out;
};
ostream &operator<<(ostream &out, const BenevolentPlayerStrategy &benevolent){
    out << "Benevolent Player Strategy is being utilized." << endl;
    return out;
};
ostream &operator<<(ostream &out, const NeutralPlayerStrategy &neutral){
    out << "Neutral Player Strategy is being utilized." << endl;
    return out;
};
ostream &operator<<(ostream &out, const CheaterPlayerStrategy &cheater){
    out << "Cheater Player Strategy is being utilized." << endl;
    return out;
};


//===================PLAYER STRATEGY===========================
//-----------OVERLOADING ASSIGNMENT OPERATORS---------
PlayerStrategy&PlayerStrategy::operator=(const PlayerStrategy &player){
        this->p = player.p;
};
//---------------------CONSTRUCTORS--------------------
PlayerStrategy::PlayerStrategy() {

}
PlayerStrategy::PlayerStrategy(Player *player) {
    this->setPlayer(player);
}
//-------------------COPY CONSTRUCTOR--------------------
PlayerStrategy::PlayerStrategy(PlayerStrategy &playerstrat){
    this->p = playerstrat.p;
};
//---------------------DESTRUCTORS-----------------------
PlayerStrategy::~PlayerStrategy() {
    delete p;
    p = nullptr;
}
//---------------------PLAYER METHODS-------------------------
Player *PlayerStrategy::getPlayer() {
    return this->p;
}

void PlayerStrategy::setPlayer(Player *player) {
    this->p = player;
}


//======================HUMAN STRATEGY =================================
//-----------OVERLOADING ASSIGNMENT OPERATORS---------
HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &human){
    this->map = human.map;
};

//---------------------CONSTRUCTORS--------------------
HumanPlayerStrategy::HumanPlayerStrategy(){

}
HumanPlayerStrategy::HumanPlayerStrategy(Player* player, Map* map){
    this->setPlayer(player);
    player->setPlayerStrategy(this);
    this->map = map;
}
//-------------------COPY CONSTRUCTOR--------------------
HumanPlayerStrategy::HumanPlayerStrategy(HumanPlayerStrategy &humanstrat){
    this->setPlayer(humanstrat.getPlayer());
    this->map = humanstrat.map;
};
//---------------------DESTRUCTORS-----------------------
HumanPlayerStrategy::~HumanPlayerStrategy() {
    delete map;
    map = nullptr;
}
//---------------------HUMAN PLAYER METHODS-------------------------
vector<Order*> HumanPlayerStrategy::issueOrder() {
    vector<Order*> humanOrders;
    vector<int> localTroops;
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        localTroops.push_back(this->getPlayer()->getTerritories()[i]->getNoOfArmies());
    }
    while(*this->getPlayer()->getReinforcements()>0) {
        cout << "You have: " << *this->getPlayer()->getReinforcements() << " reinforcements in your reinforcement pool"<< endl;
        cout << "Where would you like to deploy?" << endl;
        for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
            cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName() << endl;
        }
        Territory* territory = toDefend();
        string deployCountry = territory->getTerritoryName();
        cout<<"You've selected the territory: "<<deployCountry<<endl;
        cout<<"How many troops would you like to deploy?"<<" You have: "<<*this->getPlayer()->getReinforcements() << endl;
        int armiesToDeploy;
        cin>>armiesToDeploy;
        if (armiesToDeploy > *this->getPlayer()->getReinforcements()) {
            cout<< "You have selected the wrong number of troops. Please try again!" << endl;
        }
        else {
            int currentReinforcements = (*this->getPlayer()->getReinforcements())-armiesToDeploy;
            cout << "Your have ordered to DEPLOY " << armiesToDeploy << " onto " << deployCountry << endl;
            Order *deploy = new Deploy(&armiesToDeploy, &deployCountry, this->getPlayer());
            humanOrders.push_back(deploy);
            for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                if(this->getPlayer()->getTerritories()[i]->getTerritoryName() == deployCountry){
                    localTroops[i] += armiesToDeploy;
                }
            }
            this->getPlayer()->setReinforcements(currentReinforcements);
        }
    }
    bool hasOrders = true;
    while (hasOrders) {
        cout << "Please choose an option from the menu below: " << endl;
        cout << "1. Create an advance order " << endl;
        cout << "2. Play a card from your hand" << endl;
        cout << "3. End turn" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "These are your territories: " << endl;
                for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                    cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName() << endl;
                }
                Territory *sc = toDefend();
                string source = sc->getTerritoryName();
                cout << "These are the countries adjacent to the selected source that you can attack/defend: " << endl;
                for (int i = 0; i < sc->getAdjacentTerritories().size(); i++) {
                    cout << i + 1 << ". " << sc->getAdjacentTerritories()[i]->getTerritoryName();
                    if(sc->getAdjacentTerritories()[i]->getPlayerName() == *this->getPlayer()->getName()){
                        cout<<" (defend)"<<endl;
                    }
                    else{
                        cout<<" (attack)"<<endl;
                    }
                }
                cout << "Which country would you like to attack/defend?" << endl;
                int advanceChoice;
                cin>>advanceChoice;
                Territory* targetTerr;
                for (int i = 0; i < sc->getAdjacentTerritories().size(); ++i) {
                    if(advanceChoice==i+1){
                        targetTerr=sc->getAdjacentTerritories()[i];
                    }
                }
                string target = targetTerr->getTerritoryName();
                int noOfArmies;
                for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                    if(sc == this->getPlayer()->getTerritories()[i]){
                        noOfArmies = localTroops[i];
                    }
                }
                cout << "How many armies would you like to send. You have: " <<noOfArmies<< endl;
                int num;
                cin >> num;
                Order *advance = new Advance(&num, &target, &source, this->getPlayer());
                humanOrders.push_back(advance);
                cout << "Player: " << *this->getPlayer()->getName() << " has chosen to ADVANCE with " << num << " of their army units" <<endl;
                break;
            }

            case 2: {
                if (!this->getPlayer()->getHand()->getCardCount() == 0) {
                    cout << "Select one of the cards you have in your hand: " << endl;
                    for (int i = 0; i < this->getPlayer()->getHand()->getCardCount(); ++i) {
                        cout <<*this->getPlayer()->getHand()->getCards()[i]->getCardName() << endl;
                    }
                    string cardChoice;
                    cin >> cardChoice;
                    switch (cardChoice.size()) {
                        case 4: {
                            //BOMB
                            cout << "You've chosen to BOMB" << endl;
                            Territory *bombed = toAttack();
                            string bombTarget = bombed->getTerritoryName();
                            Order *bomb = new Bomb(&bombTarget, this->getPlayer());
                            humanOrders.push_back(bomb);
                            cout<<"Player: "<<*this->getPlayer()->getName()<<" has chosen to BOMB "<<bombTarget<<endl;
                            break;
                        }
                        case 7: {
                            //AIRLIFT
                            cout << "You have chosen to AIRLIFT"<< endl;
                            cout << "These are your territories: " << endl;
                            for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                                cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName()
                                     << endl;
                            }
                            Territory *t = toDefend();
                            string source = t->getTerritoryName();
                            cout << "You have selected: " << source
                                 << " as your source for the airlift, now please select your target destination"
                                 << endl;
                            for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                                if (this->getPlayer()->getTerritories()[i]->getTerritoryName() == source) {
                                    cout << "(source) ";
                                }
                                cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName()
                                     << endl;
                            }
                            string target;
                            cin >> target;
                            int noOfArmies;
                            bool airliftNum = true;
                            while (airliftNum) {
                                cout << "Your source territory: " << t->getTerritoryName() << " has "
                                     << t->getNoOfArmies()
                                     << " army units" << endl;
                                cout << "How many rmy units would you like to airlift?" << endl;
                                cin >> noOfArmies;
                                if (noOfArmies > t->getNoOfArmies() && noOfArmies < 0) {
                                    cout
                                            << "You have entered an invalid number of armies, please enter an appropriate amount."
                                            << endl;
                                } else {
                                    airliftNum = false;
                                }
                            }
                            Order *airlift = new Airlift(&noOfArmies, &target, &source, this->getPlayer());
                            humanOrders.push_back(airlift);
                            cout << "Player: " << *this->getPlayer()->getName() << " has chosen to AIRLIFT " << noOfArmies<<" to "<<target<< endl;
                            break;
                        }
                        case 8: {
                            //BLOCKADE
                            cout << "You have chosen to BLOCKADE"<< endl;
                            cout << "These are your territories: " << endl;
                            for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                                cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName()
                                     << endl;
                            }
                            cout << "Which territory would you like to block?" << endl;
                            string target;
                            cin >> target;
                            Order *blockade = new Blockade(&target, this->getPlayer());
                            humanOrders.push_back(blockade);
                            cout << "Player: " << *this->getPlayer()->getName() << " has chosen to BLOCKADE " << target << endl;
                            break;
                        }
                        case 9: {
                            //NEGOTIATE
                            //look through all territories adding all new players (that aren't the current player) to a vector of all player
                            cout << "You have chose to NEGOTIATE" << endl;
                            vector<Player*> enemyPlayers;
                            enemyPlayers.push_back(this->getPlayer());
                            for (int i = 0; i < map->getAllTerritories().size(); ++i) {
                                bool add = true;
                                for (int j = 0; j < enemyPlayers.size(); ++j) {
                                    if(*enemyPlayers[j]->getName() == map->getAllTerritories()[i]->getPlayerName() || map->getAllTerritories()[i]->getPlayerName()==*this->getPlayer()->getName()){
                                        add = false;
                                        break;
                                    }
                                }
                                if(add){
                                    enemyPlayers.push_back(map->getAllTerritories()[i]->getPlayer());
                                }
                            }
                            enemyPlayers.erase(enemyPlayers.begin());
                            cout<<"Choose a player to negotiate with: "<<endl;
                            for (int i = 0; i < enemyPlayers.size(); ++i) {
                                cout<<i+1<<". "<<*enemyPlayers[i]->getName()<<endl;
                            }
                            int playerNumChoice;
                            cin>>playerNumChoice;
                            Player* negotiatePartner;
                            for (int i = 0; i < enemyPlayers.size(); ++i) {
                                if(i+1 == playerNumChoice){
                                    negotiatePartner = enemyPlayers[i];
                                }
                            }
                            string negotiatePartnerName = *negotiatePartner->getName();
                            Order* negotiateOrder = new Negotiate(&negotiatePartnerName,this->getPlayer());
                            humanOrders.push_back(negotiateOrder);
                            cout<<"Player: "<< *this->getPlayer()->getName() <<" has chosen to NEGOTIATE with "<<negotiatePartnerName<<endl;
                            break;
                        }
                    }
                } else {
                    cout << "You don't have any cards!" << endl;
                }
                break;
            }
            case 3: {
                hasOrders = false;
                break;
            }

        }
    }
    return humanOrders;
}
Territory* HumanPlayerStrategy::toAttack() {
    cout << "What enemy territory would you like to bomb?" << endl;
    for (int i = 0; i < map->getAllTerritories().size(); ++i) {
        if(map->getAllTerritories()[i]->getPlayerName() != *this->getPlayer()->getName()){
            cout<<i+1<<". "<<map->getAllTerritories()[i]->getTerritoryName()<<endl;
        }
    }
    int bombTarget;
    cin>>bombTarget;
    Territory* t;
    for (int i = 0; i < map->getAllTerritories().size(); ++i) {
        if(map->getAllTerritories()[i]->getPlayerName() != *this->getPlayer()->getName()){
            if(bombTarget == i+1){
                t = map->getAllTerritories()[i];
            }
        }
    }
    return t;
}

Territory* HumanPlayerStrategy::toDefend() {
    int source;
    cout << "Please select the source territory." << endl;
    cin>>source;
    Territory* t = new Territory;
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        if (source == i+1){
            t=this->getPlayer()->getTerritories()[i];
        }
    }

    return t;
}


//======================AGGRESSIVE STRATEGY ======================
//---------------OVERLOADING ASSIGNMENT OPERATOR------
AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &aggressive){

};

//---------------------CONSTRUCTORS-------------------
AggressivePlayerStrategy::AggressivePlayerStrategy() {

}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) {
    this->setPlayer(player);
    player->setPlayerStrategy(this);
}

//----------------------COPY CONSTRUCTOR----------------------
AggressivePlayerStrategy::AggressivePlayerStrategy(AggressivePlayerStrategy &aggressivestrat){

};

//-----------------------DESTRUCTOR---------------------------
AggressivePlayerStrategy::~AggressivePlayerStrategy() {
}

//------------------AGGRESSIVE PLAYER METHODS-----------------
vector<Order*> AggressivePlayerStrategy::issueOrder() {
    vector<Order*> aggressiveOrders;
    Territory* strongestOwnedTerritory = toDefend();
    string* strongestTerritoryName = new string (strongestOwnedTerritory->getTerritoryName());
    int* allReinforcements = new int(*this->getPlayer()->getReinforcements());
    Order* deploy = new Deploy(allReinforcements, strongestTerritoryName, this->getPlayer());
    aggressiveOrders.push_back(deploy);
    cout<<"Player: "<<*this->getPlayer()->getName()<<" has ordered to DEPLOY "<<*allReinforcements<<" onto "<<*strongestTerritoryName<<" which already had "<<
        strongestOwnedTerritory->getNoOfArmies()<<" troops"<<endl;
    //this->getPlayer()->setReinforcements(0);
    Territory* weakestTargetTerritory = toAttack();
    string* weakestTerritoryName = new string(weakestTargetTerritory->getTerritoryName());
    //check if we have any aggressive cards (bomb)
    for (int i = 0; i < this->getPlayer()->getHand()->getCards().size(); ++i) {
        if(*this->getPlayer()->getHand()->getCards()[i]->getCardName() == "BOMB"){
            Order* bomb = new Bomb(weakestTerritoryName,this->getPlayer());
            aggressiveOrders.push_back(bomb);
            cout<<"Player: "<<*this->getPlayer()->getName()<<" has ordered to BOMB "<<*weakestTerritoryName<<" which only had "<<
                weakestTargetTerritory->getNoOfArmies()<<" troops"<<endl;
        }
    }
    int strongestNoOfArmies = strongestOwnedTerritory->getNoOfArmies() + *allReinforcements;//order to advance with current armies + reinforcement order needs to be checked when orders are executed
    int* strongestNoOfArmiesPtr = new int(strongestNoOfArmies);
    Order* advance = new Advance(strongestNoOfArmiesPtr,weakestTerritoryName,strongestTerritoryName,this->getPlayer());
    aggressiveOrders.push_back(advance);
    cout<<"Player: "<<*this->getPlayer()->getName()<<" has ordered to ADVANCE "<<strongestNoOfArmies<<" onto "<<*weakestTerritoryName<<" which only had "<<
        weakestTargetTerritory->getNoOfArmies()<<" troops"<<endl;
    return aggressiveOrders;
}

Territory* AggressivePlayerStrategy::toAttack() {
    //variable called terrritoryToAtk
    Territory* territory = this->toDefend();
    string toDefendResult = territory->getTerritoryName();
    Territory* territoryToAtk;
    //variable for min number of armies
    int minNumOfArmies = 999;
    string nameOfPlayer = territory->getPlayerName();
    //look at the adjacent ones to my strongestOwned
    for (int i = 0; i < territory->getAdjacentTerritories().size(); ++i) {
        if(minNumOfArmies>territory->getAdjacentTerritories()[i]->getNoOfArmies() && territory->getPlayerName() != territory->getAdjacentTerritories()[i]->getPlayerName()){
            minNumOfArmies = territory->getAdjacentTerritories()[i]->getNoOfArmies();
            territoryToAtk = territory->getAdjacentTerritories()[i];
        }
    }
    string toAttackResult = territoryToAtk->getTerritoryName();
    return territoryToAtk;
}
Territory* AggressivePlayerStrategy::toDefend() {
    //variable called strongestOwned
    Territory* strongestOwned;
    //variable with max number of armies, initially set to territory[0]
    int maxNumOfArmies = -1;
    //loop through all my owned territories
    //if bigger, set new max number and set new strongestOwned
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        if(this->getPlayer()->getTerritories()[i]->getNoOfArmies()>maxNumOfArmies
           && *this->getPlayer()->getName() == this->getPlayer()->getTerritories()[i]->getPlayerName()){
            for (int j = 0; j < this->getPlayer()->getTerritories()[i]->getAdjacentTerritories().size(); ++j) {
                if(this->getPlayer()->getTerritories()[i]->getPlayerName() != this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayerName()){
                    maxNumOfArmies = this->getPlayer()->getTerritories()[i]->getNoOfArmies();
                    strongestOwned = this->getPlayer()->getTerritories()[i];
                }
            }
        }
    }
    return strongestOwned;
}

//=====================BENEVOLENT STRATEGY=====================
//---------------OVERLOADING ASSIGNMENT OPERATOR------
BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &benevolent){

};

//---------------------CONSTRUCTORS-------------------
BenevolentPlayerStrategy::BenevolentPlayerStrategy() {

}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) {
    this->setPlayer(player);
    player->setPlayerStrategy(this);
}
//----------------------COPY CONSTRUCTOR----------------------
BenevolentPlayerStrategy::BenevolentPlayerStrategy(BenevolentPlayerStrategy & benevolentstrat){

};
//-----------------------DESTRUCTOR---------------------------
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {

}
//------------------BENEVOLENT PLAYER METHODS-----------------
vector<Order*> BenevolentPlayerStrategy::issueOrder() {
    vector<Order*> benevolentOrders;
    Territory* t = toDefend();
    string* territoryName = new string (t->getTerritoryName());
    int* noOfReinforcements = new int(*this->getPlayer()->getReinforcements());
    Order* benevolentDeploy = new Deploy(noOfReinforcements, territoryName, this->getPlayer());
    benevolentOrders.push_back(benevolentDeploy);
    cout<<"Player: "<<*this->getPlayer()->getName()<<" has ordered to DEPLOY "<<*noOfReinforcements<<" onto "<<*territoryName<<" which only had "<<t->getNoOfArmies()<<" troops"<<endl;
    //this->getPlayer()->setReinforcements(0);
    return benevolentOrders;
    //deploy armies to the weakest territory
    //call toDefend to find its weakest territory and deploy all reinforcement armies there
}
Territory* BenevolentPlayerStrategy::toAttack() {
    return nullptr;
} //void does not attack

Territory* BenevolentPlayerStrategy::toDefend() {
    //variable called weakestOwned
    Territory* weakestOwned = this->getPlayer()->getTerritories()[0];
    //variable with min number of armies, initially set to territory[0]
    int minNumOfArmies = this->getPlayer()->getTerritories()[0]->getNoOfArmies();
    //loop through all my owned territories
    //if bigger, set new max number and set new strongestOwned
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        if(this->getPlayer()->getTerritories()[i]->getNoOfArmies()<minNumOfArmies && *this->getPlayer()->getName() == this->getPlayer()->getTerritories()[i]->getPlayerName()){
            minNumOfArmies = this->getPlayer()->getTerritories()[i]->getNoOfArmies();
            weakestOwned = this->getPlayer()->getTerritories()[i];
        }
    }
    return weakestOwned;
}

//=====================NEUTRAL STRATEGY=====================
//---------------OVERLOADING ASSIGNMENT OPERATOR------
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &neutral){
    this->noOfTerritories = neutral.noOfTerritories;
};
//---------------------CONSTRUCTORS-------------------
NeutralPlayerStrategy::NeutralPlayerStrategy() {
    this->noOfTerritories = new int(0);
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) {
    this->setPlayer(player);
    player->setPlayerStrategy(this);
    this->noOfTerritories = new int(player->getTerritories().size());
}
//----------------------COPY CONSTRUCTOR----------------------
NeutralPlayerStrategy::NeutralPlayerStrategy(NeutralPlayerStrategy &neutralstrat){
    this->noOfTerritories = neutralstrat.noOfTerritories;
};

//-----------------------DESTRUCTOR---------------------------
NeutralPlayerStrategy::~NeutralPlayerStrategy() {
    delete noOfTerritories;
    noOfTerritories = nullptr;
}
//------------------NEUTRAL PLAYER METHODS-----------------
vector<Order*> NeutralPlayerStrategy::issueOrder() {
    //NEUTRAL
    vector<Order*> order;
    if(*this->noOfTerritories == 0){
        this->noOfTerritories = new int(this->getPlayer()->getTerritories().size());
    }
    if(this->getPlayer()->getTerritories().size() != *this->noOfTerritories){
        PlayerStrategy* ps = new AggressivePlayerStrategy(this->getPlayer());
        this->getPlayer()->setPlayerStrategy(ps);
        cout<<"Player: "<<*this->getPlayer()->getName()<<" has become enraged, they are now Aggressive (>_<)"<<endl;
    }
    return order;
}

Territory* NeutralPlayerStrategy::toAttack() {
    return nullptr;
}

Territory* NeutralPlayerStrategy::toDefend() {
    return nullptr;
}

//=====================CHEATER STRATEGY=====================
//---------------OVERLOADING ASSIGNMENT OPERATOR------
CheaterPlayerStrategy &CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy &cheater){
};
//---------------------CONSTRUCTORS-------------------
CheaterPlayerStrategy::CheaterPlayerStrategy() {

}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) {
    this->setPlayer(player);
    player->setPlayerStrategy(this);
}
//----------------------COPY CONSTRUCTOR----------------------
CheaterPlayerStrategy::CheaterPlayerStrategy(CheaterPlayerStrategy &cheater){
};
//-----------------------DESTRUCTOR---------------------------
CheaterPlayerStrategy::~CheaterPlayerStrategy() {

}
//------------------NEUTRAL PLAYER METHODS-----------------
vector<Order*> CheaterPlayerStrategy::issueOrder() {
//call toAttack to conquer all adjacent territories -> num of armies becomes his (ownership changes)
//cheater will go before anyone else in the orders
    vector<Order*> emptyOrders;
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        for (int j = 0; j < this->getPlayer()->getTerritories()[i]->getAdjacentTerritories().size(); ++j) {
            if(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayerName() != *this->getPlayer()->getName()){
                string name = *this->getPlayer()->getName();
                Territory* stolenTerritory = this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j];
                cout<<"Player: "<<name<<" has stolen "<<stolenTerritory->getTerritoryName()<<" from "<<stolenTerritory->getPlayerName()<<endl;
                this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayer()->removeTerritory(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]);
                this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->setPlayer(this->getPlayer());
                this->getPlayer()->addTerritory(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]);
                string name2 = *this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayer()->getName();
            }
        }
    }
    cout << "I DIDN'T CHEAT (~#_#) " <<endl;
    return emptyOrders;
}
Territory* CheaterPlayerStrategy::toAttack() {
    return nullptr;
}
Territory* CheaterPlayerStrategy::toDefend() {
    return nullptr;
}

