#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;

class Territory;
class Map;
class MapLoader;
class Player;
class Continent{
private:
    string* continentName;
    int* bonusValue;
    vector <Territory*> listofTerritories;

    // getter and setter methods for Continent class
public:
    string getContinentName();
    int getBonusValue();
    void setContinentName(string continentName);
    void setBonusValue(int bonusValue);
    void setListofTerritories(Territory* t);
    vector <Territory*> getListofTerritories();
    //void setContinentTerritories (); set a vector to hold the countries from a continent


    // constructors for Continent class
    Continent();
    Continent(string *continentName, int *bonusValue);
    Continent(Continent &continent);
    // ~Continent();

    //Overloads
    Continent& operator=(const Continent& t); //Overload assignment operator
    friend ostream& operator<<(ostream& output, Continent& obj); //Overload stream insertion

};

//the Territory class
class Territory{
private:
    vector <Territory*> adjacentTerritories;
    string* territoryName;
    Continent* continent;
    int* noOfArmies;
    // this will eventually be a player object
    Player* player;

    // getter and setter methods for Territory class.
public:
    string getTerritoryName();
    Continent *getContinent();
    int getNoOfArmies();
    string getPlayerName();
    void setTerritoryName(string territoryName);
    void setAdjacentTerritories(Territory* aT);
    vector<Territory*> getAdjacentTerritories();
    void setPlayer(Player* p);
    Player* getPlayer();

    //Im confused to why we are passing the reference to the continent here???
    //Previously it (Continent &continent) i changed it to a pointer because in the add territory
    //we are passing a continent pointer to set the continent name when territory found is true
    void setContinent(Continent *continent);
    void setNoOfArmies(int* noOfArmies);        // a: changed to pointer
    void setPlayerName(string playerName);

    // constructors for Territory class
    Territory();
    Territory(string* territoryName);
    Territory(string *territoryName, Continent *continent);
    Territory(Territory &territory);
    // ~Territory();

    //Overloads
    Territory& operator=(const Territory& t); //Overload assignment operator
    friend ostream& operator<<(ostream& output, Territory& obj); //Overload stream insertion

};

class MapLoader{
private:
 //Creation of a map in the MapLoader so that you can access the list of territories and continents from the loader itself
    Map* realMap;
public:
    Map* loadMap(string mapName);
    Territory* addTerritory(string tName, string cName);

    //Overloading operators
    MapLoader& operator=(const MapLoader& m);
    friend ostream& operator<<(ostream& output, MapLoader& obj);
};


class Map{
private:
    vector <Continent*> subgraph;
    vector <Territory*> allTerritories;

public:
    Map();
    Map(vector <Continent*> subgraph);
    Map(Map& map);
    vector <Continent*> getSubgraph();
    vector <Territory*> getAllTerritories();
    void setAllTerritories(Territory* t);
    void setSubgraph(Continent *sub);
    bool validate();
    void validateConnectedMap(Territory *t, vector <Territory*> &placesVisited);
    bool alreadyVisited (Territory* t, vector <Territory*> placesVisited);
    void printAllTerritories();

    //Overloads
    Map& operator=(const Map& map);
    friend ostream& operator<<(ostream& output, Map& obj);
};