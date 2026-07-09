#ifndef VILLAGER_H
#define VILLAGER_H

#include <string>
using namespace std;


class Villager {
private:
    string name;
    string favoriteGift;
    int friendship; // 0 to 10

public:
    Villager(string n, string gift);

    // Getters
    string getName();
    string getFavoriteGift();
    int getFriendship();

    // Setters
    void setFriendship(int level);

    // Behavior
    void receiveGift(string gift);
    void talk();
};

#endif