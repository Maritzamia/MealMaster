#include "Inventory.h"
#include <fstream>
#include <iostream>

// Load inventory data from a text file
// Clears existing inventory and reads pairs of item names and quantities from the file.
// If the file can't be opened, prints an error message.
void Inventory::loadFromFile(const std::string& filename) {
    items.clear();  // Clear current inventory list before loading new data
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "\nCould not open inventory file.\n";
        return;  // Early exit if file can't be opened
    }

    std::string name;
    int quantity;
    // Reads the item name (line) and quantity (integer) repeatedly until EOF
    while (getline(file, name) && file >> quantity) {
        file.ignore();  // Ignore leftover newline after quantity reading
        items.push_back({ name, quantity });  // Add item to inventory list
    }
}

// Save current inventory to a text file
// Writes each item's name and quantity on separate lines for easy reading and writing.
void Inventory::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& item : items) {
        file << item.name << "\n" << item.quantity << "\n";  // Save each inventory item with its quantity
    }
}

// Display the current inventory to the console
// Prints each item and its quantity for user visibility.
void Inventory::displayInventory() const {
    std::cout << "\n--- Inventory ---\n\n";
    for (const auto& item : items) {
        std::cout << item.name << ": " << item.quantity << "\n";  // Print name and current quantity
    }
}

// Update the quantity of an existing inventory item or add it if it doesn't exist
// The change can be positive (restocking) or negative (selling items).
void Inventory::updateQuantity(const std::string& name, int change) {
    for (auto& item : items) {
        if (item.name == name) {
            item.quantity += change;  // Adjust quantity based on change
            return;  // Exit after update
        }
    }
    // If item not found, add it as a new item with the given quantity (could be negative, so be cautious)
    items.push_back({ name, change });
}
bool Inventory::itemExists(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.name == itemName) {
            return true;
        }
    }
    return false;
}
// NEW FUNCTION: Set quantity explicitly for an inventory item
// This overwrites the current quantity or adds the item if it doesn't exist
void Inventory::setQuantity(const std::string& name, int quantity) {
    for (auto& item : items) {
        if (item.name == name) {
            item.quantity = quantity;  // Overwrite with new quantity
            return;
        }
    }
    // Item does not exist; add as new with specified quantity
    items.push_back({ name, quantity });
}
