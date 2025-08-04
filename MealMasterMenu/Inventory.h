#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

// Struct representing a single item in inventory with its name and current quantity
struct InventoryItem {
    std::string name;   // Name of the inventory item
    int quantity;       // Quantity currently available
};

class Inventory {
    std::vector<InventoryItem> items;  // Dynamic list to store all inventory items

public:
    // Check if an item exists by name (case-insensitive)
    bool itemExists(const std::string& itemName) const;

    // Loads inventory items from a text file
    // Clears current items before loading new data
    void loadFromFile(const std::string& filename);

    // Saves current inventory items to a text file
    void saveToFile(const std::string& filename);

    // Displays the inventory list and quantities to the console
    void displayInventory() const;

    // Updates quantity of an existing item by adding 'change' (can be positive or negative)
    // Adds a new item with given quantity if item not found
    void updateQuantity(const std::string& name, int change);

    // Sets the quantity explicitly for an item (overwrites current quantity or adds new item)
    void setQuantity(const std::string& name, int quantity);
};

#endif
