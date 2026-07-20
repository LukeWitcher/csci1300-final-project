#include "Villager.h"
#include "Item.h"
#include <iostream>
using namespace std;
 
Villager::Villager(string n, string gift, string home, string rName, string rType, int cost) {
    name = n;
    favoriteGift = gift;
    friendship = 0;
    homeLocation = home;
    rewardName = rName;
    rewardType = rType;
    rewardCost = cost;
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
 
string Villager::getHomeLocation() {
    return homeLocation;
}
 
int Villager::getRewardCost() {
    return rewardCost;
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
 
Item Villager::giveReward() {
    friendship += 1;
    return Item(rewardName, rewardType, 0);
}