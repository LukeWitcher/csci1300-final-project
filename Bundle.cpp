#include "Bundle.h"
#include <iostream>
using namespace std;

// Initializes a bundle with its name and required number of items.
Bundle::Bundle(string n, int needed) {
    bundleName = n;
    itemsNeeded = needed;
    itemsCollected = 0;
}

// Returns the bundle's name.
string Bundle::getBundleName() {
    return bundleName;
}

// Returns the number of items needed.
int Bundle::getItemsNeeded() {
    return itemsNeeded;
}

// Returns the number of items collected so far.
int Bundle::getItemsCollected() {
    return itemsCollected;
}

// Adds an item if the bundle is not already complete.
void Bundle::addItem() {
    if (itemsCollected < itemsNeeded) {
        itemsCollected++;
    }
}

// Checks whether the bundle is complete.
bool Bundle::isComplete() {
    return itemsCollected >= itemsNeeded;
}

// Displays the bundle's current progress.
void Bundle::describe() {
    cout << bundleName << " Bundle: " << itemsCollected << "/"
         << itemsNeeded << " items";

    if (isComplete()) {
        cout << " (COMPLETE)";
    }

    cout << endl;
}