#include "Orders.h"
#include "OrdersDriver.h"
#include <iostream>
#include <vector>
using namespace std;



Player* playerN;
vector<Player*> players;
Deck* deck;



void testOrdersLists();



//int main() {
//    testOrdersLists();
//    return 0;
//}



void testOrdersLists() {
//    create players
    Player* player1 = new Player(new string("Player 1"));
    Player* player2 = new Player(new string("Player 2"));
    playerN = new Player(new string("Neutral"));
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(playerN);
    player1->setReinforcements(10);
    player2->setReinforcements(10);

//    create cards and deck
    vector<Card*> cards1;
    for(int i = 0; i < 5; i++) {
        cards1.push_back(new Card(i));
    }
    Hand* hand1 = new Hand();
    hand1->setCards(cards1);
    player1->setHand(hand1);
    deck = new Deck(players);

//    create territories
    Territory* NL = new Territory(new string("Newfoundland"));
    Territory* QC = new Territory(new string("Quebec"));
    Territory* ON = new Territory(new string("Ontario"));
    Territory* MB = new Territory(new string("Manitoba"));
    NL->setNoOfArmies(4);
    QC->setNoOfArmies(3);
    ON->setNoOfArmies(2);
    MB->setNoOfArmies(1);

//    set adjacent territories for each territory
    NL->setAdjacentTerritories(QC);
    QC->setAdjacentTerritories(NL);
    QC->setAdjacentTerritories(ON);
    ON->setAdjacentTerritories(QC);
    ON->setAdjacentTerritories(MB);
    MB->setAdjacentTerritories(ON);

//    set prerequisites (ON is kept neutral for testing)
    NL->setPlayer(player1);
    QC->setPlayer(player1);
    MB->setPlayer(player2);
    ON->setPlayer(playerN);
    vector<Territory*> territories1;
    vector<Territory*> territories2;
    vector<Territory*> territoriesN;
    territories1.push_back(NL);
    territories1.push_back(QC);
    territories2.push_back(MB);
    territoriesN.push_back(ON);
    player1->setTerritories(territories1);
    player2->setTerritories(territories2);
    playerN->setTerritories(territoriesN);

//    create OrdersLists list
    OrdersLists* list = new OrdersLists();

    /*
     * P1 deploy qc works
     * P1 deploy on fails
     * P1 blockade on fails
     * P1 bomb mb fails
     * P1 airlift nl-mb fails
     * P1 advance qc-on works
     * P1 bomb mb works
     * P1 negotiate P2 works
     * P1 negotiate Pn fails
     * P1 advance qc-mb fails
     * P1 airlift nl-on works
     * P1 blockade on works
     */
//    create an Order of each subclass
    Deploy* deploy1 = new Deploy(new int(5), new string("Quebec"), player1);
    Deploy* deploy2 = new Deploy(new int(2), new string("Ontario"), player1);
    Blockade* blockade1 = new Blockade(new string("Ontario"), player1);
    Bomb* bomb1 = new Bomb(new string("Manitoba"), player1);
    Airlift* airlift1 = new Airlift(new int(2), new string("Manitoba"), new string("Newfoundland"), player1);
    Advance* advance1 = new Advance(new int(3), new string("Ontario"), new string("Quebec"), player1);
    Bomb* bomb2 = new Bomb(new string("Manitoba"), player1);
    Negotiate* negotiate1 = new Negotiate(new string("Player 2"), player1);
    Negotiate* negotiate2 = new Negotiate(new string("Neutral"), player1);
    Advance* advance2 = new Advance(new int(2), new string("Manitoba"), new string("Quebec"), player1);
    Airlift* airlift2 = new Airlift(new int(2), new string("Ontario"), new string("Newfoundland"), player1);
    Blockade* blockade2 = new Blockade(new string("Ontario"), player1);

//    add each created Order
    list->add(deploy1);
    list->add(deploy2);
    list->add(blockade1);
    list->add(bomb1);
    list->add(airlift1);
    list->add(advance1);
    list->add(bomb2);
    list->add(negotiate1);
    list->add(negotiate2);
    list->add(advance2);
    list->add(airlift2);
    list->add(blockade2);

//    execute list
    list->execute();
};