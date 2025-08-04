
#ifndef ORDER_H
#define ORDER_H

#include "Menu.h"         // Include the Menu header to use MenuItem type
#include <vector>         // Include vector for storing ordered items

// Structure to pair a menu item with its quantity
struct OrderedItem {
    MenuItem item;         // The menu item ordered
    int quantity;          // Quantity ordered of this item
};

class Order {
    std::vector<OrderedItem> orderedItems;  // Vector to hold all ordered items

public:
    // Adds a MenuItem and its quantity to the order
    void addItem(const MenuItem& item, int quantity);

    // Displays the current order with item names, quantities, and prices
    void displayOrder() const;

    // Saves the order details to a file (append mode suggested)
    void saveToFile(const std::string& filename) const;
};

#endif
