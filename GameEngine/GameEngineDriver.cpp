#include "GameEngineDriver.h"
#include "GameEngine.h"
#include <iostream>
using namespace std;

void testGameStates() {
    cout << "Start of game" << endl << endl;
    GameEngine* g = new GameEngine();
    cout << *g << endl;
    //g->startupPhase();

//
//    while (*(g->getState()) < 8) {
//        cout << "Enter command: " << endl;
//        string input;
//        cin >> input;
//        g->gameFlow(input);
//        cout << *g << endl;
//    }

    cout << "End of game" << endl;

}

void testMainGameLoop() {
    GameEngine *game = new GameEngine();
    //create players
    Player* ali = new Player(new string("Ali"));
    Player* adriana = new Player(new string("Adriana"));
    Player* diego = new Player(new string("Diego"));
    vector <Player*> listofPlayers = {ali, adriana, diego};
    //create a map?
    Map* map = new Map();
    Continent* continent1 = new Continent(new string ("North America"),new int (12));
    Continent* continent2 = new Continent(new string ("Greenland"),new int (8));
    map->setSubgraph(continent1);
    map->setSubgraph(continent2);
    //Creating vector of all the territories
    Territory *t1 = new Territory(new string("USA"),continent1);
    Territory *t2 = new Territory(new string("Greenland"),continent2);
    Territory *t3 = new Territory(new string("Mexico"),continent1);
    Territory *t4 = new Territory(new string("Canada"),continent1);
    t1->setAdjacentTerritories(t4);
    t1->setAdjacentTerritories(t3);
    t3->setAdjacentTerritories(t1);
    t4->setAdjacentTerritories(t2);
    t4->setAdjacentTerritories(t1);
    t2->setAdjacentTerritories(t4);
    continent1->setListofTerritories(t1);
    continent1->setListofTerritories(t3);
    continent1->setListofTerritories(t4);
    continent2->setListofTerritories(t2);
    vector<Territory*> territories = {t1,t2,t3,t4};
    for(int i =0; i<territories.size(); i++){
        map->setAllTerritories(territories[i]);
    }
    //give them a certain number of territories
    ali->setTerritories({t4,t2});
    t4->setPlayer(ali);
    t2->setPlayer(ali);
    adriana->setTerritories({t3});
    t3->setPlayer(adriana);
    diego->setTerritories({t1});
    t1->setPlayer(diego);
    //calculate their number of reinforcements
    cout << "We have three players:" << ali->getName() << ", " << adriana->getName() << ", and " << diego->getName() << endl;
    cout << ali->getName() << " has: " << ali->getTerritories().size() << " territories" << endl;
    cout << adriana->getName() << " has: " << adriana->getTerritories().size() << " territories" << endl;
    cout << diego->getName() << " has: " << diego->getTerritories().size() << " territories" << endl;

    cout<< "\n\nWe will now calculate their number of reinforcements that they get:" << endl;
    game->reinforcementPhase({ali, adriana, diego}, map);
    cout << ali->getName() << " has: " << *ali->getReinforcements() << " reinforcements" << endl;
    cout << adriana->getName() << " has: " << *adriana->getReinforcements()<< " reinforcements" << endl;
    cout << diego->getName() << " has: " << *diego->getReinforcements() << " reinforcements" << endl;
    //display them
    //create orderslist
    list = game->issueOrdersPhase(listofPlayers,map);
    cout << "\n\nNow we will remove a player from the game: \n";
    cout << "Adriana's number of territories: " << adriana->getTerritories().size() << " --> " ;
    adriana->setTerritories({});
    cout << adriana->getTerritories().size() << " territories" << endl;
    for (int i = 0; i < listofPlayers.size(); ++i) {
        if(listofPlayers[i]->getTerritories().size() == 0){
            cout << "Player: " << listofPlayers[i]->getName() << " has been removed from the game, since they have no more territories" << endl;
            listofPlayers.erase(listofPlayers.begin()+1);
        }
    }
    t3->setPlayer(ali);
    cout << "\n\nNow we'll give all territories to one player: \n";
    t1->setPlayer(ali);
    ali->setTerritories({t1,t2,t3,t4});
    for (int i = 0; i < listofPlayers.size(); ++i) {
        if(map->getAllTerritories().size() == listofPlayers[i]->getTerritories().size()){
            cout << "Player: " << listofPlayers[i]->getName() << " owns all territories, and as such wins the game\n";
            cout << "\n\nCONGRATS FOR COMPLETING THE GAME!!";
            break;
        }
    }
    //display that a player with no territories is to be removed from the game
    //remove all territories from adriana, give to ali
    //remove adriana from game
    //display that the game ends when someone controls all territories
    //remove all territories from diego, give to ali
    //he wins the game
}
