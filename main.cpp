#include <iostream>
#include <string>
#include "Character.h"
#include "Farmer.h"
#include "Villager.h"
#include "Bundle.h"
using namespace std;

int main() {
    // Set up starting game state
    Farmer player("Riley", 100, 500, 1);
    Villager robin("Robin", "Wood");
    Bundle boilerRoom("Boiler Room", 5);

    int choice = -1;

    cout << "Welcome to The Final Bundle!" << endl;

    while (choice != 5) {
        cout << endl;
        cout << "--- Main Menu ---" << endl;
        cout << "1. View farmer status" << endl;
        cout << "2. Talk to a villager" << endl;
        cout << "3. Collect an item for the Boiler Room bundle" << endl;
        cout << "4. Check bundle progress" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            player.describe();
        } else if (choice == 2) {
            robin.talk();
            // Placeholder: giving a gift is not fully implemented yet
            robin.receiveGift("Wood");
        } else if (choice == 3) {
            // Placeholder: real item collection will check the farmer's
            // inventory and location once those systems exist
            player.collectItem();
            boilerRoom.addItem();
            cout << "You collected an item for the Boiler Room bundle." << endl;
        } else if (choice == 4) {
            boilerRoom.describe();
        } else if (choice == 5) {
            cout << "Thanks for playing! See you next season." << endl;
        } else {
            cout << "That's not a valid option, try again." << endl;
        }
    }

    return 0;
}