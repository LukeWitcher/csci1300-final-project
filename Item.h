#ifndef ITEM_H
#define ITEM_H
 
#include <string>
using namespace std;
 
// Represents a single collectible item: a crop, fish, mineral,
// animal product, forage item, or piece of food.
class Item {
private:
    string name;
    string type;          // "Crop", "Fish", "Mineral", "Animal Product", "Forage", "Food"
    int energyRestore;     // how much energy this restores if eaten (0 if not food)
 
public:
    Item(string n, string t, int restore);
 
    // Getters
    string getName();
    string getType();
    int getEnergyRestore();
 
    // Behavior
    void displayItem();
};
 
#endif