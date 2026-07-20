#include "Farmer.h"
#include "Item.h"
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
 
void Farmer::addItem(Item newItem) {
    inventory.push_back(newItem);
    itemsCarried++;
}
 
bool Farmer::hasItem(string itemName) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i].getName() == itemName) {
            return true;
        }
    }
    return false;
}
 
void Farmer::removeItem(string itemName) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i].getName() == itemName) {
            inventory.erase(inventory.begin() + i);
            itemsCarried--;
            return;
        }
    }
}
 
void Farmer::displayInventory() {
    if (inventory.empty()) {
        cout << "Your inventory is empty." << endl;
        return;
    }
    cout << "Inventory:" << endl;
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i + 1 << ". ";
        inventory[i].displayItem();
    }
}
 
int Farmer::getInventorySize() {
    return inventory.size();
}
 
string Farmer::getItemNameAt(int index) {
    return inventory[index].getName();
}
 
Item Farmer::getItemAt(int index) {
    return inventory[index];
}