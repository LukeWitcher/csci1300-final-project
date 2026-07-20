#ifndef VILLAGER_H
#define VILLAGER_H
 
#include <string>
#include "Item.h"
using namespace std;
 
 
class Villager {
private:
    string name;
    string favoriteGift;
    int friendship; // 0 to 10
    string homeLocation;   // which Location this villager can be found at
    string rewardName;     // name of the item this villager can give the player
    string rewardType;     // type of that item (Crop, Fish, Mineral, Animal Product, Forage)
    int rewardCost;        // money cost to receive the reward
 
public:
    Villager(string n, string gift, string home, string rName, string rType, int cost);
 
    // Getters
    string getName();
    string getFavoriteGift();
    int getFriendship();
    string getHomeLocation();
    int getRewardCost();
 
    // Setters
    void setFriendship(int level);
 
    // Behavior
    void receiveGift(string gift);
    void talk();
    Item giveReward();
};
 
#endif