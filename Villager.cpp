#include "Villager.h"
#include "Item.h"
#include <iostream>
using namespace std;

// Initializes a villager with their name, gift preference, location, and reward.
Villager::Villager(string n, string gift, string home, string rName, string rType, int cost) {
    name = n;
    favoriteGift = gift;
    friendship = 0;
    homeLocation = home;
    rewardName = rName;
    rewardType = rType;
    rewardCost = cost;
}

// Returns the villager's name.
string Villager::getName() {
    return name;
}

// Returns the villager's favorite gift.
string Villager::getFavoriteGift() {
    return favoriteGift;
}

// Returns the current friendship level.
int Villager::getFriendship() {
    return friendship;
}

// Returns the location where the villager can be found.
string Villager::getHomeLocation() {
    return homeLocation;
}

// Returns the cost of the villager's reward item.
int Villager::getRewardCost() {
    return rewardCost;
}

// Changes the villager's friendship level.
void Villager::setFriendship(int level) {
    friendship = level;
}

// Increases friendship based on whether the gift is a favorite.
void Villager::receiveGift(string gift) {
    if (gift == favoriteGift) {
        friendship += 2;
        cout << name << " loved the " << gift << "!" << endl;
    } else {
        friendship += 1;
        cout << name << " appreciated the " << gift << "." << endl;
    }
}

// Displays a message from the villager.
void Villager::talk() {
    cout << name << ": \"Good to see you! Friendship level: "
         << friendship << "\"" << endl;
}

// Creates and returns the reward item while increasing friendship.
Item Villager::giveReward() {
    friendship += 1;
    return Item(rewardName, rewardType, 0);
}