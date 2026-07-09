#include "Farmer.h"
#include <iostream>
using namespace std;

// Call the base Character constructor
Farmer::Farmer(string n, int e, int m, int level) : Character(n, e, m) {
    farmingLevel = level;
    itemsCarried = 0;
}

int Farmer::getFarmingLevel() {
    return farmingLevel;
}

int Farmer::getItemsCarried() {
    return itemsCarried;
}

void Farmer::setFarmingLevel(int level) {
    farmingLevel = level;
}

void Farmer::collectItem() {
    itemsCarried++;
    spendEnergy(5); // uses the inherited Character method
}

void Farmer::describe() {
    cout << name << " (Farmer, Lv." << farmingLevel << ") - Energy: "
         << energy << ", Money: " << money << "g, Items carried: "
         << itemsCarried << endl;
}