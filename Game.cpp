#include "Game.h"
#include "Item.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
 
// Reads bundles.txt (format: name,itemsNeeded) and builds a vector of Bundle objects.
vector<Bundle> loadBundles(string filename) {
    vector<Bundle> loaded;
    ifstream inFile(filename);
 
    if (!inFile) {
        cout << "Warning: could not open " << filename << endl;
        return loaded;
    }
 
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        string name;
        string neededStr;
        getline(ss, name, ',');
        getline(ss, neededStr, ',');
        int needed = stoi(neededStr);
        loaded.push_back(Bundle(name, needed));
    }
 
    inFile.close();
    return loaded;
}
 
Game::Game() : player("Riley", 100, 500, 1) {
    currentLocationIndex = 0;
    day = 1;
    maxDays = 7;
    jojaInfluence = 0;
    gameOver = false;
}
 
void Game::setupGame() {
    // Build the map. Mines starts locked until Robin is spoken to.
    locations.push_back(Location("Farm", "Your home base. Quiet and safe.", true));
    locations.push_back(Location("Town Square", "The heart of town. Robin and Pierre are usually here.", true));
    locations.push_back(Location("Beach", "Willy fishes here most days.", true));
    locations.push_back(Location("Mines", "Full of minerals, but the entrance is blocked.", false));
    locations.push_back(Location("Community Center", "Where you donate items for the final bundle.", true));
    locations.push_back(Location("JojaMart", "Morris is always offering a 'deal'.", true));
 
    // Four characters, each tied to a location and a reward item.
    villagers.push_back(Villager("Robin", "Wood", "Town Square", "Wood", "Forage", 0));
    villagers.push_back(Villager("Pierre", "Parsnip", "Town Square", "Parsnip", "Crop", 20));
    villagers.push_back(Villager("Willy", "Sunfish", "Beach", "Sunfish", "Fish", 10));
    villagers.push_back(Villager("Marnie", "Egg", "Farm", "Egg", "Animal Product", 15));
 
    // Load the final bundles from file instead of hardcoding them.
    bundles = loadBundles("bundles.txt");
}
 
void Game::displayDashboard() {
    cout << endl;
    cout << "==================================================" << endl;
    cout << "                 THE FINAL BUNDLE" << endl;
    cout << "==================================================" << endl;
    cout << "Day: " << day << " / " << maxDays
         << "        Energy: " << player.getEnergy()
         << "        Money: " << player.getMoney() << "g" << endl;
    cout << "Joja Influence: " << jojaInfluence << endl;
    cout << "Location: " << locations[currentLocationIndex].getName() << endl;
 
    int completeCount = 0;
    for (size_t i = 0; i < bundles.size(); i++) {
        if (bundles[i].isComplete()) {
            completeCount++;
        }
    }
    cout << "Bundle Progress: " << completeCount << " / " << bundles.size() << " bundles complete" << endl;
}
 
void Game::displayMap() {
    cout << endl;
    cout << "Map:" << endl;
    cout << "[Farm] -- [Town Square] -- [Community Center] -- [Beach]" << endl;
    cout << "              |" << endl;
    cout << "          [Mines]        [JojaMart]" << endl;
    cout << endl;
    for (size_t i = 0; i < locations.size(); i++) {
        if ((int)i == currentLocationIndex) {
            cout << "* ";
        } else {
            cout << "  ";
        }
        locations[i].displayLocation();
    }
    cout << "* = You are here" << endl;
}
 
void Game::showMainMenu() {
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Move to another location" << endl;
    cout << "2. Talk to someone here" << endl;
    cout << "3. View inventory" << endl;
    cout << "4. View bundle progress" << endl;
    cout << "5. Do the special thing here (donate / JojaMart)" << endl;
    cout << "6. End day" << endl;
    cout << "7. Quit game" << endl;
    cout << "Choose an option: ";
}
 
int Game::findLocationIndex(string locationName) {
    for (size_t i = 0; i < locations.size(); i++) {
        if (locations[i].getName() == locationName) {
            return i;
        }
    }
    return -1;
}
 
int Game::findVillagerIndex(string villagerName) {
    for (size_t i = 0; i < villagers.size(); i++) {
        if (villagers[i].getName() == villagerName) {
            return i;
        }
    }
    return -1;
}
 
void Game::movePlayer() {
    cout << endl;
    cout << "Where would you like to go?" << endl;
    for (size_t i = 0; i < locations.size(); i++) {
        cout << i + 1 << ". " << locations[i].getName();
        if (!locations[i].isUnlocked()) {
            cout << " (LOCKED)";
        }
        cout << endl;
    }
    cout << "Choose a location: ";
    int choice;
    cin >> choice;
 
    if (choice < 1 || choice > (int)locations.size()) {
        cout << "That's not a valid location." << endl;
        return;
    }
 
    int index = choice - 1;
    if (!locations[index].isUnlocked()) {
        cout << "That location is still locked." << endl;
        return;
    }
 
    currentLocationIndex = index;
    cout << "You travel to " << locations[currentLocationIndex].getName() << "." << endl;
}
 
