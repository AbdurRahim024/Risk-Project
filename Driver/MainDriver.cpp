#include "CardsDriver.h"
#include "mapDriver.h"
#include "GameEngineDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include <iostream>


//int main () {
//    cout << "Please enter the number associated with the test you'd like to run" << endl;
//    cout<<"To test the Map: press 1"<<endl;
//    cout<<"To test the Player: press 2"<<endl;
//    cout<<"To test the Orders List: press 3"<<endl;
//    cout<<"To test the Cards deck/hand: press 4"<<endl;
//    cout<<"To test the Game Engine: press 5"<<endl;
//    int input;
//    cin>>input;
//    while(input!= 0) {
//        switch (input) {
//            case 1:
//                cout << "You have chosen to test the Map..." << endl;
//                testLoadMaps();
//                break;
//            case 2:
//                cout << "You have chosen to test the Player..." << endl;
//                testPlayers();
//                break;
//            case 3:
//                cout << "You have chosen to test the Orders list..." << endl;
//                testOrdersLists();
//                break;
//            case 4:
//                cout << "You have chosen to test the Cards deck/hand..." << endl;
//                testCards();
//                break;
//            case 5:
//                cout << "You have chosen to test the Game Engine..." << endl;
//                testGameStates();
//                break;
//        }
//        cout<<"Enter the next input!"<<endl;
//        cout<<"To test the Map: press 1"<<endl;
//        cout<<"To test the Player: press 2"<<endl;
//        cout<<"To test the Orders List: press 3"<<endl;
//        cout<<"To test the Cards deck/hand: press 4"<<endl;
//        cout<<"To test the Game Engine: press 5"<<endl;
//        cin>>input;
//    }
//    return 0;
//}
int main(){
    testMainGameLoop();
    testGameStates();
    return 0;
}