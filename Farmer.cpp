#include "Farmer.h"
#include "Item.h"
#include <iostream>
using namespace std;

// Initializes the Farmer using the base Character constructor.
Farmer::Farmer(string n, int e, int m, int level) : Character(n, e, m) {
    farmingLevel = level;
    itemsCarried = 0;
}

// Returns the farmer's farming level.
int Farmer::getFarmingLevel() {
    return farmingLevel;
}

// Returns the number of items the farmer is carrying.
int Farmer::getItemsCarried() {
    return itemsCarried;
}

// Updates the farmer's farming level.
void Farmer::setFarmingLevel(int level) {
    farmingLevel = level;
}

// Collecting an item increases the item count and uses energy.
void Farmer::collectItem() {
    itemsCarried++;
    spendEnergy(5); // uses the inherited Character method
}

// Displays the farmer's current information.
void Farmer::describe() {
    cout << name << " (Farmer, Lv." << farmingLevel << ") - Energy: "
         << energy << ", Money: " << money << "g, Items carried: "
         << itemsCarried << endl;
}

// Adds an item to the farmer's inventory.
void Farmer::addItem(Item newItem) {
    inventory.push_back(newItem);
    itemsCarried++;
}

// Checks whether the farmer has an item with the given name.
bool Farmer::hasItem(string itemName) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i].getName() == itemName) {
            return true;
        }
    }
    return false;
}

// Removes the first matching item from the inventory.
void Farmer::removeItem(string itemName) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i].getName() == itemName) {
            inventory.erase(inventory.begin() + i);
            itemsCarried--;
            return;
        }
    }
}

// Displays every item currently in the inventory.
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

// Returns the number of items in the inventory.
int Farmer::getInventorySize() {
    return inventory.size();
}

// Returns the name of an item at a specific inventory index.
string Farmer::getItemNameAt(int index) {
    return inventory[index].getName();
}

// Returns the item at a specific inventory index.
Item Farmer::getItemAt(int index) {
    return inventory[index];
}