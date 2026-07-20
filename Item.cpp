#include "Item.h"
#include <iostream>
using namespace std;

// Initializes an item with its name, type, and energy restoration value.
Item::Item(string n, string t, int restore) {
    name = n;
    type = t;
    energyRestore = restore;
}

// Returns the item's name.
string Item::getName() {
    return name;
}

// Returns the item's type.
string Item::getType() {
    return type;
}

// Returns the amount of energy the item restores.
int Item::getEnergyRestore() {
    return energyRestore;
}

// Displays the item's information.
void Item::displayItem() {
    cout << name << " (" << type << ")";

    // Only display the energy restoration message for items that restore energy.
    if (energyRestore > 0) {
        cout << " - restores " << energyRestore << " energy";
    }

    cout << endl;
}