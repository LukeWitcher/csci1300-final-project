#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Character.h"
#include "Farmer.h"
#include "Villager.h"
#include "Bundle.h"
using namespace std;

// Reads bundles.txt (format: name,itemsNeeded) and builds a vector of Bundle objects
vector<Bundle> loadBundles(string filename) {
    vector<Bundle> bundles;
    ifstream inFile(filename);

    if (!inFile) {
        cout << "Warning: could not open " << filename << endl;
        return bundles;
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
        bundles.push_back(Bundle(name, needed));
    }

    inFile.close();
    return bundles;
}

int main() {
    // Set up starting game state
    Farmer player("Riley", 100, 500, 1);
    Villager robin("Robin", "Wood");

    // Load bundles from file instead of hardcoding one
    vector<Bundle> bundles = loadBundles("bundles.txt");
    cout << "Loaded " << bundles.size() << " bundles from bundles.txt" << endl;

    int choice = -1;

    cout << "Welcome to The Final Bundle!" << endl;

    while (choice != 5) {
        cout << endl;
        cout << "--- Main Menu ---" << endl;
        cout << "1. View farmer status" << endl;
        cout << "2. Talk to a villager" << endl;
        cout << "3. Collect an item for a bundle" << endl;
        cout << "4. Check bundle progress" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            player.describe();
        } else if (choice == 2) {
            robin.talk();
            robin.receiveGift("Wood");
        } else if (choice == 3) {
            if (bundles.empty()) {
                cout << "No bundles loaded." << endl;
            } else {
                cout << "Which bundle? (enter number)" << endl;
                for (size_t i = 0; i < bundles.size(); i++) {
                    cout << i + 1 << ". " << bundles[i].getBundleName() << endl;
                }
                int bundleChoice;
                cin >> bundleChoice;
                if (bundleChoice >= 1 && bundleChoice <= (int)bundles.size()) {
                    player.collectItem();
                    bundles[bundleChoice - 1].addItem();
                    cout << "You collected an item for the "
                         << bundles[bundleChoice - 1].getBundleName()
                         << " bundle." << endl;
                } else {
                    cout << "That's not a valid bundle." << endl;
                }
            }
        } else if (choice == 4) {
            for (size_t i = 0; i < bundles.size(); i++) {
                bundles[i].describe();
            }
        } else if (choice == 5) {
            cout << "Thanks for playing! See you next season." << endl;
        } else {
            cout << "That's not a valid option, try again." << endl;
        }
    }

    return 0;
}