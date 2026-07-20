#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Farmer.h"
#include "Villager.h"
#include "Item.h"
#include "Location.h"
#include "Bundle.h"

using namespace std;

class Game {
private:
    // The player object stores the farmer's stats and inventory.
    Farmer player;

    // Stores all locations available in the game.
    vector<Location> locations;

    // Stores all villagers the player can interact with.
    vector<Villager> villagers;

    // Stores the bundles that the player must complete.
    vector<Bundle> bundles;

    // Tracks the player's current location in the locations vector.
    int currentLocationIndex;

    // Tracks the current day and the maximum number of days available.
    int day;
    int maxDays;

    // Tracks how much the player has relied on Joja shortcuts.
    int jojaInfluence;

    // Controls whether the game loop should continue running.
    bool gameOver;

    // Stores the custom farm name entered by the player.
    string farmName;

    // Helps format text so the dashboard lines up correctly.
    string padRight(string text, int width);

    // Checks whether every bundle has been completed.
    bool allBundlesComplete();

public:
    // Creates and initializes a new game.
    Game();

    // Sets up the locations, villagers, and bundles.
    void setupGame();

    // Runs the main game loop.
    void run();

    // Displays the main game dashboard.
    void displayDashboard();

    // Displays the available actions.
    void showMainMenu();

    // Processes the player's menu choice.
    void processChoice(char choice);

    // Allows the player to travel to another location.
    void movePlayer();

    // Allows the player to interact with villagers.
    void talkToCharacter();

    // Displays the player's inventory.
    void viewInventory();

    // Displays bundle progress.
    void viewBundles();

    // Handles donations at the Community Center.
    void visitCommunityCenter();

    // Handles the JojaMart shortcut system.
    void visitJojaMart();

    // Ends the current day and restores some energy.
    void endDay();

    // Checks whether the player has won.
    bool checkWin();

    // Checks whether the player has lost.
    bool checkLoss();

    // Displays the ending based on the player's choices.
    void displayEnding();

    // Finds a location by name and returns its index.
    int findLocationIndex(string locationName);

    // Finds a villager by name and returns their index.
    int findVillagerIndex(string villagerName);

    // Displays the map.
    void displayMap();
};

#endif