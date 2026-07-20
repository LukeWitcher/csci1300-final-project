#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "Farmer.h"
#include "Villager.h"
#include "Location.h"
#include "Bundle.h"
using namespace std;

// The Game class owns and controls the entire game: the player,
// the villagers, the locations/map, and the final bundles.
// This is where the main game loop lives.
class Game {
private:
    Farmer player;
    vector<Villager> villagers;
    vector<Location> locations;
    vector<Bundle> bundles;

    int currentLocationIndex;
    int day;
    int maxDays;
    int jojaInfluence;
    bool gameOver;

public:
    Game();

    void setupGame();
    void run();

    void displayDashboard();
    void displayMap();
    void showMainMenu();
    void processChoice(int choice);

    void movePlayer();
    void talkToCharacter();
    void viewInventory();
    void viewBundles();
    void visitCommunityCenter();
    void visitJojaMart();
    void endDay();

    bool allBundlesComplete();
    bool checkWin();
    bool checkLoss();
    void displayEnding();

    int findLocationIndex(string locationName);
    int findVillagerIndex(string villagerName);
};

#endif