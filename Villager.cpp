#include "Villager.h"
#include <iostream>
using namespace std;

Villager::Villager(string n, string gift) {
    name = n;
    favoriteGift = gift;
    friendship = 0;
}

string Villager::getName() {
    return name;
}

string Villager::getFavoriteGift() {
    return favoriteGift;
}

int Villager::getFriendship() {
    return friendship;
}

void Villager::setFriendship(int level) {
    friendship = level;
}

void Villager::receiveGift(string gift) {
    if (gift == favoriteGift) {
        friendship += 2;
        cout << name << " loved the " << gift << "!" << endl;
    } else {
        friendship += 1;
        cout << name << " appreciated the " << gift << "." << endl;
    }
}

void Villager::talk() {
    cout << name << ": \"Good to see you! Friendship level: "
         << friendship << "\"" << endl;
}