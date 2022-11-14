#include "Player.h"
#include "PlayerDriver.h"

//void testPlayers() {
//    cout << "" << endl;
//    cout << "--- Player Test Function ---" << endl;
//
//    // MAKING PLAYER LIST
//    Player* p1 = new Player(new string("Sarah"));
//
//    // Printing player info for reference
//    cout << "" << endl;
//    cout << "--- Outputting Player's Current Info ---" << endl;
//    cout << "" << endl;
//    cout << *p1;
//
//    // List of players used to create deck
//    vector<Player*> players;
//    players.push_back(p1);
//
//    // Making deck with players
//    Deck* testDeck = new Deck(players);
//
//
//    cout << "--- Setting Player's Territory List ---" << endl;
//    cout << "" << endl;
//
//    // Creating arbitrary territories list (includes creating continent and assigning bonus values)
//    vector<Territory*> playerTerritories;
//    playerTerritories.push_back(new Territory(new string("Sudan"),new Continent(new string("Africa"), new int(5))));
//    playerTerritories.push_back(new Territory(new string("Germany"),new Continent(new string("Europe"), new int(9))));
//    playerTerritories.push_back(new Territory(new string("China"),new Continent(new string("Asia"), new int(2))));
//    p1->setTerritories(playerTerritories);
//
//    cout << "--- Creating Defend List ---" << endl;
//    cout << "" << endl;
//
//    //Call toDefend()
//    vector<Territory*> p1DefendList = p1->toDefend();
//
//    //Outputting p1DefendList
//    cout << "Player 1 will defend the following territories: " << endl;
//    for (Territory* ter : p1DefendList) {
//        cout << *ter << endl;
//    }
//
//    cout << "" << endl;
//    cout << "--- Creating Attack List ---" << endl;
//    cout << "" << endl;
//
//    //Call toAttack()
//    vector<Territory*> p1AttackList = p1->toAttack();
//
//    //Outputting p1AttackList
//    cout << "Player 1 will attack the following territories: " << endl;
//    for (Territory* ter : p1AttackList) {
//        cout << *ter << endl;
//    }
//
//
//    cout << "" << endl;
//    cout << "--- Player Drawing 4 Cards ---" << endl;
//    cout << "" << endl;
//
//    // Player drawing 4 random cards
//    p1->getHand()->addToHand(testDeck->draw());
//    p1->getHand()->addToHand(testDeck->draw());
//    p1->getHand()->addToHand(testDeck->draw());
//    p1->getHand()->addToHand(testDeck->draw());
//
//    cout << "--- Outputting Player's Current Info ---" << endl;
//    cout << "" << endl;
//
//    cout << *p1 << endl;
//
//    cout << "--- Player playing all cards (Cards Are Returned To Deck + Orders Are Issued) ---" << endl;
//    cout << "" << endl;
//
//    // Player issuing orders
//    p1->issueOrder(1);
//    p1->issueOrder(2);
//    p1->issueOrder(3);
//    p1->issueOrder(4);
//
//    // Output player info
//    cout << "" << endl;
//    cout << "--- Outputting Player's Current Info ---" << endl;
//    cout << "" << endl;
//    cout << *p1 << endl;

//}
