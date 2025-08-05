#include "Inventory.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Helper: convert string to lowercase
std::string Inventory::toLower(const std::string& str) const {
    std::string lowered = str;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
    return lowered;
}

// Helper: trim whitespace from both ends
std::string Inventory::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Load inventory data from a text file
void Inventory::loadFromFile(const std::string& filename) {
    items.clear();
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "\nCould not open inventory file.\n";
        return;
    }

    std::string name;
    int quantity;
    while (getline(file, name) && file >> quantity) {
        file.ignore(); // Ignore leftover newline
        name = trim(name);
        items.push_back({ name, quantity });
    }
}

// Save current inventory to a text file
void Inventory::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& item : items) {
        file << item.name << "\n" << item.quantity << "\n";
    }
}

// Display inventory
void Inventory::displayInventory() const {
    std::cout << "\n--- Inventory ---\n\n";
    for (const auto& item : items) {
        std::cout << item.name << ": " << item.quantity << "\n";
    }
}

// Update quantity (case-insensitive)
void Inventory::updateQuantity(const std::string& name, int change) {
    std::string normalizedName = toLower(trim(name));
    for (auto& item : items) {
        if (toLower(trim(item.name)) == normalizedName) {
            item.quantity += change;
            return;
        }
    }
    // If not found, add new
    items.push_back({ trim(name), change });
}

// Set quantity (overwrite)
void Inventory::setQuantity(const std::string& name, int quantity) {
    std::string normalizedName = toLower(trim(name));
    for (auto& item : items) {
        if (toLower(trim(item.name)) == normalizedName) {
            item.quantity = quantity;
            return;
        }
    }
    // If not found, add new
    items.push_back({ trim(name), quantity });
}

// Check if item exists (case-insensitive)
bool Inventory::itemExists(const std::string& itemName) const {
    std::string normalizedName = toLower(trim(itemName));
    for (const auto& item : items) {
        if (toLower(trim(item.name)) == normalizedName) {
            return true;
        }
    }
    return false;
}
