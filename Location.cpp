#include "Location.h"
#include <iostream>
using namespace std;
 
Location::Location(string n, string desc, bool startUnlocked) {
    name = n;
    description = desc;
    unlocked = startUnlocked;
}
 
string Location::getName() {
    return name;
}
 
string Location::getDescription() {
    return description;
}
 
bool Location::isUnlocked() {
    return unlocked;
}
 
void Location::unlockLocation() {
    unlocked = true;
}
 
void Location::displayLocation() {
    cout << name << " - " << description;
    if (!unlocked) {
        cout << " (LOCKED)";
    }
    cout << endl;
}
 #include "Location.h"
#include <iostream>
using namespace std;

// Initializes a location with its name, description, and starting lock status.
Location::Location(string n, string desc, bool startUnlocked) {
    name = n;
    description = desc;
    unlocked = startUnlocked;
}

// Returns the location's name.
string Location::getName() {
    return name;
}

// Returns the location's description.
string Location::getDescription() {
    return description;
}

// Checks whether the location is currently unlocked.
bool Location::isUnlocked() {
    return unlocked;
}

// Unlocks the location so the player can access it.
void Location::unlockLocation() {
    unlocked = true;
}

// Displays the location's name and description.
void Location::displayLocation() {
    cout << name << " - " << description;

    // Show the locked status when the location has not been unlocked.
    if (!unlocked) {
        cout << " (LOCKED)";
    }

    cout << endl;
}