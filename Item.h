#pragma once
#include <string>
#include <iostream>

// Enum for all supported item types
enum class ItemType {
    AXE,
    SWORD,
    SHOVEL,
    DIRT,
    STONE,
    BOW,
    ARROW,
    UNKNOWN
};

// Base class representing a single inventory item
class Item {
private:
    std::string itemName;
    ItemType    itemType;
    int         quantity;
    int         durability;     // 0–100; -1 means "no durability" (stackable consumables)
    bool        isDurable;      // true  → tool (has durability)
                                // false → consumable/block (stackable)

public:
    // Constructor
    Item(const std::string& name, ItemType type, int qty = 1);

    // ── Getters 
    std::string  getItemName()   const { return itemName;   }
    ItemType     getItemType()   const { return itemType;   }
    int          getQuantity()   const { return quantity;   }
    int          getDurability() const { return durability; }
    bool         getIsDurable()  const { return isDurable;  }

    // ── Quantity management 
    void addQuantity(int amount);
    bool removeQuantity(int amount);   // returns false if not enough

    // ── Durability 
    bool use();           // Reduce durability by 25; returns false when item breaks
    bool isIntact() const;// true if item still has durability > 0 (or is non-durable)

    // ── Display 
    void displayItem(int index) const;

    // ── Static helpers 
    static std::string  typeToString(ItemType type);
    static ItemType     stringToType(const std::string& name);
    static bool         typeIsDurable(ItemType type);
};
