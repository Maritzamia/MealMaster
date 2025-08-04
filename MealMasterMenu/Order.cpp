#include "Order.h"
#include <iostream>
#include <fstream>

// Adds a menu item along with the quantity ordered to the order list
void Order::addItem(const MenuItem& item, int quantity) {
    // Push an OrderEntry struct containing the item and quantity
    orderedItems.push_back({ item, quantity });
}

// Displays a summary of the order to the console
// Shows each item, quantity, item total cost, and grand total
void Order::displayOrder() const {
    std::cout << "\n--- Order Summary ---\n\n";
    double total = 0;
    // Loop through each ordered item and calculate cost
    for (const auto& entry : orderedItems) {
        double cost = entry.item.price * entry.quantity;
        std::cout << entry.item.name << " x" << entry.quantity << " = $" << cost << "\n";
        total += cost; // Keep a running total
    }
    std::cout << "Total: $" << total << "\n"; // Display grand total
}

// Saves the order details to a file, appending at the end
// Format: item name, quantity, price per item on each line
void Order::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app); // Open file in append mode
    for (const auto& entry : orderedItems) {
        file << entry.item.name << "," << entry.quantity << "," << entry.item.price << "\n";
    }
}