void Game::talkToCharacter() {
    string here = locations[currentLocationIndex].getName();
 
    vector<int> presentVillagers;
    for (size_t i = 0; i < villagers.size(); i++) {
        if (villagers[i].getHomeLocation() == here) {
            presentVillagers.push_back(i);
        }
    }
 
    if (presentVillagers.empty()) {
        cout << "There's no one to talk to here." << endl;
        return;
    }
 
    cout << endl;
    cout << "Characters nearby:" << endl;
    for (size_t i = 0; i < presentVillagers.size(); i++) {
        cout << i + 1 << ". " << villagers[presentVillagers[i]].getName() << endl;
    }
    cout << "Talk to who? ";
    int choice;
    cin >> choice;
 
    if (choice < 1 || choice > (int)presentVillagers.size()) {
        cout << "That's not a valid choice." << endl;
        return;
    }
 
    int vIndex = presentVillagers[choice - 1];
    villagers[vIndex].talk();
    player.spendEnergy(2);
 
    // Robin's special role: talking to her repairs the path to the Mines.
    if (villagers[vIndex].getName() == "Robin") {
        int minesIndex = findLocationIndex("Mines");
        if (minesIndex != -1 && !locations[minesIndex].isUnlocked()) {
            locations[minesIndex].unlockLocation();
            cout << "Robin clears the rubble blocking the Mines entrance." << endl;
            cout << "The Mines are now unlocked!" << endl;
        }
    }
 
    int cost = villagers[vIndex].getRewardCost();
    cout << "Would you like their item? (costs " << cost << "g) 1. Yes  2. No: ";
    int giftChoice;
    cin >> giftChoice;
 
    if (giftChoice == 1) {
        if (player.getMoney() >= cost) {
            player.setMoney(player.getMoney() - cost);
            Item reward = villagers[vIndex].giveReward();
            player.addItem(reward);
            cout << "You received " << reward.getName() << "!" << endl;
            cout << "Friendship with " << villagers[vIndex].getName()
                 << " is now " << villagers[vIndex].getFriendship() << "." << endl;
        } else {
            cout << "You don't have enough money for that." << endl;
        }
    }
}
 
void Game::viewInventory() {
    cout << endl;
    player.displayInventory();
}
 
void Game::viewBundles() {
    cout << endl;
    cout << "Final Bundles:" << endl;
    for (size_t i = 0; i < bundles.size(); i++) {
        bundles[i].describe();
    }
}
 
void Game::visitCommunityCenter() {
    if (locations[currentLocationIndex].getName() != "Community Center") {
        cout << "There's nothing special to do here." << endl;
        return;
    }
 
    if (player.getInventorySize() == 0) {
        cout << "You have nothing to donate right now." << endl;
        return;
    }
 
    cout << endl;
    cout << "Which bundle would you like to donate to?" << endl;
    for (size_t i = 0; i < bundles.size(); i++) {
        cout << i + 1 << ". ";
        bundles[i].describe();
    }
    cout << "Choose a bundle: ";
    int bundleChoice;
    cin >> bundleChoice;
 
    if (bundleChoice < 1 || bundleChoice > (int)bundles.size()) {
        cout << "That's not a valid bundle." << endl;
        return;
    }
 
    int bIndex = bundleChoice - 1;
    if (bundles[bIndex].isComplete()) {
        cout << "That bundle is already complete!" << endl;
        return;
    }
 
    cout << "Which item would you like to donate?" << endl;
    player.displayInventory();
    cout << "Choose an item (1-" << player.getInventorySize() << "): ";
    int itemChoice;
    cin >> itemChoice;
 
    if (itemChoice < 1 || itemChoice > player.getInventorySize()) {
        cout << "That's not a valid item." << endl;
        return;
    }
 
    string itemName = player.getItemNameAt(itemChoice - 1);
    player.removeItem(itemName);
    bundles[bIndex].addItem();
 
    cout << "You donated " << itemName << " to the " << bundles[bIndex].getBundleName() << " bundle!" << endl;
    bundles[bIndex].describe();
}
 
