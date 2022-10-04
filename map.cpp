#include <iostream>
#include <vector>
#include "map.h"
#include <stack>
#include <fstream>
using namespace std;


// --------------- OVERLOADING INSERTION STREAM OPERATORS ---------------

    ostream &operator<<(ostream &output, Continent &obj){
        output << obj.getContinentName() << endl;
        return output;
    }

    ostream &operator<<(ostream &output, Territory &obj){
        output << obj.getTerritoryName() << " belongs to Continent: " << obj.getContinent()->getContinentName() << endl;
        return output;
    }
    ostream &operator<<(ostream &output, Map &obj)
    {
        output << "The Map has " << obj.getSubgraph().size() << " continents." << endl;
        return output;
    }


    // ------------------- CONTINENT CLASS --------------------------
    
    // ------------------ GETTERS AND SETTERS ----------------------

    string Continent::getContinentName(){
        return *this->continentName;
    }; 
    int Continent::getBonusValue(){
        return *this->bonusValue;
    };
    void Continent::setContinentName(string continentName){
        *this->continentName = continentName;
    };
    void Continent :: setBonusValue(int bonusValue){
        *this->bonusValue = bonusValue;
    };



    // ------------------- CONSTRUCTORS ----------------------
    //Default constructor
    Continent::Continent(){};
    

    Continent::Continent(string continentName, int bonusValue) {
        continentName = continentName; 
        bonusValue = bonusValue; 
    };
    
    //Copy Constructor
    Continent::Continent(Continent &continent){
        this->continentName = continent.continentName;
        this->bonusValue = continent.bonusValue;
    };
    
  

    // ---------------- OVERLOADING ASSIGNMENT OPERATORS -----------------

    Continent &Continent::operator=(const Continent &t)
    {
        if (this != &t)
        {
            continentName = t.continentName;
        }
        return *this;
    }

    
        
    // --------------------- TERRITORY CLASS --------------------------

    // -------------------- GETTERS AND SETTERS ----------------------
    string Territory::getTerritoryName(){
        return *this->territoryName;
    };
    Continent *Territory::getContinent(){
        return this->continent;
    };
    int Territory::getNoOfArmies(){
        return *this->noOfArmies;
    };
    string Territory::getPlayerName(){
        return *this->playerName;
    }
    void Territory::setTerritoryName(string territoryName){
        *this->territoryName = territoryName;
    };
    void Territory::setContinent(Continent &continent){
        *this->continent = continent;
    };
    void Territory::setNoOfArmies(int noOfArmies){
        *this->noOfArmies = noOfArmies;
    };
    void Territory::setPlayerName(string playerName){
        *this->playerName = playerName;
    }



    // --------------------- CONSTRUCTORS -------------------------

    // Default Constructor
    Territory::Territory(){};

    Territory::Territory(string territoryName, Continent continent,int noOfArmies, vector <Territory*> adjacent){
        *this->territoryName = territoryName;
        *this->continent = continent;
        *this->noOfArmies = noOfArmies;
        //create a list of adjacent countries of the territory stored in a vector of points 
    };

    // Copy Constructor
    Territory::Territory(Territory &territory){
        this->territoryName = territory.territoryName;
        this->noOfArmies= territory.noOfArmies;
        this->continent = territory.continent;
        this->playerName = territory.playerName;
    };




    // --------------------- OVERLOADING ASSIGNMENT OPERATOR -----------------
    //Confused about pointers so if we have references instead of values i know where to look
    Territory &Territory::operator=(const Territory &t){
        if (this != &t)
        {
            territoryName = t.territoryName;
            noOfArmies = t.noOfArmies;
            continent = t.continent;
        }
        return *this;
    }

// ------------------- Map Class ---------------------
// ------------------- Getters and Setters ---------------
vector <Continent*> Map::getSubgraph (){
    return this->subgraph;
};

void Map::setSubgraph(vector<Continent*> sub){
    this->subgraph = sub;
}

// ----------------- Constructors ----------------
Map::Map(){};
Map::Map(vector<Continent*> subgraph){
    this->subgraph = subgraph;
};







class MapLoader{
    Map* loadMap();

    vector<Continent*> listOfContinents(){
        
    };
};