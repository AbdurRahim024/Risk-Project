#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
using namespace std;
#include <vector>


void testCommandProcessor() {
    cout << "TOURNAMENT TEST" << endl;
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

    //todo emma: test this
//    string str = "tournament -M Asia.map,NY.map -P aggressive,benevolent,neutral,cheater -G 2 -D 10";
//    vector<string> tournamentInfo = Tournament::tokenize(str,' ');
//    Tournament* t = new Tournament(tournamentInfo);
//    t->printGameData();
}

int main() {
    testCommandProcessor();
}




