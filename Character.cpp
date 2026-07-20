#include "Character.h"
#include <iostream>
using namespace std;

// Initializes a character with a name, energy level, and amount of money.
Character::Character(string n, int e, int m) {
    name = n;
    energy = e;
    money = m;
}

// Returns the character's name.
string Character::getName() {
    return name;
}

// Returns the character's current energy.
int Character::getEnergy() {
    return energy;
}

// Returns the character's current money.
int Character::getMoney() {
    return money;
}

// Updates the character's energy.
void Character::setEnergy(int e) {
    energy = e;
}

// Updates the character's money.
void Character::setMoney(int m) {
    money = m;
}

// Removes energy while preventing the value from going below zero.
void Character::spendEnergy(int amount) {
    energy -= amount;
    if (energy < 0) {
        energy = 0;
    }
}

// Adds money to the character's total.
void Character::earnMoney(int amount) {
    money += amount;
}

// Displays the character's current information.
void Character::describe() {
    cout << name << " - Energy: " << energy << ", Money: " << money << "g" << endl;
}