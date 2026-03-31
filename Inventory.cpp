#include "Inventory.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// 
// Constructor
// 
Inventory::Inventory() : currentCapacity(0) {}

// 
// Internal: find item index by name
// 
int Inventory::findItemIndex(const std::string& itemName) const {
    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        if (items[i].getItemName() == itemName)
            return i;
    }
    return -1;
}

// 
// addItem
//   - Durable tools use 1 slot each (they don't stack)
//   - Consumables/blocks use 1 slot total regardless of quantity (they stack)
// 
bool Inventory::addItem(ItemType type, int amount) {
    if (amount <= 0) {
        std::cout << "\n  [!] Quantity must be at least 1.\n";
        return false;
    }

    std::string name = Item::typeToString(type);
    bool durable     = Item::typeIsDurable(type);

    // ── Durable tools: each unit takes 1 slot
    if (durable) {
        if (currentCapacity + amount > maxCapacity) {
            std::cout << "\n  [!] Cannot add " << amount << " " << name
                      << "(s). Inventory too full! Available space: "
                      << getAvailableSpace() << " slot(s).\n";
            return false;
        }
        // Each tool is its own slot entry
        for (int i = 0; i < amount; ++i) {
            items.emplace_back(name, type, 1);
            ++currentCapacity;
        }
        std::cout << "\n  [+] Added " << amount << " " << name
                  << "(s) to inventory.\n";
        return true;
    }

    // ── Stackable items: all units share 1 slot (or add to existing)
    int idx = findItemIndex(name);

    if (idx == -1) {
        // New stackable item: needs 1 new slot
        if (currentCapacity >= maxCapacity) {
            std::cout << "\n  [!] Cannot add " << name
                      << ". Inventory full! Available space: 0 slot(s).\n";
            return false;
        }
        items.emplace_back(name, type, amount);
        ++currentCapacity;
    } else {
        // Stack onto existing slot (no extra slot needed)
        items[idx].addQuantity(amount);
    }

    std::cout << "\n  [+] Added " << amount << " " << name
              << "(s) to inventory.\n";
    return true;
}

// 
// removeItem
// 
bool Inventory::removeItem(const std::string& itemName, int amount) {
    if (amount <= 0) {
        std::cout << "\n  [!] Quantity to remove must be at least 1.\n";
        return false;
    }

    int idx = findItemIndex(itemName);
    if (idx == -1) {
        std::cout << "\n  [!] Item \"" << itemName << "\" not found in inventory.\n";
        return false;
    }

    Item& item = items[idx];

    if (amount > item.getQuantity()) {
        std::cout << "\n  [!] Cannot remove " << amount << " " << itemName
                  << "(s). Only " << item.getQuantity() << " available.\n";
        return false;
    }

    item.removeQuantity(amount);
    std::cout << "\n  [-] Removed " << amount << " " << itemName
              << "(s) from inventory.\n";

    if (item.getQuantity() == 0) {
        items.erase(items.begin() + idx);
        --currentCapacity;
        std::cout << "      (Last " << itemName << " removed — slot freed.)\n";
    }

    return true;
}

// 
// useItem
// 
void Inventory::useItem(const std::string& itemName) {
    int idx = findItemIndex(itemName);
    if (idx == -1) {
        std::cout << "\n  [!] Item \"" << itemName << "\" not found in inventory.\n";
        return;
    }

    Item& item = items[idx];

    if (!item.getIsDurable()) {
        std::cout << "\n  [!] " << itemName
                  << " is a consumable/block and cannot be 'used' this way.\n"
                  << "      (Use Remove Item to consume it.)\n";
        return;
    }

    bool stillAlive = item.use();

    if (stillAlive) {
        std::cout << "\n  [*] Used " << itemName
                  << ". Durability: " << item.getDurability() << "/100\n";
        // Visual bar
        int filled = item.getDurability() / 10;
        std::cout << "      Durability bar: [";
        for (int i = 0; i < 10; ++i)
            std::cout << (i < filled ? '#' : '-');
        std::cout << "]\n";
    } else {
        std::cout << "\n  [X] " << itemName
                  << " broke and was removed from inventory!\n";
        items.erase(items.begin() + idx);
        --currentCapacity;
    }
}

// 
// displayInventory
// 
void Inventory::displayInventory() const {
    const std::string line(55, '=');
    std::cout << "\n" << line << "\n";
    std::cout << "              === INVENTORY ===\n";
    std::cout << line << "\n";
    std::cout << "  Capacity  : " << currentCapacity << "/" << maxCapacity << "\n";
    std::cout << "  Available : " << getAvailableSpace() << " slot(s)\n";
    std::cout << line << "\n";

    if (items.empty()) {
        std::cout << "  (Inventory is empty)\n";
    } else {
        std::cout << "  Items:\n";
        for (int i = 0; i < static_cast<int>(items.size()); ++i) {
            items[i].displayItem(i + 1);
        }
    }

    std::cout << line << "\n";
}

// 
// clearBrokenItems  (utility — not strictly needed in this flow but available)
// 
void Inventory::clearBrokenItems() {
    int removed = 0;
    for (int i = static_cast<int>(items.size()) - 1; i >= 0; --i) {
        if (items[i].getQuantity() == 0 || !items[i].isIntact()) {
            items.erase(items.begin() + i);
            --currentCapacity;
            ++removed;
        }
    }
    if (removed > 0)
        std::cout << "\n  [*] Cleared " << removed << " broken/empty item(s).\n";
}
