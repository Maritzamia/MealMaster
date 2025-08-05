#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

// Struct representing a single menu item with a name and a price
struct MenuItem {
    std::string name;
    double price;
};

class Menu {
private:
    std::vector<MenuItem> items;  // Collection of all menu items

    // Case-insensitive comparison helper
    bool equalsIgnoreCase(const std::string& a, const std::string& b) const;

public:
    // Loads menu items from a given file (expects name and price per item)
    void loadFromFile(const std::string& filename);

    // Saves current menu items to a given file
    void saveToFile(const std::string& filename) const;

    // Prints the menu to the console
    void displayMenu() const;

    // Adds a new item to the menu (prevents duplicates)
    void addItem(const std::string& name, double price, class Inventory& inventory);


    // Gets the menu item by index (for ordering by number)
    MenuItem getItem(int index) const;

    // Gets the menu item by name (case-insensitive search)
    const MenuItem* getItem(const std::string& name) const;

    // Returns how many menu items are currently available
    int getSize() const;

    // Checks if an item with the given name already exists (case-insensitive)
    bool itemExists(const std::string& name) const;
};

#endif
