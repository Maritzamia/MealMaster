// ---------------------------------------------
// Project: Restaurant Management System 
// Project Name: MealMaster
// Student: Maritza Estrada
// Date: July 28, 2025
// Description: Command-line app to manage menu, orders, inventory, and employees.
// ---------------------------------------------
// Set Up!!!
#include "Menu.h"
#include "Inventory.h"
#include "Order.h"
#include "EmployeeManager.h"
#include <iostream>
#include <limits>
#include <cctype> // for isalpha()

using namespace std;

// Helper function to clear invalid input from cin buffer
static void clearCin() {
    cin.clear(); // Reset error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard leftover input
}

// Checks if a name is valid (letters and spaces only)
bool isValidName(const std::string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return !name.empty();
}

int main() {
    // Initialize objects for menu, inventory, and employee management
    Menu menu;
    Inventory inventory;
    EmployeeManager empManager;

    // Load saved data from files
    menu.loadFromFile("menu.txt");
    inventory.loadFromFile("inventory.txt");
    empManager.loadFromFile("employees.txt");

    // Welcome message
    cout << "--------------------------------------------\n";
    cout << " Welcome to MealMaster - Restaurant Manager\n";
    cout << "--------------------------------------------\n";
    cout << " This program helps you manage your menu,\n";
    cout << " inventory, orders, and employees with ease.\n";
    cout << " It automatically loads your latest data and\n";
    cout << " saves changes as you work. Stay organized and\n";
    cout << " keep your restaurant running smoothly!\n\n";

    // Main menu loop
    while (true) {
        cout << "\n==== Restaurant Management System ====\n\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Inventory\n";
        cout << "4. Add/Edit Menu Item\n";
        cout << "5. Employee Management\n";
        cout << "6. Edit Inventory Quantity\n";
        cout << "0. Exit\n\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        // ClearCin is to clean bad input from the users, so the program doesnt get stuck 
        if (cin.fail()) {
            clearCin();
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
        case 0:
            cout << "Exiting...\n";
            return 0;

        case 1:
            // Display current menu
            menu.displayMenu();
            break;

        case 2: {
            // Handle placing an order
            Order order;
            int itemNum, qty;
            menu.displayMenu();

            cout << "Enter item number (0 to Complete Transaction): ";
            while (cin >> itemNum && itemNum != 0) {
                if (itemNum < 1 || itemNum > menu.getSize()) {
                    cout << "Invalid item number. Try again: ";
                    continue;
                }

                cout << "Enter quantity: ";
                cin >> qty;
                if (qty < 1) {
                    cout << "Invalid quantity. Try again: ";
                    continue;
                }

                // Add item to order and reduce inventory
                MenuItem item = menu.getItem(itemNum - 1);
                order.addItem(item, qty);
                inventory.updateQuantity(item.name, -qty);

                cout << "Add another item (0 to Complete Transaction): ";
            }

            // Display final order and save data
            order.displayOrder();
            order.saveToFile("orders.txt");
            inventory.saveToFile("inventory.txt");
            break;
        }

        case 3:
            // View all inventory items
            inventory.displayInventory();
            break;

      case 4: {
     // Add a new item to the menu
     string name;
     double price;

     clearCin(); // Clear input buffer before getline

     // Validate item name: no numbers or symbols
     do {
         cout << "Enter new item name (letters and spaces only): ";
         getline(cin, name);
         if (!isValidName(name)) {
             cout << "Invalid name. Please use letters and spaces only.\n";
         }
     } while (!isValidName(name));

     cout << "Enter price: ";
     cin >> price;

     if (cin.fail() || price < 0) {
         clearCin();
         cout << "Invalid price.\n";
         break;
     }

     menu.addItem(name, price, inventory);
     menu.saveToFile("menu.txt");
     inventory.saveToFile("inventory.txt");

     cout << "Item added to menu and inventory synced.\n";
     break;
 }

        case 5: {
            // Employee management menu
            cout << "\n--- Employee Management ---\n\n";
            cout << "1. Add Employee\n";
            cout << "2. View Employees\n";
            cout << "3. Delete Employee\n\n";
            cout << "Enter choice: ";

            int empChoice;
            cin >> empChoice;
            clearCin();

            if (empChoice == 1) {
                // Add new employee (with name validation)
                string firstName, lastName, shift;
                // isvalidname ensires employees names contain numbers only. 
                cout << "Enter first name: ";
                getline(cin, firstName);
                while (!isValidName(firstName)) {
                    cout << "Invalid first name. Use letters only: ";
                    getline(cin, firstName);
                }

                cout << "Enter last name: ";
                getline(cin, lastName);
                while (!isValidName(lastName)) {
                    cout << "Invalid last name. Use letters only: ";
                    getline(cin, lastName);
                }

                // Validate shift input
                while (true) {
                    cout << "Enter shift (Morning, Afternoon, Night): ";
                    getline(cin, shift);
                    if (shift == "Morning" || shift == "Afternoon" || shift == "Night") {
                        break;
                    }
                    cout << "Invalid shift. Please enter Morning, Afternoon, or Night.\n";
                }

                empManager.addEmployee(firstName, lastName, shift);
                empManager.saveToFile("employees.txt");
                cout << "Employee added.\n";
            }
            else if (empChoice == 2) {
                // Display all employees
                empManager.displayEmployees();
            }
            else if (empChoice == 3) {
                // Delete employee by ID
                string id;
                cout << "Enter ID of employee to delete: ";
                getline(cin, id);
                empManager.deleteEmployeeById(id);
                empManager.saveToFile("employees.txt");
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }

        case 6: {
            // Edit inventory quantity for an existing item with input validation
            string itemName;
            int newQty;

            clearCin(); // clear input buffer
            do {
                cout << "Enter item name to edit quantity (letters and spaces only): ";
                getline(cin, itemName);
                if (!isValidName(itemName)) {
                    cout << "Invalid item name. Use only letters and spaces.\n";
                }
            } while (!isValidName(itemName));

            // Check if item exists in inventory
            if (!inventory.itemExists(itemName)) {
                cout << "Item not found in inventory.\n";
                break;
            }

            cout << "Enter new quantity: ";
            cin >> newQty;

            if (cin.fail() || newQty < 0) {
                clearCin();
                cout << "Invalid quantity. Quantity must be a non-negative number.\n";
                break;
            }

            inventory.setQuantity(itemName, newQty);
            inventory.saveToFile("inventory.txt");
            cout << "Quantity updated.\n";
            break;
        }

        default:
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}

