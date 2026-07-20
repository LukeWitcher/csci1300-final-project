#ifndef LOCATION_H
#define LOCATION_H
 
#include <string>
using namespace std;
 
// Represents one place on the town map the player can visit.
class Location {
private:
    string name;
    string description;
    bool unlocked;
 
public:
    Location(string n, string desc, bool startUnlocked);
 
    // Getters
    string getName();
    string getDescription();
    bool isUnlocked();
 
    // Behavior
    void unlockLocation();
    void displayLocation();
};
 
#endif