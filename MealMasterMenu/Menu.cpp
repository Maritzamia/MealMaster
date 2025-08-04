#include "Menu.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Case-insensitive comparison helper
bool Menu::equalsIgnoreCase(const std::string& a, const std::string& b) const {
    if (a.size() != b.size()) return false;
    return std::equal(a.begin(), a.end(), b.begin(), [](char c1, char c2) {
        return std::tolower(static_cast<unsigned char>(c1)) == std::tolower(static_cast<unsigned char>(c2));
        });
}

// Checks if a menu item with the given name exists
bool Menu::itemExists(const std::string& name) const {
    for (const auto& item : items) {
        if (equalsIgnoreCase(item.name, name)) {
            return true;
        }
    }
    return false;
}

// Loads menu items from a file
void Menu::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string name;
    double price;

    while (std::getline(file, name) && file >> price) {
        file.ignore(); // Skip newline after price
        if (!itemExists(name)) {
            items.push_back({ name, price });
        }
        else {
            std::cout << "Skipped duplicate item: " << name << "\n";
        }
    }
}

// Saves current menu items to a file
void Menu::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& item : items) {
        file << item.name << "\n" << item.price << "\n";
    }
}

// Displays the menu
void Menu::displayMenu() const {
    std::cout << "\n--- Menu ---\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i].name << " - $" << items[i].price << "\n";
    }
}

// Adds a new item if it doesn't already exist
void Menu::addItem(const std::string& name, double price) {
    if (itemExists(name)) {
        std::cout << "Item \"" << name << "\" already exists in the menu.\n";
        return;
    }
    items.push_back({ name, price });
    std::cout << "Item \"" << name << "\" added to menu.\n";
}

// Returns item by index
MenuItem Menu::getItem(int index) const {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        return items[index];
    }
    return { "Invalid", 0.0 };
}

// Returns pointer to item by name
const MenuItem* Menu::getItem(const std::string& name) const {
    for (const auto& item : items) {
        if (equalsIgnoreCase(item.name, name)) {
            return &item;
        }
    }
    return nullptr;
}

// Returns menu size
int Menu::getSize() const {
    return static_cast<int>(items.size());
}
