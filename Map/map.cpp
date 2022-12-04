#include <iostream>
#include <vector>
#include "map.h"
#include <fstream>
#include <string>
using namespace std;


// --------------- OVERLOADING INSERTION STREAM OPERATORS ---------------

ostream &operator<<(ostream &output, Continent &obj){
    output << obj.getContinentName() <<" has the bonus value of " << endl;
    return output;
}

ostream &operator<<(ostream &output, Territory &obj){
    output << obj.getTerritoryName() << " belongs to Continent: " << obj.getContinent()->getContinentName() << endl;
    return output;
}
ostream &operator<<(ostream &output, Map &obj)
{
    output << "The Map has " << obj.getSubgraph().size() << " continents and " << obj.getAllTerritories().size()<< " territories"<< endl;
    return output;
}
ostream &operator<<(ostream &output, MapLoader &obj)
{
    output << "Map is being Loaded!" <<endl;
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
void Continent::setListofTerritories(Territory *t) {
    this->listofTerritories.push_back(t);
}
vector <Territory*> Continent::getListofTerritories(){
    return this->listofTerritories;
}



// ------------------- CONSTRUCTORS ----------------------
//Default constructor
Continent::Continent(){};
Continent::Continent(string *cName,int *bonusValue) {
    this->continentName = cName;
    this->bonusValue = bonusValue;
};
//Copy Constructor
Continent::Continent(Continent& continent){
    this->continentName = continent.continentName;
    this->bonusValue = continent.bonusValue;
};



// ---------------- OVERLOADING ASSIGNMENT OPERATORS -----------------

Continent &Continent::operator=(const Continent &t){
    continentName = t.continentName;
    bonusValue = t.bonusValue;

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
Player* Territory::getPlayer(){
    return this->player;
}
string Territory::getPlayerName() {
    return *this->getPlayer()->getName();
}
vector <Territory*> Territory:: getAdjacentTerritories(){
    return this->adjacentTerritories;
}
void Territory::setTerritoryName(string territoryName){
    *this->territoryName = territoryName;
};
//Why are we passing the reference to continent here???
void Territory::setContinent(Continent *continent){
    this->continent = continent;
};
void Territory::setNoOfArmies(int* noOfArmies){
    this->noOfArmies = noOfArmies;
};
void Territory::setPlayer(Player* playerName){
    this->player = playerName;
}
void Territory::setAdjacentTerritories(Territory* aT){
    this->adjacentTerritories.push_back(aT);
}




// --------------------- CONSTRUCTORS -------------------------

// Default Constructor
Territory::Territory(){};
Territory::Territory(string* territoryName){
    this->territoryName = territoryName;
    this->continent = NULL;
    this->setNoOfArmies(new int(0));
}

Territory::Territory(string *territoryName, Continent *continent){
    this->territoryName = territoryName;
    this->continent = continent;
    this->setNoOfArmies(new int(0));

    //create a list of adjacent countries of the territory stored in a vector of points
};

// Copy Constructor
Territory::Territory(Territory &territory){
    this->territoryName = territory.territoryName;
    this->noOfArmies= territory.noOfArmies;
    this->continent = territory.continent;
    this->player = territory.player;
};




// --------------------- OVERLOADING ASSIGNMENT OPERATOR -----------------

Territory &Territory::operator=(const Territory &t){
    territoryName = t.territoryName;
    noOfArmies = t.noOfArmies;
    continent = t.continent;
    return *this;
}

// ------------------------ MAP CLASS -------------------------
// ------------------- GETTERS AND SETTERS -------------------
vector <Continent*> Map::getSubgraph (){
    return this->subgraph;
};
vector <Territory*> Map::getAllTerritories(){
    return this->allTerritories;
}
void Map::setAllTerritories(Territory* t) {
    this->allTerritories.push_back(t);
}
void Map::setSubgraph(Continent *sub){
    this->subgraph.push_back(sub);
}

// ----------------- Constructors ----------------
Map::Map(){};
Map::Map(vector<Continent*> subgraph){
    this->subgraph = subgraph;
};
Map::Map(Map& map){
    this->subgraph = map.subgraph;
    this->allTerritories = map.allTerritories;
}

// ----------------- OVERLOADING ASSIGNMENT OPERATORS --------------------
Map &Map::operator=(const Map &map){
    this->subgraph = map.subgraph;
    this->allTerritories = map.allTerritories;
    return *this;
}

// ------------------------- MAP LOADER CLASS ------------------------


// ------------------ OVERLOADING ASSIGNMENT OPERATORS --------------

MapLoader &MapLoader::operator=(const MapLoader &map){
    this->realMap = map.realMap;
    return *this;
}


//Strip Line function which splits the string into a vector of strings
vector<string> stripLine(string line) {
    vector<string> result;
    string word = "";
    for (unsigned i = 0; i < line.length(); i++) {
        if (i == line.length()-1) {
            word=word +line.at(i);
            result.push_back(word);
        }
        if (line.at(i) == ',') {
            result.push_back(word);
            word = "";
        } else {
            word = word + line.at(i);
        }
    }
    return result;
}
Territory* MapLoader::addTerritory(string tName, string cName){
    vector<Continent*> continents = realMap->getSubgraph();
    vector<Territory*> f = realMap->getAllTerritories();
    bool territoryFound = false;
    int found = 0;
    string* tnamePointer = new string(tName);
    for(int i = 0; i < f.size();i++){
        if(f[i]->getTerritoryName() == tName){
            territoryFound = true;
            found = i;
            break;
        };
    }

    //If territory is not found and is in the adjacent list do the following
    if(territoryFound== false && cName == "adjacent"){
        Territory* adjacent = new Territory(tnamePointer);
        //add to list of all territories
        realMap->setAllTerritories(adjacent);
        return adjacent;
    }
    //If the territory is not found in the list of all Territories do the following
    if(territoryFound == false) {
        int pos = 0;
        for (int i = 0; i < continents.size(); i++) {
            if (continents[i]->getContinentName() == cName) {
                pos = i;
                break;
            }
        }
        //Creating a territory
        Territory* territory = new Territory(tnamePointer, continents[pos]);

        //Adding the territory to the all territories vector
        realMap->setAllTerritories(territory);
        continents[pos]->setListofTerritories(territory);
        return territory;
    }

    //If territory is found in the list of territories and is adjacent
    if(territoryFound == true && cName=="adjacent"){
        return f[found];
    }

    //If the territory is found in the list of territories
    if(territoryFound == true) {
        int pos = 0;
        for (int i = 0; i < continents.size(); i++) {
            if (continents[i]->getContinentName() == cName) {
                pos = i;
                break;
            }
        }
        if (f[found]->getContinent() == NULL) {

            f[found]->setContinent(continents[pos]);
            continents[pos]->setListofTerritories(f[found]);
            return f[found];
        }
        //we purposefully add any repeat territories here
        Territory *territory = new Territory(tnamePointer, continents[pos]);
        continents[pos]->setListofTerritories(territory);
        realMap->setAllTerritories(territory);
        return territory;
    }
}


/*This method is going to create a map after reading the .map files provided by the user
using io streams and return a pointer to the map object*/

Map* MapLoader::loadMap(string mapName){
    string fileName = mapName;
    cout<<"You have chosen file name: "<<fileName<<endl;
    realMap = new Map();
    string extension = fileName.substr((fileName.length())-4,fileName.length());
    if(extension!=".map"){
        cout<<"The file you entered is not of the .map format, you may try again!"<<endl;
        // by returning a null map pointer, we can reject all non .map files
        return realMap;
        //loop in driver to ensure we re-prompt user for the file name
    }
    // Open the file
    ifstream file;
    file.open(fileName);

    string lineText;
    bool atContinents = false;
    bool atTerritories = false;
    // loop through until we find [CONTINENTS] keyword
    while(!file.eof() && !atContinents){
        getline(file,lineText);
        if(lineText == "[Continents]"){
            atContinents = true;
        };

    };

    //If end of file and reached and we didn't find the [Continents] keyword
    if(file.eof() && !atContinents){
        cout << "End of File reached. No continents found, invalid map!" <<endl;
        //Returning an empty map
        return realMap;
    };

    //If we find the continents keyword
    if(atContinents){

        //Going to the next line
        getline(file,lineText);

        //Loop until the line is empty
        while (!lineText.empty()){

            //Splitting the string using = and creating a new continent and adding it to the continent's list inside the map
            string delimiter = "=";
            string *continentName = new string (lineText.substr(0, lineText.find(delimiter)));
            int *bonusValue = new  int (stoi(lineText.substr(lineText.find(delimiter)+1, lineText.length())));
            Continent* continent = new Continent(continentName,bonusValue);
            realMap->setSubgraph(continent);

            //Deallocating the memory since we created things inside the heap to prevent memory leaks
            continentName = nullptr;
            delete continentName;
            bonusValue = nullptr;
            delete bonusValue;
            continent = nullptr;
            delete continent;
            getline(file,lineText);
        }
    }

   // ------------------------- STARTING TO READ THE TERRITORIES ------------------------

   // If the end of file is not reached and territory keyword is not found
    while(!file.eof() && !atTerritories){
        getline(file,lineText);

        //Territories keyword is found
        if(lineText == "[Territories]"){
            atTerritories = true;
        };
    };



    // Rejecting the file if the territories keyword is not found after reading the whole map file
    if(file.eof() && !atTerritories){
        cout << "End of File reached. No Territories found, invalid map!"<<endl;

        //Returning an empty map
        return realMap;
    };


    //When the territories found is true
    if(atTerritories){

        //Loop until the end of file
        while (!file.eof()) {
            getline(file, lineText);
            if (!lineText.empty()) {

                //Splitting the string into a vector of strings
                vector<string> currentLine = stripLine(lineText);
                string countryName = currentLine[0];
                string continentName = currentLine[3];

                //Creating the first territory
                Territory *t = (addTerritory(countryName, continentName));

                //Looping over the rest of the vector of strings as we know the rest of territories are adjacent we create them
                for (int i = 4; i < currentLine.size(); i++) {
                    Territory *a = addTerritory(currentLine[i], "adjacent");
                    t->setAdjacentTerritories(a);

                    //Deallocating memory to avoid memory leaks
                    a = nullptr;
                    delete a;
                }
                //Deallocating memory to avoid memory leaks
                t = nullptr;
                delete t;
            }
        }
    }

    //Returning the map filled with all the territories created along with the continent vectors
    return realMap;
};

//recursive algorithm to ensure that the map is connected
void Map::validateConnectedMap(Territory *current, vector <Territory*> &placesVisited) {

    //prevent adding duplicate names of the same territory
    if (alreadyVisited(current, placesVisited)) {
        return;
    }
    //pushing the territories into the placesVisited vector
    placesVisited.push_back(current);

    //recursive part of the method to navigate through all territories
    for (Territory *neighbor: current->getAdjacentTerritories()) {
        validateConnectedMap (neighbor, placesVisited);
    }

}

//method to ensure that when going through the recursive algorith, we do not assign duplicate territories onto the list
bool Map::alreadyVisited(Territory* t, vector <Territory*> placesVisited) {
    //checks if the place is already visited and if it is, prevents if from being added to the list
    for (Territory* territory: placesVisited) {
        if(territory->getTerritoryName() == t->getTerritoryName()) {
            return true;
        }
    }
    return false;
}
//validate method to ensure that the map can be used
bool Map::validate() {

    //validate method to ensure that no duplicate territories are found in different continents
    for(int i = 0; i<this->getAllTerritories().size();i++){
        string territoryName = this->getAllTerritories()[i]->getTerritoryName();
        for(int j=i+1; j<this->getAllTerritories().size();j++){
            if(territoryName == this->getAllTerritories()[j]->getTerritoryName()){
                cout << "A duplicated territory was found within the map, it is an invalid map." <<endl;
                return false;
            }
        }
    }
    //vector of placesVisited to keep track when validating the map
    vector <Territory*> placesVisited;

    //starting condition to check if the map is valid
    validateConnectedMap(this->getAllTerritories()[0], placesVisited);
    if (placesVisited.size() != this->getAllTerritories().size()) {
        cout << "The map is not connected, it is invalid." <<endl;
        return false;
    }

    cout << "The map is valid" << endl;
    return true;

}

