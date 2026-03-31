#include "ItemFactory.h"
#include <stdexcept>

Item ItemFactory::createItem(const std::string& typeName, int quantity) {
    ItemType type = Item::stringToType(typeName);
    if (type == ItemType::UNKNOWN)
        throw std::invalid_argument("Unknown item type: " + typeName);
    return Item(typeName, type, quantity);
}

Item ItemFactory::createItem(ItemType type, int quantity) {
    if (type == ItemType::UNKNOWN)
        throw std::invalid_argument("Cannot create item of UNKNOWN type.");
    std::string name = Item::typeToString(type);
    return Item(name, type, quantity);
}
