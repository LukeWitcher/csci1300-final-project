#ifndef FARMER_H
#define FARMER_H

#include "Character.h"
#include <string>
using namespace std;

class Farmer : public Character {
private:
    int farmingLevel;
    int itemsCarried;

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
};

#endif