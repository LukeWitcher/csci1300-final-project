#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

// Base class for anyone who exists in the game world:
// the player's farmer, the villagers, shopkeepers, etc.
class Character {
protected:
    string name;
    int energy;
    int money;

public:
    Character(string n, int e, int m);

    // Getters
    string getName();
    int getEnergy();
    int getMoney();

    // Setters
    void setEnergy(int e);
    void setMoney(int m);

    
    void spendEnergy(int amount);
    void earnMoney(int amount);
    virtual void describe();
};

#endif