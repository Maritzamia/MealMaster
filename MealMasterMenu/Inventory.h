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
private:
    std::vector<InventoryItem> items;  // Dynamic list to store all inventory items

    // Helper functions for case-insensitive comparison and whitespace trimming
    std::string toLower(const std::string& str) const;
    std::string trim(const std::string& str) const;

public:
    // Check if an item exists by name (case-insensitive, trimmed)
    bool itemExists(const std::string& itemName) const;

    // Load inventory items from a text file
    void loadFromFile(const std::string& filename);

    // Save current inventory items to a text file
    void saveToFile(const std::string& filename);

    // Display the inventory list and quantities to the console
    void displayInventory() const;

    // Update quantity of an item (adds or subtracts; adds new if item not found)
    void updateQuantity(const std::string& name, int change);

    // Set the quantity of an item explicitly (adds new if item not found)
    void setQuantity(const std::string& name, int quantity);
};

#endif
