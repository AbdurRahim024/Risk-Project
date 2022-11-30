#include "PlayerStrategies.h"
#include <iostream>
using namespace std;

class LogObserver;
LogObserver* Command::obs = NULL;
LogObserver* CommandProcessor ::obs = NULL;

//----------------OVERLOADING INSERTION STREAM OPERATORS------------------


Player *PlayerStrategy::getPlayer() {
    return this->p;
}

Player *PlayerStrategy::setPlayer(Player *player) {
    this->p = player;
}


//HUMAN
vector<Order*> HumanPlayerStrategy::issueOrder() {
    vector<Order*> humanOrders;
    while(*this->getPlayer()->getReinforcements()>0) {
        cout << "You have: " << *this->getPlayer()->getReinforcements() << " reinforcements in your reinforcement pool"
             << endl;

        cout << "Where would you like to deploy?" << endl;
        string deployCountry;
        cin>> deployCountry;
        Territory* t = toDefend(deployCountry);
        cout<<"You've selected the territory: "<<t->getTerritoryName()<<endl;
        cout<<"How many troops would you like to deploy?"<< endl;
        int armiesToDeploy;
        cin>>armiesToDeploy;
        cout<<"Your have ordered to deploy "<<armiesToDeploy<<" onto "<<t->getTerritoryName()<<endl;
        Order *deploy = new Deploy(&armiesToDeploy, &deployCountry, this->getPlayer());
        humanOrders.push_back(deploy);
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
                string source;
                cout << "Please select the source territory." << endl;
                cin >> source;
                Territory *sc = toDefend(source);
                cout << "These are the countries adjacent to the selected source that you can attack/defend: " << endl;
                for (int i = 0; i < sc->getAdjacentTerritories().size(); i++) {
                    cout << i + 1 << ". " << sc->getAdjacentTerritories()[i]->getTerritoryName() << endl;
                }
                string target;
                cout << "Which country would you like to attack/defend?" << endl;
                cin >> target;
                cout << "How many armies would you like to send." << endl;
                int num;
                cin >> num;
                Order *advance = new Advance(&num, &target, &source, this->getPlayer());
                humanOrders.push_back(advance);
            }

            case 2:{
                cout<<"Select one of the cards you have in your hand: "<<endl;
                for (int i = 0; i < this->getPlayer()->getHand()->getCardCount(); ++i) {
                    cout<<*this->getPlayer()->getHand()->getCards()[i]->getCardName()<<endl;
                }
                string cardChoice;
                cin>>cardChoice;
                switch (cardChoice.size()) {
                    case 4:{
                        //BOMB
                        cout<<"You've chosen to " << cardChoice<<endl;
                        cout<<"What enemy territory would you like to bomb?"<<endl;
                        for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                            for (int j = 0; j < this->getPlayer()->getTerritories()[i]->getAdjacentTerritories().size(); ++j) {
                                if(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayerName() != *this->getPlayer()->getName()){
                                    cout<<this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[i];
                                }
                            }
                        }
                        string bombTarget;
                        cin>>bombTarget;
                        Territory* bombed = toAttack(bombTarget);
                        Order* bomb = new Bomb(&bombTarget, this->getPlayer());
                        humanOrders.push_back(bomb);
                    }
                    case 7:{
                        //AIRLIFT
                        cout << "You have chosen to " << cardChoice <<endl;
                        cout << "These are your territories: " << endl;
                        for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                            cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName() << endl;
                        }
                        cout << "From which territory would you like to airlift" <<endl;
                        string source;
                        cin >> source;
                        cout << "Which territory would you like to advance to other than your source: " <<endl;
                        for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                            if(this->getPlayer()->getTerritories()[i]->getTerritoryName() == source){
                                cout<<"(source) ";
                            }
                            cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName() << endl;
                        }
                        string target;
                        cin >> target;
                        int noOfArmies;
                        Territory *t = toDefend(source);
                        bool airliftNum = true;
                        while (airliftNum) {
                            cout << "Your source territory: " << t->getTerritoryName() << " has " << t->getNoOfArmies()
                                 << " army units" << endl;
                            cout << "How many rmy units would you like to airlift?" << endl;
                            cin >> noOfArmies;
                            if (noOfArmies > t->getNoOfArmies() && noOfArmies < 0) {
                                cout << "You have entered an invalid number of armies, please enter an appropriate amount."<<endl;
                            }
                            else{
                                airliftNum = false;
                            }
                        }
                        Order *airlift = new Airlift(&noOfArmies,&target,&source,this->getPlayer());
                        humanOrders.push_back(airlift);
                    }
                    case 8:{
                        //BLOCKADE
                        cout << "You have chose to " << cardChoice <<endl;
                        cout << "These are your territories: " << endl;
                        for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
                            cout << i + 1 << ". " << this->getPlayer()->getTerritories()[i]->getTerritoryName() << endl;
                        }
                        cout << "Which territory would you like to block?" << endl;
                        string target;
                        cin >> target;
                        Order *blockade = new Blockade(&target, this->getPlayer());
                        humanOrders.push_back(blockade);

                    }
                    case 9:{
                        //NEGOTIATE
                    }
                }
            }

            case 3: {
                hasOrders = false;
            }

        }
    }
    return humanOrders;
}
Territory* HumanPlayerStrategy::toAttack(string attackCountry) {
    Territory* t = new Territory;
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        for (int j = 0; j < this->getPlayer()->getTerritories()[i]->getAdjacentTerritories().size(); ++j) {
            if(this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getPlayerName() != *this->getPlayer()->getName()
            && attackCountry == this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j]->getTerritoryName()) {
                t = this->getPlayer()->getTerritories()[i]->getAdjacentTerritories()[j];
            }
        }
    }
    return t;
}

