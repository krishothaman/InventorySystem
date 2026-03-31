/*
 * ============================================================================
 *  Minecraft-Inspired Inventory System — main.cpp
 *  C++17  |  OOP Design (Item / Inventory / ItemFactory)
 * ============================================================================
 */

#include <iostream>
#include <limits>
#include <string>
#include "Inventory.h"
#include "ItemFactory.h"

// 
// Helpers
// 

// Flush bad input and optionally show a message
void clearInput(const std::string& msg = "") {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!msg.empty()) std::cout << msg;
}

// Read a validated integer in [lo, hi]
int readInt(const std::string& prompt, int lo, int hi) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= lo && val <= hi) {
            clearInput();   // eat the trailing newline
            return val;
        }
        clearInput("  [!] Invalid input. Please enter a number between "
                   + std::to_string(lo) + " and " + std::to_string(hi) + ".\n");
    }
}

// 
// UI Helpers
// 
void printBanner() {
    std::cout << "\n";
    std::cout << "  ======================================================\n";
    std::cout << "                 MINECRAFT INVENTORY SYSTEM             \n";
    std::cout << "  ======================================================\n";
}

void printMainMenu() {
    std::cout << "\n";
    std::cout << "  --- MAIN MENU ---\n";
    std::cout << "  1. Add Item\n";
    std::cout << "  2. Remove Item\n";
    std::cout << "  3. Use Item\n";
    std::cout << "  4. Display Inventory\n";
    std::cout << "  5. Check Available Space\n";
    std::cout << "  6. Exit\n";
    std::cout << "  -----------------\n";
}

// Map menu choice 1-7 → ItemType
ItemType pickItemType() {
    std::cout << "\n  Select item type:\n";
    std::cout << "    1. Axe    (Tool  | Durability: 100)\n";
    std::cout << "    2. Sword  (Tool  | Durability: 100)\n";
    std::cout << "    3. Shovel (Tool  | Durability: 100)\n";
    std::cout << "    4. Bow    (Tool  | Durability: 100)\n";
    std::cout << "    5. Dirt   (Block | Stackable)\n";
    std::cout << "    6. Stone  (Block | Stackable)\n";
    std::cout << "    7. Arrow  (Ammo  | Stackable)\n";

    int choice = readInt("  Your choice (1-7): ", 1, 7);
    switch (choice) {
        case 1: return ItemType::AXE;
        case 2: return ItemType::SWORD;
        case 3: return ItemType::SHOVEL;
        case 4: return ItemType::BOW;
        case 5: return ItemType::DIRT;
        case 6: return ItemType::STONE;
        case 7: return ItemType::ARROW;
        default: return ItemType::UNKNOWN;
    }
}

// 
// Action: Add Item
// 
void doAddItem(Inventory& inv) {
    if (inv.isFull()) {
        std::cout << "\n  [!] Inventory is full! Remove something first.\n";
        return;
    }

    ItemType type   = pickItemType();
    int      amount = readInt("  Enter quantity to add: ", 1, 25);

    inv.addItem(type, amount);
}

// 
// Action: Remove Item
// 
void doRemoveItem(Inventory& inv) {
    if (inv.getItemCount() == 0) {
        std::cout << "\n  [!] Inventory is already empty.\n";
        return;
    }

    inv.displayInventory();

    std::string itemName;
    std::cout << "\n  Enter item name to remove (exact, e.g. Axe, Dirt): ";
    std::cin >> itemName;
    clearInput();

    int amount = readInt("  Enter quantity to remove: ", 1, 999);

    inv.removeItem(itemName, amount);
}

// 
// Action: Use Item
//
void doUseItem(Inventory& inv) {
    if (inv.getItemCount() == 0) {
        std::cout << "\n  [!] Inventory is empty — nothing to use.\n";
        return;
    }

    inv.displayInventory();

    std::string itemName;
    std::cout << "\n  Enter item name to use (exact, e.g. Sword, Bow): ";
    std::cin >> itemName;
    clearInput();

    inv.useItem(itemName);
}

// ─────────────────────────────────────────────────────────────────────────────
// main — game loop
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    Inventory inv;
    bool running = true;

    printBanner();

    while (running) {
        printMainMenu();
        std::cout << "  Capacity: " << inv.getItemCount()
                  << "/" << inv.getMaxCapacity() << "\n";

        int choice = readInt("\n  Your choice (1-6): ", 1, 6);

        switch (choice) {
            case 1: doAddItem(inv);    break;
            case 2: doRemoveItem(inv); break;
            case 3: doUseItem(inv);    break;
            case 4: inv.displayInventory(); break;

            case 5:
                std::cout << "\n  Available space: "
                          << inv.getAvailableSpace() << " slot(s) / "
                          << inv.getMaxCapacity() << " max.\n";
                break;

            case 6:
                std::cout << "\n  Goodbye! Your inventory has been closed.\n\n";
                running = false;
                break;
        }
    }

    return 0;
}
