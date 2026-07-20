#include "Game.h"
#include "Item.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Reads bundles.txt (format: name,itemsNeeded) and builds a vector of Bundle objects.
vector<Bundle> loadBundles(string filename) {
    // This vector stores all of the bundles loaded from the file.
    vector<Bundle> loaded;

    // Open the file so the program can read the bundle information.
    ifstream inFile(filename);

    // If the file cannot be opened, display a warning and return an empty vector.
    if (!inFile) {
        cout << "Warning: could not open " << filename << endl;
        return loaded;
    }

    string line;

    // Read the file one line at a time until there are no more lines.
    while (getline(inFile, line)) {
        // Skip blank lines so they do not cause errors when being processed.
        if (line.empty()) {
            continue;
        }

        // Use a stringstream to separate the bundle name and number of items.
        stringstream ss(line);
        string name;
        string neededStr;

        // Read the bundle name before the comma.
        getline(ss, name, ',');

        // Read the number of items needed after the comma.
        getline(ss, neededStr, ',');

        // Convert the number from a string to an integer.
        int needed = stoi(neededStr);

        // Create a Bundle object and add it to the vector.
        loaded.push_back(Bundle(name, needed));
    }

    // Close the file after all bundle information has been read.
    inFile.close();

    // Return the bundles that were loaded from the file.
    return loaded;
}

// Constructor initializes the game with the player's starting information.
Game::Game() : player("Riley", 100, 500, 1) {
    // The player begins at the first location in the locations vector.
    currentLocationIndex = 0;

    // The game starts on Day 1 and lasts for a maximum of 7 days.
    day = 1;
    maxDays = 7;

    // The player starts with no Joja influence.
    jojaInfluence = 0;

    // The game is active when it first starts.
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

// Adds spaces to the end of a string until it reaches the requested width.
// This helps keep the text-based dashboard aligned.
string Game::padRight(string text, int width) {
    while ((int)text.length() < width) {
        text = text + " ";
    }
    return text;
}

void Game::displayDashboard() {
    // Width of each location cell in the text-based map.
    const int CELL_WIDTH = 19;

    // Build the 2-row, 3-column grid map as plain text lines first.
    // Grid layout:
    //   Farm          Town Square   Beach
    //   Mines         Community Ctr JojaMart
    int gridOrder[6] = {0, 1, 2, 3, 4, 5};
    vector<string> mapLines;

    // Create the border used to separate each location on the map.
    string border = "+";
    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < CELL_WIDTH; i++) {
            border = border + "-";
        }
        border = border + "+";
    }

    mapLines.push_back(border);

    // Loop through each row of the map.
    for (int row = 0; row < 2; row++) {
        string nameLine = "|";
        string markLine = "|";

        // Loop through each column of the map.
        for (int col = 0; col < 3; col++) {
            // Convert the row and column position into a location index.
            int locIndex = gridOrder[row * 3 + col];

            // Get the name of the current location.
            string label = locations[locIndex].getName();

            // Hide the name of a locked location.
            if (!locations[locIndex].isUnlocked()) {
                label = "???";
            }

            // Add the location name to the map and align it to the cell width.
            nameLine = nameLine + padRight(" " + label, CELL_WIDTH) + "|";

            string mark = "";

            // Mark the player's current location with an X.
            if (locIndex == currentLocationIndex) {
                mark = " X";
            }

            // Add the location marker to the map.
            markLine = markLine + padRight(mark, CELL_WIDTH) + "|";
        }

        // Add the completed map lines to the vector.
        mapLines.push_back(nameLine);
        mapLines.push_back(markLine);
        mapLines.push_back(border);
    }

    // Explain what the X represents on the map.
    mapLines.push_back("X = your current location");

    // Convert the farm name to uppercase for the dashboard title.
    string upperName = "";
    for (size_t i = 0; i < farmName.length(); i++) {
        upperName = upperName + (char)toupper(farmName[i]);
    }

    // Build the player's status information as separate lines.
    vector<string> statLines;
    statLines.push_back("+----------------------------------+");
    statLines.push_back("|  " + upperName);
    statLines.push_back("+----------------------------------+");
    statLines.push_back("  Season Day .... " + to_string(day) + " / " + to_string(maxDays));

    // Create a visual energy bar based on the player's current energy.
    string energyBarLine = "  Energy ........ [";
    int energyBars = player.getEnergy() / 10;

    // Each '=' represents 10 energy, while '.' represents missing energy.
    for (int i = 0; i < 10; i++) {
        if (i < energyBars) {
            energyBarLine = energyBarLine + "=";
        } else {
            energyBarLine = energyBarLine + ".";
        }
    }

    energyBarLine = energyBarLine + "] " + to_string(player.getEnergy()) + "/100";
    statLines.push_back(energyBarLine);

    // Display the player's current money and Joja influence.
    statLines.push_back("  Coin Purse .... " + to_string(player.getMoney()) + "g");
    statLines.push_back("  Joja Favor .... " + to_string(jojaInfluence));

    // Count how many bundles have been completed.
    int completeCount = 0;
    for (size_t i = 0; i < bundles.size(); i++) {
        if (bundles[i].isComplete()) {
            completeCount++;
        }
    }

    // Display the number of completed bundles out of the total.
    statLines.push_back("  Bundles Done .. " + to_string(completeCount) + " / " + to_string(bundles.size()));
    statLines.push_back("+----------------------------------+");

    // Print the map and status panel next to each other.
    cout << endl;

    // Find the number of lines needed to print both panels completely.
    size_t maxLines = mapLines.size();
    if (statLines.size() > maxLines) {
        maxLines = statLines.size();
    }

    // Determine the width needed to keep the two panels separated.
    int mapColumnWidth = (int)border.length();

    // Print each line of the map and dashboard side by side.
    for (size_t i = 0; i < maxLines; i++) {
        string left = "";

        if (i < mapLines.size()) {
            left = mapLines[i];
        }

        cout << padRight(left, mapColumnWidth + 2);

        if (i < statLines.size()) {
            cout << statLines[i];
        }

        cout << endl;
    }

    // Display the current location and its description.
    cout << endl << "You are standing at: " << locations[currentLocationIndex].getName() << endl;
    locations[currentLocationIndex].displayLocation();
}

