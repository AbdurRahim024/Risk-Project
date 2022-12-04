#include "Player.h"
#include <iostream>
#include <string>
#include "PlayerStrategies.h"
#include "map.h"
using namespace std;


void testPlayerStrategies(){
    //map
    //2 continents, player owns the one with 3 countries
    // 1 , 5 , 3 troops on top
    //   4 , 2   troops on bottom
    //5 continent bonus for top
    //0 continent bonus for bot

    //united states is 5
    //canada is 1
    //mexico is 3

    //brazil is 4
    //colombia is 2
    Map* map = new Map();

    //Continents
    Continent* top = new Continent(new string ("North America"), new int (5));
    Continent* bottom = new Continent(new string("South America"), 0);
    map->setSubgraph(top);
    map->setSubgraph(bottom);

    //Territories
    Territory* canada = new Territory(new string ("Canada"), top);
    Territory* unitedStates = new Territory(new string("United States"), top);
    Territory* mexico = new Territory(new string("Mexico"), top);
    Territory* brazil = new Territory(new string("Brazil"), bottom);
    Territory* colombia = new Territory(new string("Colombia"), bottom);
    //setting territories to continents
    top->setListofTerritories(canada);
    top->setListofTerritories(unitedStates);
    top->setListofTerritories(mexico);

    bottom->setListofTerritories(brazil);
    bottom->setListofTerritories(colombia);

    //setting adjacency lists
    canada->setAdjacentTerritories(unitedStates);
    canada->setAdjacentTerritories(brazil);

    unitedStates->setAdjacentTerritories(canada);
    unitedStates->setAdjacentTerritories(mexico);
    unitedStates->setAdjacentTerritories(brazil);
    unitedStates->setAdjacentTerritories(colombia);

    mexico->setAdjacentTerritories(unitedStates);
    mexico->setAdjacentTerritories(colombia);

    brazil->setAdjacentTerritories(canada);
    brazil->setAdjacentTerritories(colombia);
    brazil->setAdjacentTerritories(unitedStates);

    colombia->setAdjacentTerritories(mexico);
    colombia->setAdjacentTerritories(unitedStates);
    colombia->setAdjacentTerritories(brazil);

    //setting up the territories to the map
    vector<Territory*> territories = {canada,unitedStates,mexico,brazil,colombia};
    for (int i = 0; i < territories.size(); ++i) {
        map->setAllTerritories(territories[i]);
    }

    Player* enemyPlayer = new Player(new string("EnemyPlayer"));
    Player* testPlayer = new Player(new string("TestPlayer"));
    cout<<"TestPlayer has been created"<<endl;

    //giving out the territories to the players
    testPlayer->setTerritories({unitedStates,canada,mexico});
    enemyPlayer->setTerritories({brazil, colombia});


    canada->setPlayer(testPlayer);
    unitedStates->setPlayer(testPlayer);
    mexico->setPlayer(testPlayer);

    brazil->setPlayer(enemyPlayer);
    colombia->setPlayer(enemyPlayer);

    //adding troops to territories
    canada->setNoOfArmies(new int(1));
    unitedStates->setNoOfArmies(new int(5));
    mexico->setNoOfArmies(new int(3));

    brazil->setNoOfArmies(new int(4));
    colombia->setNoOfArmies(new int(2));
    //adding reinforcements to player
    testPlayer->setReinforcements(8);
    Card* bombCard = new Card(0);
    Hand* testHand = new Hand();
    testHand->addToHand(bombCard);
    testPlayer->setHand(testHand);
    PlayerStrategy* humanPs = new HumanPlayerStrategy(testPlayer, map);
    testPlayer->setPlayerStrategy(humanPs);
    cout<<"We have set the TestPlayer to have the HumanPlayerStrategy behavior"<<endl;
    vector<Order*>humansOrders = testPlayer->issueOrder();
    //toString the orders

    testPlayer->setReinforcements(8);
    PlayerStrategy* aggressivePs = new AggressivePlayerStrategy(testPlayer);
    testPlayer->setPlayerStrategy(aggressivePs);
    cout<<"We have set the TestPlayer to have the AggressivePlayerStrategy behavior"<<endl;
    vector<Order*> aggressiveOrders = testPlayer->issueOrder();
    cout<<"Order: "<<*aggressiveOrders[0]->getOrderName()<<"has been created by "<<*testPlayer->getName()<<endl;
    cout<<"Here the aggressive player has deployed all of his reinforcement units onto his strongest territory"<<endl;
    cout<<"Order: "<<*aggressiveOrders[1]->getOrderName()<<"has been created by "<<*testPlayer->getName()<<endl;
    cout<<"Here the aggressive player has chosen to bomb the weakest territory"<<endl;

    testPlayer->setReinforcements(8);
    PlayerStrategy* benevolentPs = new BenevolentPlayerStrategy(testPlayer);
    testPlayer->setPlayerStrategy(benevolentPs);
    cout<< "We have set the TestPlayer to have the BenevolentPlayerStrategy behavior"<<endl;
    vector<Order*> benevolentOrders = testPlayer->issueOrder();

    testPlayer->setReinforcements(8);
    PlayerStrategy* neutralPs = new NeutralPlayerStrategy(testPlayer);
    testPlayer->setPlayerStrategy(neutralPs);
    cout<<"We have set the TestPlayer to have the NeutralPlayerStrategy behavior"<<endl;
    vector<Order*> neutralOrders = testPlayer->issueOrder();

    PlayerStrategy* cheaterPs = new CheaterPlayerStrategy(testPlayer);
    testPlayer->setPlayerStrategy(cheaterPs);
    cout<<"We have set the TestPlayer to have the CheaterPlayerStrategy behavior"<<endl;
    vector<Order*> cheaterOrders = testPlayer->issueOrder();
    for (int i = 0; i < map->getAllTerritories().size(); ++i) {
        cout<<map->getAllTerritories()[i]->getPlayerName()<<" - "<<map->getAllTerritories()[i]->getTerritoryName()<<endl;
    }
    for (int i = 0; i < enemyPlayer->getTerritories().size(); ++i) {
        cout<<enemyPlayer->getTerritories()[i]->getTerritoryName()<<endl;
    }
    for (int i = 0; i < testPlayer->getTerritories().size(); ++i) {
        cout<<testPlayer->getTerritories()[i]->getTerritoryName()<<endl;
    }

}



//int main(){
//    testPlayerStrategies();
//}
//create a player

//assign them a specific strategy
//print this info out on the screen
//each player does their iconic order sequence
//Human: ask for user input on deploy and advance
//Aggressive: deploy all units on strongest owned territory then advance all units (including the ones deployed) to the weakest adjacent enemy
//Benevolent: deploy all units to the weakest owned territory
//Neutral: does nothing then gets attacked (we might just remove some armies to simulate this), then turns into an Aggressive player
//Cheater: just steals all surrounding territories