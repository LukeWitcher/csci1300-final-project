#include "Bundle.h"
#include <iostream>
using namespace std;

Bundle::Bundle(string n, int needed) {
    bundleName = n;
    itemsNeeded = needed;
    itemsCollected = 0;
}

string Bundle::getBundleName() {
    return bundleName;
}

int Bundle::getItemsNeeded() {
    return itemsNeeded;
}

int Bundle::getItemsCollected() {
    return itemsCollected;
}

void Bundle::addItem() {
    if (itemsCollected < itemsNeeded) {
        itemsCollected++;
    }
}

bool Bundle::isComplete() {
    return itemsCollected >= itemsNeeded;
}

void Bundle::describe() {
    cout << bundleName << " Bundle: " << itemsCollected << "/"
         << itemsNeeded << " items";
    if (isComplete()) {
        cout << " (COMPLETE)";
    }
    cout << endl;
}