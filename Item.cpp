#include "Item.h"
#include <iomanip>
#include <stdexcept>

// 
// Constructor
// 
Item::Item(const std::string& name, ItemType type, int qty)
    : itemName(name), itemType(type)
{
    if (qty <= 0) throw std::invalid_argument("Quantity must be positive.");

    quantity  = qty;
    isDurable = typeIsDurable(type);
    durability = isDurable ? 100 : -1;   // -1 = "no durability concept"
}

// 
// Quantity management
// 
void Item::addQuantity(int amount) {
    if (amount <= 0) throw std::invalid_argument("Amount to add must be positive.");
    quantity += amount;
}

bool Item::removeQuantity(int amount) {
    if (amount <= 0) throw std::invalid_argument("Amount to remove must be positive.");
    if (amount > quantity) return false;
    quantity -= amount;
    return true;
}

// 
// Durability
// 
bool Item::use() {
    if (!isDurable) return true;   // consumables: "use" has no durability effect
    durability -= 25;
    if (durability < 0) durability = 0;
    return durability > 0;         // false → item just broke
}

bool Item::isIntact() const {
    if (!isDurable) return true;
    return durability > 0;
}

//
// Display
// 
void Item::displayItem(int index) const {
    std::cout << "  " << index << ". "
              << std::left << std::setw(8) << itemName
              << " | Qty: " << std::setw(3) << quantity;

    if (isDurable) {
        std::cout << " | Durability: " << durability << "/100";
        // Visual durability bar
        int filled = durability / 10;
        std::cout << "  [";
        for (int i = 0; i < 10; ++i)
            std::cout << (i < filled ? '#' : '-');
        std::cout << "]";
    } else {
        std::cout << " | Stack Limited (no durability)";
    }
    std::cout << "\n";
}

// 
// Static helpers
// 
std::string Item::typeToString(ItemType type) {
    switch (type) {
        case ItemType::AXE:    return "Axe";
        case ItemType::SWORD:  return "Sword";
        case ItemType::SHOVEL: return "Shovel";
        case ItemType::DIRT:   return "Dirt";
        case ItemType::STONE:  return "Stone";
        case ItemType::BOW:    return "Bow";
        case ItemType::ARROW:  return "Arrow";
        default:               return "Unknown";
    }
}

ItemType Item::stringToType(const std::string& name) {
    if (name == "Axe")    return ItemType::AXE;
    if (name == "Sword")  return ItemType::SWORD;
    if (name == "Shovel") return ItemType::SHOVEL;
    if (name == "Dirt")   return ItemType::DIRT;
    if (name == "Stone")  return ItemType::STONE;
    if (name == "Bow")    return ItemType::BOW;
    if (name == "Arrow")  return ItemType::ARROW;
    return ItemType::UNKNOWN;
}

bool Item::typeIsDurable(ItemType type) {
    switch (type) {
        case ItemType::AXE:
        case ItemType::SWORD:
        case ItemType::SHOVEL:
        case ItemType::BOW:
            return true;
        default:
            return false;
    }
}
