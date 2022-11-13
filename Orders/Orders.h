#pragma once
#include "map.h"
#include "Player.h"
#include "Cards.h"
#include <iostream>
#include <vector>
using namespace std;


class Territory;
class Player;
class Hand;
class Card;
class Deck;


extern Player* playerN;
extern vector<Player*> players;
extern Deck* deck;


class Order {
private:
    string* orderName;
    string* orderEffect;
    bool* executable;

protected:
    Player* player;

public:
    Order();
    Order(string* orderName);
    Order(Order* order);
    ~Order();
    string* getOrderName();
    string* getOrderEffect();
    bool* getExecutable();
    Player* getPlayer();
    void setOrderName(string* orderName);
    void setOrderEffect(string* orderEffect);
    void setExecutable(bool* executable);
    void setPlayer(Player* player);
    virtual bool* equals(Order* order);
    virtual bool* validate();
    virtual void execute();
    static Order* createSubtype(string s);
    static Order* createSubtype(Order* order);
    friend ostream & operator << (ostream &in, Order &o);
};



class Deploy : public Order {
private:
    int* unitsAtStart;
    int* unitsToSend;
    string* targetName;
    Territory* targetTerritory;

public:
    Deploy(int* unitsToSend, string* targetName, Player* player);
    Deploy(Deploy* deploy);
    ~Deploy();
    int getUnitsAtStart();
    int getUnitsToSend();
    string* getTargetName();
    Territory* getTargetTerritory();
    void setUnitsAtStart(int* unitsAtStart);
    void setUnitsToSend(int* unitsToSend);
    void setTargetName(string* targetName);
    void setTargetTerritory(Territory* targetTerritory);
    bool* equals(Order* order);
    bool* validate();
    void execute();
};



class Advance : public Order {
private:
    int* unitsAtStart;
    int* unitsToSend;
    string* targetName;
    string* sourceName;
    Territory* targetTerritory;
    Territory* sourceTerritory;

public:
    Advance(int* unitsToSend, string* targetName, string* sourceName, Player* player);
    Advance(Advance* advance);
    ~Advance();
    int getUnitsAtStart();
    int getUnitsToSend();
    string* getTargetName();
    string* getSourceName();
    Territory* getTargetTerritory();
    Territory* getSourceTerritory();
    void setUnitsAtStart(int* unitsAtStart);
    void setUnitsToSend(int* unitsToSend);
    void setTargetName(string* targetName);
    void setSourceName(string* sourceName);
    void setTargetTerritory(Territory* sourceTerritory);
    void setSourceTerritory(Territory* sourceTerritory);
    bool* equals(Order* order);
    bool* validate();
    void execute();
};



class Bomb : public Order {
private:
    string* targetName;
    Territory* targetTerritory;

public:
    Bomb(string* targetName, Player* player);
    Bomb(Bomb* bomb);
    ~Bomb();
    string* getTargetName();
    Territory* getTargetTerritory();
    void setTargetName(string* targetName);
    void setTargetTerritory(Territory* targetTerritory);
    bool* equals(Order* order);
    bool* validate();
    void execute();
};



class Blockade : public Order {
private:
    string* targetName;
    Territory* targetTerritory;

public:
    Blockade(string* targetName, Player* player);
    Blockade(Blockade* order);
    ~Blockade();
    string* getTargetName();
    Territory* getTargetTerritory();
    void setTargetName(string* targetName);
    void setTargetTerritory(Territory* targetTerritory);
    bool* equals(Order* order);
    bool* validate();
    void execute();
};



class Airlift : public Order {
private:
    int* unitsAtStart;
    int* unitsToSend;
    string* targetName;
    string* sourceName;
    Territory* targetTerritory;
    Territory* sourceTerritory;

public:
    Airlift(int* unitsToSend, string* targetName, string* sourceName, Player* player);
    Airlift(Airlift* airlift);
    ~Airlift();
    int getUnitsAtStart();
    int getUnitsToSend();
    string* getTargetName();
    string* getSourceName();
    Territory* getTargetTerritory();
    Territory* getSourceTerritory();
    void setUnitsAtStart(int* unitsAtStart);
    void setUnitsToSend(int* unitsToSend);
    void setTargetName(string* targetName);
    void setSourceName(string* sourceName);
    void setTargetTerritory(Territory* sourceTerritory);
    void setSourceTerritory(Territory* sourceTerritory);
    bool* equals(Order* order);
    bool* validate();
    void execute();
};



class Negotiate : public Order {
private:
    string* targetName;
    Player* targetPlayer;

public:
    Negotiate(string* targetName, Player* player);
    Negotiate(Negotiate* negotiate);
    ~Negotiate();
    string* getTargetName();
    Player* getTargetPlayer();
    void setTargetName(string* targetName);
    void setTargetPlayer(Player* targetPlayer);
    bool* equals(Order* order);
    bool* validate();
    void execute();
};



class OrdersLists {
private:
    vector<Order*> orders;

public:
    OrdersLists();
    OrdersLists(OrdersLists* list);
    ~OrdersLists();
    vector<Order*> getOrders();
    int getListSize();
    void setOrders(vector<Order*> orders);
    void add(Order* order);
    void remove(int index);
    void remove(Order* order);
    void move(int firstIndex, int secondIndex);
    void execute();
};



ostream & operator << (ostream &out, Order &o);