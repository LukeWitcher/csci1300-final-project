#ifndef BUNDLE_H
#define BUNDLE_H

#include <string>
using namespace std;

// Bundle represents one Community Center bundle (e.g. the Boiler

class Bundle {
private:
    string bundleName;
    int itemsNeeded;
    int itemsCollected;

public:
    Bundle(string n, int needed);

    // Getters
    string getBundleName();
    int getItemsNeeded();
    int getItemsCollected();

    // Behavior
    void addItem();
    bool isComplete();
    void describe();
};

#endif