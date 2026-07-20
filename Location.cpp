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
 