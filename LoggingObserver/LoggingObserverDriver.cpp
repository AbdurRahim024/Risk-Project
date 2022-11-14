#include <iostream>
#include <fstream>
#include "LoggingObserver.h"
#include "GameEngine.h"
#include "Orders.h"
#include "GameEngineDriver.h"
#include "OrdersDriver.h"

void testLogObserver() {
    //creating observer
    LogObserver* obs = new LogObserver("gamelog.txt");

    //attaching observer to subjects
    GameEngine::setObserver(obs);
    Order::setObserver(obs);
    OrdersLists::setObserver(obs);
    CommandProcessor::setObserver(obs);
    Command::setObserver(obs);
    FileCommandProcessorAdapter::setObserver(obs);

    //start game
    GameEngine* g = new GameEngine();
    g->startupPhase();
    testMainGameLoop();
    testOrdersLists();


    //free observer
    delete obs;
    obs = nullptr;
}

int main() {
    testLogObserver();
}