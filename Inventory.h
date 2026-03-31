#pragma once
#include "Item.h"
#include <vector>
#include <string>

// Manages all items in the player's inventory
class Inventory {
private:
    std::vector<Item> items;
    int currentCapacity;          // total number of item SLOTS used
    static const int maxCapacity = 25;

    // Internal helper: find item index by name (-1 if not found)
    int findItemIndex(const std::string& itemName) const;

public:
    // Constructor
    Inventory();

    // ── Core operations 
    bool addItem(ItemType type, int amount = 1);
    bool removeItem(const std::string& itemName, int amount = 1);
    void useItem(const std::string& itemName);

    // ── Queries 
    void displayInventory()   const;
    bool isFull()             const { return currentCapacity >= maxCapacity; }
    int  getItemCount()       const { return currentCapacity;               }
    int  getAvailableSpace()  const { return maxCapacity - currentCapacity; }
    int  getMaxCapacity()     const { return maxCapacity;                   }

    // ── Maintenance 
    void clearBrokenItems();   // Remove any item with quantity == 0
};
