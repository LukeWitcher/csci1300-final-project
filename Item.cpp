#include "Item.h"
#include <iostream>
using namespace std;
 
Item::Item(string n, string t, int restore) {
    name = n;
    type = t;
    energyRestore = restore;
}
 
string Item::getName() {
    return name;
}
 
string Item::getType() {
    return type;
}
 
int Item::getEnergyRestore() {
    return energyRestore;
}
 
void Item::displayItem() {
    cout << name << " (" << type << ")";
    if (energyRestore > 0) {
        cout << " - restores " << energyRestore << " energy";
    }
    cout << endl;
}
 