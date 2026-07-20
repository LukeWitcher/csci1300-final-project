#ifndef FARMER_H
#define FARMER_H
 
#include "Character.h"
#include "Item.h"
#include <string>
#include <vector>
using namespace std;
 
class Farmer : public Character {
private:
    int farmingLevel;
    int itemsCarried;
    vector<Item> inventory;
 
public:
    Farmer(string n, int e, int m, int level);
 
    // Getters
    int getFarmingLevel();
    int getItemsCarried();
 
    // Setters
    void setFarmingLevel(int level);
 
    // Farmer-specific behavior
    void collectItem();
    void describe(); // overrides Character::describe()
 
    // Inventory management
    void addItem(Item newItem);
    bool hasItem(string itemName);
    void removeItem(string itemName);
    void displayInventory();
    int getInventorySize();
    string getItemNameAt(int index);
    Item getItemAt(int index);
};
 
#endif