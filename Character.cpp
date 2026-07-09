#include "Character.h"
#include <iostream>
using namespace std;

Character::Character(string n, int e, int m) {
    name = n;
    energy = e;
    money = m;
}

string Character::getName() {
    return name;
}

int Character::getEnergy() {
    return energy;
}

int Character::getMoney() {
    return money;
}

void Character::setEnergy(int e) {
    energy = e;
}

void Character::setMoney(int m) {
    money = m;
}

void Character::spendEnergy(int amount) {
    energy -= amount;
    if (energy < 0) {
        energy = 0;
    }
}

void Character::earnMoney(int amount) {
    money += amount;
}

void Character::describe() {
    cout << name << " - Energy: " << energy << ", Money: " << money << "g" << endl;
}