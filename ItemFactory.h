#pragma once
#include "Item.h"
#include <string>

// Factory pattern: centralises object creation for all item types
class ItemFactory {
public:
    // Create an Item from a type string like "Axe", "Dirt", etc.
    static Item createItem(const std::string& typeName, int quantity = 1);

    // Create an Item directly from enum
    static Item createItem(ItemType type, int quantity = 1);
};