// Displays the actions the player can choose from.
void Game::showMainMenu() {
    cout << endl << "-- Choose an action --" << endl;
    cout << "  [t] Travel to a new place" << endl;
    cout << "  [s] Speak with someone here" << endl;
    cout << "  [b] Open your bag" << endl;
    cout << "  [p] Check bundle progress" << endl;
    cout << "  [h] Do whatever's special here" << endl;
    cout << "  [e] End the day" << endl;
    cout << "  [q] Quit" << endl;
    cout << "> ";
}

// Searches through all locations and returns the matching index.
int Game::findLocationIndex(string locationName) {
    for (size_t i = 0; i < locations.size(); i++) {
        if (locations[i].getName() == locationName) {
            return i;
        }
    }

    // Return -1 when the location cannot be found.
    return -1;
}

// Searches through all villagers and returns the matching index.
int Game::findVillagerIndex(string villagerName) {
    for (size_t i = 0; i < villagers.size(); i++) {
        if (villagers[i].getName() == villagerName) {
            return i;
        }
    }

    // Return -1 when the villager cannot be found.
    return -1;
}

// Allows the player to select and travel to another location.
void Game::movePlayer() {
    cout << endl;
    cout << "Where would you like to go?" << endl;

    // Display every location and whether it is currently locked.
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

    // Check that the user's choice is within the list of locations.
    if (choice < 1 || choice > (int)locations.size()) {
        cout << "That's not a valid location." << endl;
        return;
    }

    // Convert the user's numbered choice into a vector index.
    int index = choice - 1;

    // Prevent the player from traveling to locked locations.
    if (!locations[index].isUnlocked()) {
        cout << "That location is still locked." << endl;
        return;
    }

    // Update the player's current location.
    currentLocationIndex = index;
    cout << "You travel to " << locations[currentLocationIndex].getName() << "." << endl;
}

