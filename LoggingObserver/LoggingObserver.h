#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Observer {
    public:
        //-------------- Constructor --------------//
        Observer();

        //-------------- Destructor --------------//
        ~Observer();

        //-------------- Others --------------//
        virtual void update() = 0;
};

class Subject {
    public:
        //-------------- Constructors --------------//
        // Default
        Subject();
        // Parameterized
        Subject(vector<Observer*> observers);
        // Copy
        Subject(const Subject &initSubject);

        //-------------- Destructor --------------//
        ~Subject();

        //-------------- Others --------------//
        virtual void Attach(Observer* obs);
        void Detach(Observer* obs);
        void Notify();
        Subject &operator=(const Subject &subject);
        friend std::ostream &operator<<(std::ostream &stream, const Subject &subject);
    private:
        vector<Observer*>* observers;
};

class ILoggable{
    public:
        ILoggable();
        ~ILoggable();
        virtual string stringToLog() = 0;
};