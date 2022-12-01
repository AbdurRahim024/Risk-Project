#include "PlayerStrategies.h"
#include <iostream>
using namespace std;

//class LogObserver;
//LogObserver* Command::obs = NULL;
//LogObserver* CommandProcessor ::obs = NULL;

//----------------OVERLOADING INSERTION STREAM OPERATORS------------------


Player *PlayerStrategy::getPlayer() {
    return this->p;
}

void PlayerStrategy::setPlayer(Player *player) {
    this->p = player;
}

PlayerStrategy::PlayerStrategy() {

}
PlayerStrategy::PlayerStrategy(Player *player) {
    this->setPlayer(player);
}

PlayerStrategy::~PlayerStrategy() {

}


//HUMAN
HumanPlayerStrategy::HumanPlayerStrategy(){

}
HumanPlayerStrategy::HumanPlayerStrategy(Player* player, Map* map){
    this->setPlayer(player);
    this->map = map;
}
//HumanPlayerStrategy::~HumanPlayerStrategy() {
//
//}

vector<Order*> HumanPlayerStrategy::issueOrder() {
    vector<Order*> humanOrders;
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
            cout << "Your have ordered to deploy " << armiesToDeploy << " onto " << deployCountry << endl;
            Order *deploy = new Deploy(&armiesToDeploy, &deployCountry, this->getPlayer());
            humanOrders.push_back(deploy);
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
                cout << "How many armies would you like to send. You have: " <<sc->getNoOfArmies()<< endl;
                int num;
                cin >> num;
                Order *advance = new Advance(&num, &target, &source, this->getPlayer());
                humanOrders.push_back(advance);
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
                            cout << "You've chosen to " << cardChoice << endl;
                            Territory *bombed = toAttack();
                            string bombTarget = bombed->getTerritoryName();
                            Order *bomb = new Bomb(&bombTarget, this->getPlayer());
                            humanOrders.push_back(bomb);
                            break;
                        }
                        case 7: {
                            //AIRLIFT
                            cout << "You have chosen to " << cardChoice << endl;
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
                            break;
                        }
                        case 8: {
                            //BLOCKADE
                            cout << "You have chose to " << cardChoice << endl;
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
                            break;
                        }
                        case 9: {
                            //NEGOTIATE
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


//AGGRESSIVE
AggressivePlayerStrategy::AggressivePlayerStrategy() {

}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) {
    this->setPlayer(player);
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {

}

vector<Order*> AggressivePlayerStrategy::issueOrder() {
    vector<Order*> aggressiveOrders;
    Territory* strongestOwnedTerritory = toDefend();
    string strongestTerritoryName = strongestOwnedTerritory->getTerritoryName();
    int allReinforcements = *this->getPlayer()->getReinforcements();
    Order* deploy = new Deploy(&allReinforcements, &strongestTerritoryName, this->getPlayer());
    aggressiveOrders.push_back(deploy);
    this->getPlayer()->setReinforcements(0);
    Territory* weakestTargetTerritory = toAttack();
    string weakestTerritoryName = weakestTargetTerritory->getTerritoryName();
    //check if we have any aggressive cards (bomb)
    for (int i = 0; i < this->getPlayer()->getHand()->getCards().size(); ++i) {
        if(*this->getPlayer()->getHand()->getCards()[i]->getCardName() == "BOMB"){
            Order* bomb = new Bomb(&weakestTerritoryName,this->getPlayer());
            aggressiveOrders.push_back(bomb);
        }
    }
    int strongestNoOfArmies = strongestOwnedTerritory->getNoOfArmies() + allReinforcements; //order to advance with current armies + reinforcement order needs to be checked when orders are executed
    Order* advance = new Advance(&strongestNoOfArmies,&weakestTerritoryName,&strongestTerritoryName,this->getPlayer());
    aggressiveOrders.push_back(advance);
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
    Territory* strongestOwned = this->getPlayer()->getTerritories()[0];
    //variable with max number of armies, initially set to territory[0]
    int maxNumOfArmies = this->getPlayer()->getTerritories()[0]->getNoOfArmies();
    //loop through all my owned territories
    //if bigger, set new max number and set new strongestOwned
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        if(this->getPlayer()->getTerritories()[i]->getNoOfArmies()>maxNumOfArmies && *this->getPlayer()->getName() == this->getPlayer()->getTerritories()[i]->getPlayerName()){
            maxNumOfArmies = this->getPlayer()->getTerritories()[i]->getNoOfArmies();
            strongestOwned = this->getPlayer()->getTerritories()[i];
        }
    }
    return strongestOwned;
}

//BENEVOLENT
BenevolentPlayerStrategy::BenevolentPlayerStrategy() {

}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) {
    this->setPlayer(player);
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {

}
vector<Order*> BenevolentPlayerStrategy::issueOrder() {
    vector<Order*> benevolentOrders;
    Territory* t = toDefend();
    string territoryName = t->getTerritoryName();
    int noOfReinforcements = *this->getPlayer()->getReinforcements();
    Order* benevolentDeploy = new Deploy(&noOfReinforcements, &territoryName, this->getPlayer());
    benevolentOrders.push_back(benevolentDeploy);
    this->getPlayer()->setReinforcements(0);
    return benevolentOrders;
    //deploy armies to the weakest territory
    //call toDefend to find its weakest territory and deploy all reinforcement armies there
}
Territory* BenevolentPlayerStrategy::toAttack() {
    return nullptr;
} //void does not attack

Territory* BenevolentPlayerStrategy::toDefend() {
    //variable called weakestOwned
    Territory* weakestOwned = new Territory();
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

//NEUTRAL
NeutralPlayerStrategy::NeutralPlayerStrategy() {

}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) {
    this->setPlayer(player);
    this->noOfTerritories = new int(this->getPlayer()->getTerritories().size());
}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {

}

vector<Order*> NeutralPlayerStrategy::issueOrder() {
    //NEUTRAL
    vector<Order*> order;
    if(this->getPlayer()->getTerritories().size() != *this->noOfTerritories){
        PlayerStrategy* ps = new AggressivePlayerStrategy(this->getPlayer());
        this->getPlayer()->setPlayerStrategy(ps);
    }
    return order;
}

Territory* NeutralPlayerStrategy::toAttack() {
    return nullptr;
}

Territory* NeutralPlayerStrategy::toDefend() {
    return nullptr;
}

//Cheater
CheaterPlayerStrategy::CheaterPlayerStrategy() {

}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) {
    this->setPlayer(player);
}

CheaterPlayerStrategy::~CheaterPlayerStrategy() {

}

vector<Order*> CheaterPlayerStrategy::issueOrder() {
//call toAttack to conquer all adjacent territories -> num of armies becomes his (ownership changes)
//cheater will go before anyone else in the orders
    vector<Order*> emptyOrders;
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        for (int j = 0; j < this->getPlayer()->getTerritories()[i]->getAdjacentTerritories().size(); ++j) {
            if(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayerName() != *this->getPlayer()->getName()){
                string name = *this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayer()->getName();
                this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayer()->removeTerritory(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]);
                this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->setPlayer(this->getPlayer());
                this->getPlayer()->addTerritory(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]);
                //string playersName = *this->getPlayer()->getName();
                //this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->setPlayerName(playersName);
                string name2 = *this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayer()->getName();

            }
        }
    }

    return emptyOrders;
}
Territory* CheaterPlayerStrategy::toAttack() {
    return nullptr;
}
Territory* CheaterPlayerStrategy::toDefend() {
    return nullptr;
}