void Game::visitJojaMart() {
    if (locations[currentLocationIndex].getName() != "JojaMart") {
        cout << "There's nothing special to do here." << endl;
        return;
    }
 
    cout << endl;
    cout << "Morris says:" << endl;
    cout << "\"Why waste time gathering everything yourself? Joja can help... for a price.\"" << endl;
    cout << "1. Buy a bundle item directly - 75g" << endl;
    cout << "2. Buy a Joja Cola - 20g, restores 3 energy" << endl;
    cout << "3. Leave" << endl;
    cout << "Choose an option: ";
    int choice;
    cin >> choice;
 
    if (choice == 1) {
        if (player.getMoney() < 75) {
            cout << "You don't have enough money for that." << endl;
            return;
        }
        cout << "Which bundle needs an item?" << endl;
        for (size_t i = 0; i < bundles.size(); i++) {
            cout << i + 1 << ". ";
            bundles[i].describe();
        }
        int bundleChoice;
        cin >> bundleChoice;
        if (bundleChoice < 1 || bundleChoice > (int)bundles.size()) {
            cout << "That's not a valid bundle." << endl;
            return;
        }
        int bIndex = bundleChoice - 1;
        if (bundles[bIndex].isComplete()) {
            cout << "That bundle is already complete!" << endl;
            return;
        }
        player.setMoney(player.getMoney() - 75);
        bundles[bIndex].addItem();
        jojaInfluence++;
        cout << "Joja fills in an item for the " << bundles[bIndex].getBundleName() << " bundle." << endl;
        cout << "Joja Influence increased to " << jojaInfluence << "." << endl;
    } else if (choice == 2) {
        if (player.getMoney() < 20) {
            cout << "You don't have enough money for that." << endl;
            return;
        }
        player.setMoney(player.getMoney() - 20);
        player.setEnergy(player.getEnergy() + 3);
        jojaInfluence++;
        cout << "You bought a Joja Cola. Energy increased by 3." << endl;
        cout << "Joja Influence increased to " << jojaInfluence << "." << endl;
    } else {
        cout << "You leave JojaMart." << endl;
    }
}
 
void Game::endDay() {
    day++;
    int restedEnergy = player.getEnergy() + 30;
    if (restedEnergy > 100) {
        restedEnergy = 100;
    }
    player.setEnergy(restedEnergy);
    cout << endl;
    cout << "Night falls. You rest and recover some energy." << endl;
    cout << "Day " << day << " begins." << endl;
}
 
bool Game::allBundlesComplete() {
    for (size_t i = 0; i < bundles.size(); i++) {
        if (!bundles[i].isComplete()) {
            return false;
        }
    }
    return true;
}
 
bool Game::checkWin() {
    return allBundlesComplete() && day <= maxDays;
}
 
bool Game::checkLoss() {
    return day > maxDays && !allBundlesComplete();
}
 
void Game::displayEnding() {
    cout << endl;
    cout << "==================================================" << endl;
    if (allBundlesComplete()) {
        cout << "You completed the Final Bundle!" << endl;
        if (jojaInfluence == 0) {
            cout << "COMMUNITY HERO ENDING" << endl;
            cout << "The Community Center is restored fully through community effort." << endl;
        } else if (jojaInfluence <= 2) {
            cout << "QUIET RESTORATION ENDING" << endl;
            cout << "The Community Center is restored, but the town noticed Joja's influence." << endl;
        } else {
            cout << "JOJA SHORTCUT ENDING" << endl;
            cout << "The bundle is complete, but Joja has gained real power in the valley." << endl;
        }
    } else {
        int completeCount = 0;
        for (size_t i = 0; i < bundles.size(); i++) {
            if (bundles[i].isComplete()) {
                completeCount++;
            }
        }
        if (completeCount > 0) {
            cout << "ALMOST THERE ENDING" << endl;
            cout << "You made real progress, but ran out of days before finishing the bundle." << endl;
        } else {
            cout << "SEASON OVER ENDING" << endl;
            cout << "The season ended before you could get the Community Center back on track." << endl;
        }
    }
    cout << "==================================================" << endl;
}
 
void Game::processChoice(int choice) {
    if (choice == 1) {
        movePlayer();
    } else if (choice == 2) {
        talkToCharacter();
    } else if (choice == 3) {
        viewInventory();
    } else if (choice == 4) {
        viewBundles();
    } else if (choice == 5) {
        string here = locations[currentLocationIndex].getName();
        if (here == "Community Center") {
            visitCommunityCenter();
        } else if (here == "JojaMart") {
            visitJojaMart();
        } else {
            cout << "There's nothing special to do here." << endl;
        }
    } else if (choice == 6) {
        endDay();
    } else if (choice == 7) {
        gameOver = true;
        cout << "Thanks for playing! See you next season." << endl;
    } else {
        cout << "That's not a valid option, try again." << endl;
    }
}
 
void Game::run() {
    setupGame();
    cout << "Welcome to The Final Bundle!" << endl;
    cout << "The Community Center needs your help before Day " << maxDays << " ends." << endl;
 
    while (!gameOver) {
        displayDashboard();
        displayMap();
 
        if (allBundlesComplete()) {
            gameOver = true;
            break;
        }
        if (day > maxDays) {
            gameOver = true;
            break;
        }
 
        showMainMenu();
        int choice;
        cin >> choice;
        processChoice(choice);
 
        if (!gameOver && player.getEnergy() <= 0) {
            cout << endl;
            cout << "You're too exhausted to continue today." << endl;
            endDay();
            if (day > maxDays) {
                gameOver = true;
            }
        }
    }
 
    displayEnding();
}