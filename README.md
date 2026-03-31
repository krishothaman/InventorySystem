⛏ Minecraft Inventory System — C++

A simple inventory system using OOPS concepts


Features

| 25-slot inventory capacity |
| 7 item types (Axe, Sword, Shovel, Bow, Dirt, Stone, Arrow) |
| Stackable consumables / blocks |
| Durability system (100 → 75 → 50 → 25 → 0 → broken) |
| Auto-remove broken tools |
| Capacity overflow protection |
| Full input validation |
| Visual durability bar |

---

## Project Structure

```
InventorySystem/
├── Item.h / Item.cpp          <- Base item class + enum
├── Inventory.h / Inventory.cpp <- Inventory manager
├── ItemFactory.h / ItemFactory.cpp <- Factory pattern
├── main.cpp                   <- Game loop & UI
└── README.md
```



Build & Run

```powershell
# Compile (single command)
g++ -std=c++17 Item.cpp Inventory.cpp ItemFactory.cpp main.cpp -o InventorySystem.exe

# Run
.\InventorySystem.exe
```



## Item Rules

| Item | Type | Durability | Stackable |
|------|------|-----------|-----------|
| Axe | Tool | 100 (−25/use) | No (1 slot each) |
| Sword | Tool | 100 (−25/use) | No (1 slot each) |
| Shovel | Tool | 100 (−25/use) | No (1 slot each) |
| Bow | Tool | 100 (−25/use) | No (1 slot each) |
| Arrow | Ammo | N/A | Yes (1 slot, any qty) |
| Dirt | Block | N/A | Yes (1 slot, any qty) |
| Stone | Block | N/A | Yes (1 slot, any qty) |



Sample Session

```
⛏  MINECRAFT INVENTORY SYSTEM  ⛏

  MAIN MENU
  1. Add Item
  2. Remove Item
  3. Use Item
  4. Display Inventory
  5. Check Available Space
  6. Exit

  Capacity: 0/25
  Your choice: 1
  Select item type: 1 (Axe)
  Quantity: 1
  [+] Added 1 Axe(s) to inventory.

  ...

  === INVENTORY ===
  Capacity  : 1/25
  Available : 24 slot(s)
  Items:
    1. Axe      | Qty: 1   | Durability: 75/100  [#######---]
```



OOP Design

```
Item  (base class)
  ├── getters / setters
  ├── use()          → reduces durability by 25
  ├── addQuantity()  → stack items
  └── removeQuantity()

Inventory
  ├── addItem()      → stacking + capacity check
  ├── removeItem()   → quantity validation
  ├── useItem()      → delegates to Item::use(), auto-removes broken
  └── displayInventory()

ItemFactory  (factory pattern)
  └── createItem(type) → returns a ready Item object
```