Territory* HumanPlayerStrategy::toDefend(string deployCountry) {
    Territory* t = new Territory;
    for (int i = 0; i < this->getPlayer()->getTerritories().size(); ++i) {
        if (this->getPlayer()->getTerritories()[i]->getTerritoryName() == deployCountry){
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
    Territory* weakestTargetTerritory = toAttack(strongestOwnedTerritory);
    string weakestTerritoryName = weakestTargetTerritory->getTerritoryName();
    //check if we have any aggressive cards (bomb)
    for (int i = 0; i < this->getPlayer()->getHand()->getCards().size(); ++i) {
        if(*this->getPlayer()->getHand()->getCards()[i]->getCardName() == "BOMB"){
            Order* bomb = new Bomb(&weakestTerritoryName,this->getPlayer());
            aggressiveOrders.push_back(bomb);
        }
    }
    int strongestNoOfArmies = strongestOwnedTerritory->getNoOfArmies();
    Order* advance = new Advance(&strongestNoOfArmies,&weakestTerritoryName,&strongestTerritoryName,this->getPlayer());
    aggressiveOrders.push_back(advance);
    return aggressiveOrders;
}
Territory* AggressivePlayerStrategy::toAttack(Territory* territory) {
    //variable called terrritoryToAtk
    Territory* territoryToAtk = new Territory();
    //variable for min number of armies
    int minNumOfArmies = territory->getAdjacentTerritories()[0]->getNoOfArmies();
    //look at the adjacent ones to my strongestOwned
    for (int i = 0; i < territory->getAdjacentTerritories().size(); ++i) {
        if(minNumOfArmies<territory->getAdjacentTerritories()[i]->getNoOfArmies() && territory->getPlayerName() != territory->getAdjacentTerritories()[i]->getPlayerName()){
            minNumOfArmies = territory->getAdjacentTerritories()[i]->getNoOfArmies();
            territoryToAtk = territory->getAdjacentTerritories()[i];
        }
    }
    return territoryToAtk;
}
Territory* AggressivePlayerStrategy::toDefend() {
    //variable called strongestOwned
    Territory* strongestOwned = new Territory();
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
    return benevolentOrders;
    //deploy armies to the weakest territory
    //call toDefend to find its weakest territory and deploy all reinforcement armies there
}
Territory* BenevolentPlayerStrategy::toAttack() {} //void does not attack

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
    if(this->getPlayer()->getTerritories().size() != *this->noOfTerritories){
        //turn it to aggressive
        //this->getPlayer().setPs(Aggressive);

        //player1.issueOrder(ps->issueOrder
    }
/*
 * have a counter to count his initial armies present on his territories, loop every round through his
 * owned territories to add all armies. if the counter is not the same as the initial value turn him into aggresive
 * count1 > counter2 -> aggressive
 * his methods will become that of the aggresive one, inherit from aggresive and points to the methods?
 */
}

Territory* NeutralPlayerStrategy::toAttack() {

}

Territory* NeutralPlayerStrategy::toDefend() {

}

//Cheater
CheaterPlayerStrategy::CheaterPlayerStrategy() {

}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) {

}

CheaterPlayerStrategy::~CheaterPlayerStrategy() {

}

vector<Order*> CheaterPlayerStrategy::issueOrder() {
//call toAttack to conquer all adjacent territories -> num of armies becomes his (ownership changes)
//cheater will go before anyone else in the orders
}
Territory* CheaterPlayerStrategy::toAttack() {
//loop through countries adjacent to territories he owns and make them his
}
Territory* CheaterPlayerStrategy::toDefend() {
//don't defend you simply conquer territories
}

