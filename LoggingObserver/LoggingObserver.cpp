#include "LoggingObserver.h"
#include <algorithm>
using namespace std;
Observer::Observer(){

}
Observer::~Observer() {

}

Subject::Subject(){
    observers = new vector<Observer*>;
}
Subject::~Subject(){
    delete observers;
}
void Subject::Attach(Observer* o){
    observers->push_back(o);
};
void Subject::Detach(Observer* o){
    observers->erase(remove(observers->begin(),observers->end(),o));
    //auto itr = std::remove_if(observers->begin(),observers->end(), [&](Observer* a){return *a == *o;});

    //observers->erase(itr,observers->end());
    
};
void Subject::Notify(){
    vector<Observer *>::iterator i = observers->begin();
    for (; i != observers->end(); ++i)
        (*i)->update();
};