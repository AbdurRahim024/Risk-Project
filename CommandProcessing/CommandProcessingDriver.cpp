#include "CommandProcessing.h"
#include "GameEngine.h"

void testCommandProcessor() {
    cout << "COMMAND PROCESSING TEST" << endl;
    GameEngine* g = new GameEngine();
    g->startupPhase();
}
