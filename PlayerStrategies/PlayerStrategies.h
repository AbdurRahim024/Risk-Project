#pragma once
#include "Player.h"
#include "LoggingObserver.h"
#include "GameEngine.h"
#include "Orders.h"
#include <iostream>

class Order;
class Territory;

class PlayerStrategy {
private:
    Player* p;
    static LogObserver* obs;
public:
    //constructors
    PlayerStrategy();
    PlayerStrategy(Player* player);

    //copy constructor
    PlayerStrategy(PlayerStrategy &playerstrat);

    //stream insertion operators
    friend ostream &operator << (ostream &output, PlayerStrategy &obj);

    //assignment operator
    PlayerStrategy& operator=(const PlayerStrategy &player);

    //destructor
    ~PlayerStrategy();

    //methods
    Player* getPlayer();
    void setPlayer(Player* player);
    virtual vector<Order*> issueOrder() = 0;
    virtual Territory* toAttack() = 0;
    virtual Territory* toDefend() = 0;
};

class HumanPlayerStrategy: public PlayerStrategy {
private:
    static LogObserver* obs;
    Map* map;
public:
    //constructors
    HumanPlayerStrategy();
    HumanPlayerStrategy(Player* player, Map* map);


    //copy consturctor
    HumanPlayerStrategy(HumanPlayerStrategy &humanstrat);

    //stream insertion operator
    friend ostream &operator<<(ostream &out, const HumanPlayerStrategy &human);

    //assignment operator
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy &human);

    //destructor
    ~HumanPlayerStrategy();

    //methods
    vector<Order*> issueOrder();
    Territory* toAttack();
    Territory* toDefend();

};

class AggressivePlayerStrategy: public PlayerStrategy{
private:
    static LogObserver* obs;
public:
    //constructors
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(Player* player);

    //copy constructor
    AggressivePlayerStrategy(AggressivePlayerStrategy &aggressivestrat);

    //stream insertion operator
    friend ostream &operator<<(ostream &out, const AggressivePlayerStrategy &aggressive);

    //assignment operator
     AggressivePlayerStrategy &operator=(const AggressivePlayerStrategy &aggressive);

     //destructor
    ~AggressivePlayerStrategy();

    //methods
    vector<Order*> issueOrder();
    Territory* toAttack();
    Territory* toDefend();
};

class BenevolentPlayerStrategy: public PlayerStrategy{
private:
    static LogObserver* obs;
public:
    //constructors
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(Player* player);

    //copy constructor
    BenevolentPlayerStrategy(BenevolentPlayerStrategy & bevolentstrat);

    //stream insertion operator
    friend ostream &operator<<(ostream &out, const BenevolentPlayerStrategy &benevolent);

    //assignment operator
    BenevolentPlayerStrategy &operator=(const BenevolentPlayerStrategy &benevolent);

    //destructor
    ~BenevolentPlayerStrategy();

    //methods
    vector<Order*> issueOrder();
    Territory* toAttack();
    Territory* toDefend();
};

class NeutralPlayerStrategy: public PlayerStrategy {
private:
    static LogObserver* obs;
    const int* noOfTerritories;
public:
    //constructors
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(Player* player);

    //copy constructor
    NeutralPlayerStrategy(NeutralPlayerStrategy &neutralstrat);

    //stream insertion operator
    friend ostream &operator<<(ostream &out, const NeutralPlayerStrategy &neutral);

    //assignment operator
     NeutralPlayerStrategy &operator=(const NeutralPlayerStrategy &neutral);

     //destructor
    ~NeutralPlayerStrategy();

    //methods
    vector<Order*> issueOrder();
    Territory* toAttack();
    Territory* toDefend();
};

class CheaterPlayerStrategy: public PlayerStrategy{
private:
    static LogObserver* obs;
public:
    //constructors
    CheaterPlayerStrategy();
    CheaterPlayerStrategy(Player* player);

    //copy constructor
    CheaterPlayerStrategy(CheaterPlayerStrategy &cheater);

    //stream insertion operator
    friend ostream &operator<<(ostream &out, const CheaterPlayerStrategy &cheater);

    //assignment operator
    CheaterPlayerStrategy &operator=(const CheaterPlayerStrategy &cheater);

    //destructor
    ~CheaterPlayerStrategy();

    //methods
    vector<Order*> issueOrder();
    Territory* toAttack();
    Territory* toDefend();
};