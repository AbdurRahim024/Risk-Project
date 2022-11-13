#include "Cards.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include<iterator>
using namespace std;

/////////////////////////////////////////////// DECK /////////////////////////////////////////////////

// CONSTRUCTOR
Deck::Deck(const vector<Player*>& players) {

    //Make initial deck (2 cards of each type)
    Card* bomb1 = new Card(0);
    Card* bomb2 = new Card(0);
    Card* reinforcement1 = new Card(1);
    Card* reinforcement2 = new Card(1);
    Card* blockade1 = new Card(2);
    Card* blockade2 = new Card(2);
    Card* airlift1 = new Card(3);
    Card* airlift2 = new Card(3);
    Card* diplomacy1 = new Card(4);
    Card* diplomacy2 = new Card(4);
    Card* bomb3 = new Card(0);
    Card* bomb4 = new Card(0);
    Card* reinforcement3 = new Card(1);
    Card* reinforcement4 = new Card(1);

    cards.push_back(bomb1);
    cards.push_back(bomb2);
    cards.push_back(bomb3);
    cards.push_back(bomb4);
    cards.push_back(reinforcement1);
    cards.push_back(reinforcement2);
    cards.push_back(reinforcement3);
    cards.push_back(reinforcement4);
    cards.push_back(blockade1);
    cards.push_back(blockade2);
    cards.push_back(airlift1);
    cards.push_back(airlift2);
    cards.push_back(diplomacy1);
    cards.push_back(diplomacy2);

    //Assign deck to players
    for (auto currentPlayer : players) {

        //Assign this deck to each player
        currentPlayer->setDeck(this);

    }
}

// COPY CONSTRUCTOR
Deck::Deck(const Deck& copyDeck) {
    cout << "Copy constructor of Deck called" << endl;
    cards = copyDeck.cards;

}

// ASSIGNMENT OPERATOR
Deck& Deck::operator=(const Deck& assignDeck)
{
    cout << "Copy assignment operator of Deck" << endl;
    cards = assignDeck.cards;
}

// STREAM INSERTION OPERATOR
ostream& operator<<(ostream& os, Deck& deck)
{
    cout << "There are " << deck.cards.size() << " cards left in the deck." << endl;

    //iterate through deck and print every card type
    for(Card* card : deck.cards) {
        cout << *card << "; ";
    }
    cout << "" << endl << endl;
    return os;
}

// GETTERS
vector<Card*> Deck::getCards() {
    return cards;
}

int Deck::size() {
    // Return current size of deck
    return cards.size();
}

// SETTERS
void Deck::setCards(vector<Card*> newCards) {
    cards = newCards;
}

// OTHER
Card* Deck::draw() {

    //Retrieve random card from the deck and delete
    int cardsInDeck = cards.size();

    srand(time(nullptr)); // a new set of random numbers is generated
    int randomIndex = rand() % (cardsInDeck-1);

    Card* randomCard = cards.at(randomIndex);
    cards.erase(cards.begin() + randomIndex); //delete card from deck

    return randomCard;

}

void Deck::addToDeck(Card* card) {
    // After a player plays a card, it goes back into the deck
    cards.push_back(card);
}


// Destructor
Deck::~Deck() {

    //delete every card pointer in hand
    for (Card* card : cards) {
        delete card;
        card = nullptr;
    }

}


/////////////////////////////////////////////// HAND /////////////////////////////////////////////////

// CONSTRUCTOR
Hand::Hand() {
}

// COPY CONSTRUCTOR
Hand::Hand(const Hand& copyHand) {
    cout << "Copy constructor of Hand called" << endl;
    this->cards = copyHand.cards;
}

// ASSIGNMENT OPERATOR
Hand& Hand::operator=(const Hand& assignHand)
{
    cout << "Copy assignment operator of Hand" << endl;
    for (auto card : assignHand.cards)
    {
        this->cards.push_back(new Card(*card));
    }
    return *this;
}

// STREAM INSERTION OPERATOR
ostream& operator <<(ostream& os, const Hand& hand)
{
    cout << "This player has " << hand.cards.size() << " cards in hand" << endl;

    //iterate through deck and print every card type
    for(Card* card : hand.cards) {
        cout << *card << "; ";
    }

    if (!hand.cards.empty()) {
        cout << "" << endl;
    }

    return os;
}

// GETTERS
vector<Card*> Hand::getCards() {
    return cards;
}

int Hand::getCardCount() {
    return (int) cards.size();
}

// SETTERS
void Hand::setCards(vector<Card*> newCards) {
    cards = std::move(newCards);
}

// OTHER
void Hand::addToHand(Card* cardToAdd) {
    // Add card to hand
    cards.push_back(cardToAdd);

}

void Hand::deleteFromHand(Card* cardToDelete) {
    string* deleteCardName = cardToDelete->getCardName();

    //iterate through hand and find the card index
    for(int i = 0; i < cards.size(); i++) {
        Card* currentCard = cards.at(i);
        string* currCardName = currentCard->getCardName();

        // delete the card
        if (*deleteCardName == *currCardName) {
            cards.erase(cards.begin() + i);
            break;
        }

    }

}


// DESTRUCTOR
Hand::~Hand() {
    //delete every card pointer in hand
    for (Card* card : cards) {
        delete card;
        card = nullptr;
    }

}

/////////////////////////////////////////////// CARD /////////////////////////////////////////////////

// CONSTRUCTOR
Card::Card(int cardType) {

    // assign card name based on integer parameter
    switch (cardType) {

        case 0: {
            cardName = new string("BOMB");
            break;
        }
        case 1: {
            cardName = new string("REINFORCEMENT");
            break;
        }
        case 2: {
            cardName = new string("BLOCKADE");
            break;
        }
        case 3: {
            cardName = new string("AIRLIFT");
            break;
        }
        case 4: {
            cardName = new string("DIPLOMACY");
            break;
        }
        default: {
            cout << "Invalid input" << endl;
        }

    }
}

// COPY CONSTRUCTOR
Card::Card(const Card& copyCard) {
    cout << "Copy constructor of Card called" << endl;
    this->cardName = new string(*(copyCard.cardName));
}

// ASSIGNMENT OPERATOR
Card& Card::operator=(const Card& assignCard)
{
    cout << "Copy assignment operator of Card" << endl;
    this->cardName = new string(*(assignCard.cardName));
    return *this;
}

// STREAM INSERTION OPERATOR
ostream& operator <<(ostream& os, const Card& card)
{
    cout << *card.cardName;
    return os;
}

// GETTERS
string* Card::getCardName() {
    return cardName;
}

//SETTERS
void Card::setCardName(string* newCard) {
    cardName = newCard;
}

// OTHER
void Card::play(Player* p1, Deck* deck) {

    //remove card from player's hand
    p1->getHand()->deleteFromHand(this);

    //return card to deck
    deck->addToDeck(this);

}

// DESTRUCTORS
Card::~Card() {
    delete cardName;
    cardName = nullptr;
}