// Allows the player to talk with villagers located at the current location.
void Game::talkToCharacter() {
    string here = locations[currentLocationIndex].getName();

    // Store the indexes of villagers currently at the player's location.
    vector<int> presentVillagers;

    for (size_t i = 0; i < villagers.size(); i++) {
        if (villagers[i].getHomeLocation() == here) {
            presentVillagers.push_back(i);
        }
    }

    // If there are no villagers at the location, stop the function.
    if (presentVillagers.empty()) {
        cout << "There's no one to talk to here." << endl;
        return;
    }

    cout << endl;
    cout << "Characters nearby:" << endl;

    // Display only the villagers who are currently at this location.
    for (size_t i = 0; i < presentVillagers.size(); i++) {
        cout << i + 1 << ". " << villagers[presentVillagers[i]].getName() << endl;
    }

    cout << "Talk to who? ";
    int choice;
    cin >> choice;

    // Validate the selected villager.
    if (choice < 1 || choice > (int)presentVillagers.size()) {
        cout << "That's not a valid choice." << endl;
        return;
    }

    // Get the actual villager index from the list of villagers at this location.
    int vIndex = presentVillagers[choice - 1];

    // Talking to a villager uses a small amount of energy.
    villagers[vIndex].talk();
    player.spendEnergy(2);

    // Robin's special role: talking to her repairs the path to the Mines.
    if (villagers[vIndex].getName() == "Robin") {
        int minesIndex = findLocationIndex("Mines");

        // Unlock the Mines only if they are currently locked.
        if (minesIndex != -1 && !locations[minesIndex].isUnlocked()) {
            locations[minesIndex].unlockLocation();
            cout << "Robin clears the rubble blocking the Mines entrance." << endl;
            cout << "The Mines are now unlocked!" << endl;
        }
    }

    // Ask whether the player wants to purchase the villager's reward item.
    int cost = villagers[vIndex].getRewardCost();

    cout << "Would you like their item? (costs " << cost << "g) 1. Yes  2. No: ";
    int giftChoice;
    cin >> giftChoice;

    if (giftChoice == 1) {
        // Check whether the player has enough money before purchasing the item.
        if (player.getMoney() >= cost) {
            player.setMoney(player.getMoney() - cost);

            // Receive the reward item and add it to the player's inventory.
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

// Displays all items currently held by the player.
void Game::viewInventory() {
    cout << endl;
    player.displayInventory();
}

// Displays the progress of every bundle.
void Game::viewBundles() {
    cout << endl;
    cout << "Final Bundles:" << endl;

    for (size_t i = 0; i < bundles.size(); i++) {
        bundles[i].describe();
    }
}

// Allows the player to donate an inventory item to a bundle.
void Game::visitCommunityCenter() {
    // The donation action can only be performed at the Community Center.
    if (locations[currentLocationIndex].getName() != "Community Center") {
        cout << "There's nothing special to do here." << endl;
        return;
    }

    // Prevent the player from trying to donate when their inventory is empty.
    if (player.getInventorySize() == 0) {
        cout << "You have nothing to donate right now." << endl;
        return;
    }

    cout << endl;
    cout << "Which bundle would you like to donate to?" << endl;

    // Display all available bundles so the player can choose one.
    for (size_t i = 0; i < bundles.size(); i++) {
        cout << i + 1 << ". ";
        bundles[i].describe();
    }

    cout << "Choose a bundle: ";
    int bundleChoice;
    cin >> bundleChoice;

    // Validate the bundle selection.
    if (bundleChoice < 1 || bundleChoice > (int)bundles.size()) {
        cout << "That's not a valid bundle." << endl;
        return;
    }

    // Convert the user's choice into a vector index.
    int bIndex = bundleChoice - 1;

    // Do not allow additional items to be donated to a completed bundle.
    if (bundles[bIndex].isComplete()) {
        cout << "That bundle is already complete!" << endl;
        return;
    }

    cout << "Which item would you like to donate?" << endl;
    player.displayInventory();

    cout << "Choose an item (1-" << player.getInventorySize() << "): ";
    int itemChoice;
    cin >> itemChoice;

    // Validate the selected inventory item.
    if (itemChoice < 1 || itemChoice > player.getInventorySize()) {
        cout << "That's not a valid item." << endl;
        return;
    }

    // Get the selected item's name, remove it from the inventory, and add it to the bundle.
    string itemName = player.getItemNameAt(itemChoice - 1);
    player.removeItem(itemName);
    bundles[bIndex].addItem();

    cout << "You donated " << itemName << " to the " << bundles[bIndex].getBundleName() << " bundle!" << endl;

    // Display the updated progress of the bundle.
    bundles[bIndex].describe();
}

// Allows the player to use the special actions available at JojaMart.
void Game::visitJojaMart() {
    // The JojaMart actions can only be used while at JojaMart.
    if (locations[currentLocationIndex].getName() != "JojaMart") {
        cout << "There's nothing special to do here." << endl;
        return;
    }

    cout << endl;
    cout << "The clerk barely looks up from the register." << endl;
    cout << "\"Running behind on that bundle? We can fix that. Costs extra, obviously.\"" << endl;
    cout << "1. Pay for a bundle item, no questions asked - 75g" << endl;
    cout << "2. Grab an energy drink off the shelf - 20g, restores 3 energy" << endl;
    cout << "3. Walk out" << endl;
    cout << "Choose an option: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        // The player must have enough money to purchase a bundle item.
        if (player.getMoney() < 75) {
            cout << "The clerk eyes your wallet. \"Come back when you've got the gold.\"" << endl;
            return;
        }

        cout << "Which bundle needs an item?" << endl;

        // Display the bundles that can receive the purchased item.
        for (size_t i = 0; i < bundles.size(); i++) {
            cout << i + 1 << ". ";
            bundles[i].describe();
        }

        int bundleChoice;
        cin >> bundleChoice;

        // Validate the bundle choice.
        if (bundleChoice < 1 || bundleChoice > (int)bundles.size()) {
            cout << "That's not a valid bundle." << endl;
            return;
        }

        int bIndex = bundleChoice - 1;

        // Do not allow Joja to add items to an already completed bundle.
        if (bundles[bIndex].isComplete()) {
            cout << "That bundle is already complete!" << endl;
            return;
        }

        // Pay for the item and increase Joja's influence.
        player.setMoney(player.getMoney() - 75);
        bundles[bIndex].addItem();
        jojaInfluence++;

        cout << "An item shows up for the " << bundles[bIndex].getBundleName() << " bundle, no explanation given." << endl;
        cout << "Joja Favor is now " << jojaInfluence << "." << endl;

    } else if (choice == 2) {
        // Check whether the player has enough money for the energy drink.
        if (player.getMoney() < 20) {
            cout << "You're a few gold short." << endl;
            return;
        }

        // Purchase the drink, restore energy, and increase Joja influence.
        player.setMoney(player.getMoney() - 20);
        player.setEnergy(player.getEnergy() + 3);
        jojaInfluence++;

        cout << "You down the drink. It works, somehow. Energy up by 3." << endl;
        cout << "Joja Favor is now " << jojaInfluence << "." << endl;

    } else {
        // Any other option causes the player to leave without buying anything.
        cout << "You leave without buying anything." << endl;
    }
}

// Ends the current day and restores some of the player's energy.
void Game::endDay() {
    // Move to the next day.
    day++;

    // Restore 30 energy after resting.
    int restedEnergy = player.getEnergy() + 30;

    // Prevent energy from exceeding the maximum of 100.
    if (restedEnergy > 100) {
        restedEnergy = 100;
    }

    player.setEnergy(restedEnergy);

    cout << endl;
    cout << "Night falls. You rest and recover some energy." << endl;
    cout << "Day " << day << " begins." << endl;
}

// Checks whether every bundle has been completed.
bool Game::allBundlesComplete() {
    for (size_t i = 0; i < bundles.size(); i++) {
        // If even one bundle is incomplete, the player has not won yet.
        if (!bundles[i].isComplete()) {
            return false;
        }
    }

    // Every bundle is complete.
    return true;
}

// The player wins if all bundles are complete before the time limit ends.
bool Game::checkWin() {
    return allBundlesComplete() && day <= maxDays;
}

// The player loses if the maximum number of days has passed without completing all bundles.
bool Game::checkLoss() {
    return day > maxDays && !allBundlesComplete();
}

// Displays the ending based on the player's progress and Joja influence.
void Game::displayEnding() {
    cout << endl;
    cout << "+----------------------------------------+" << endl;

    // First determine whether the player completed all of the bundles.
    if (allBundlesComplete()) {
        cout << "You completed the Final Bundle!" << endl;

        // Different endings are determined by how much Joja influence the player gained.
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
        // Count the number of bundles completed before the game ended.
        int completeCount = 0;

        for (size_t i = 0; i < bundles.size(); i++) {
            if (bundles[i].isComplete()) {
                completeCount++;
            }
        }

        // Give a different ending based on how much progress the player made.
        if (completeCount > 0) {
            cout << "ALMOST THERE ENDING" << endl;
            cout << "You made real progress, but ran out of days before finishing the bundle." << endl;
        } else {
            cout << "SEASON OVER ENDING" << endl;
            cout << "The season ended before you could get the Community Center back on track." << endl;
        }
    }

    cout << "+----------------------------------------+" << endl;
}

// Processes the character entered by the player and calls the correct game action.
void Game::processChoice(char choice) {
    // Each letter corresponds to a different action in the main menu.
    if (choice == 't') {
        movePlayer();

    } else if (choice == 's') {
        talkToCharacter();

    } else if (choice == 'b') {
        viewInventory();

    } else if (choice == 'p') {
        viewBundles();

    } else if (choice == 'h') {
        // The special action depends on the player's current location.
        string here = locations[currentLocationIndex].getName();

        if (here == "Community Center") {
            visitCommunityCenter();

        } else if (here == "JojaMart") {
            visitJojaMart();

        } else {
            cout << "There's nothing special to do here." << endl;
        }

    } else if (choice == 'e') {
        endDay();

    } else if (choice == 'q') {
        // Set gameOver to true so the main game loop ends.
        gameOver = true;
        cout << "Thanks for playing! See you next season." << endl;

    } else {
        // Inform the player when an invalid menu option is entered.
        cout << "Not a valid choice — try one of the letters shown." << endl;
    }
}

// Runs the main game loop.
void Game::run() {
    // Set up all locations, villagers, and bundles before starting the game.
    setupGame();

    cout << "Welcome to The Final Bundle!" << endl;
    cout << "Name your farm: ";

    // Read the farm name entered by the player.
    getline(cin, farmName);

    // Use a default name if the player does not enter one.
    if (farmName.empty()) {
        farmName = "Riley's Farm";
    }

    cout << "The Community Center needs your help before Day " << maxDays << " ends." << endl;

    // Continue running the game until the player wins, loses, or quits.
    while (!gameOver) {
        // Display the current game state before each action.
        displayDashboard();

        // End the game when all bundles have been completed.
        if (allBundlesComplete()) {
            gameOver = true;
            break;
        }

        // End the game when the maximum number of days has passed.
        if (day > maxDays) {
            gameOver = true;
            break;
        }

        // Show the available actions and get the player's choice.
        showMainMenu();

        char choice;
        cin >> choice;

        // Perform the action selected by the player.
        processChoice(choice);

        // Automatically end the day if the player runs out of energy.
        if (!gameOver && player.getEnergy() <= 0) {
            cout << endl;
            cout << "You're too exhausted to continue today." << endl;

            endDay();

            // If the player runs out of time, end the game.
            if (day > maxDays) {
                gameOver = true;
            }
        }
    }

    // Display the final ending after the main game loop ends.
    displayEnding();
}