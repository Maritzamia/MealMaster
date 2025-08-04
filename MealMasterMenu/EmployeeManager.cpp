#include "EmployeeManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Generate a unique employee ID with zero padding, e.g. E001, E002, etc.
std::string EmployeeManager::generateEmployeeID() const {
    // employees.size() + 1 for next ID
    std::ostringstream oss;
    oss << "E" << std::setfill('0') << std::setw(3) << employees.size() + 1;
    return oss.str();
}

// Basic shift validation (optional: improve if needed)
bool EmployeeManager::isValidShift(const std::string& shift) const {
    // Accept only Morning, Afternoon, Night (case sensitive)
    return (shift == "Morning" || shift == "Afternoon" || shift == "Night");
}

// Add an employee with separate first and last name and auto-generated ID
void EmployeeManager::addEmployee(const std::string& firstName, const std::string& lastName, const std::string& shift) {
    if (!isValidShift(shift)) {
        cout << "Invalid shift. Please enter Morning, Afternoon, or Night.\n";
        return;
    }

    std::string fullName = firstName + " " + lastName;
    std::string id = generateEmployeeID();

    employees.push_back(Employee(fullName, id, shift));
    cout << "Employee " << fullName << " added successfully with ID: " << id << "\n";
}

// Load employees from a text file
void EmployeeManager::loadFromFile(const std::string& filename) {
    employees.clear();
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Could not open " << filename << " for reading.\n";
        return;
    }

    string name, id, shift;
    while (getline(inFile, name) && getline(inFile, id) && getline(inFile, shift)) {
        employees.push_back(Employee(name, id, shift));
    }

    inFile.close();
}

// Save employees to a text file
void EmployeeManager::saveToFile(const std::string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Could not open " << filename << " for writing.\n";
        return;
    }

    for (const auto& emp : employees) {
        outFile << emp.name << "\n";
        outFile << emp.id << "\n";
        outFile << emp.shift << "\n";
    }

    outFile.close();
}

// Display all employees in neat columns
void EmployeeManager::displayEmployees() {
    cout << "\nCurrent Employees:\n";
    cout << left << setw(25) << "Name" << setw(10) << "ID" << setw(15) << "Shift" << "\n";
    cout << "-------------------------------------------------------\n";
    for (const auto& emp : employees) {
        cout << left << setw(25) << emp.name << setw(10) << emp.id << setw(15) << emp.shift << "\n";
    }
    if (employees.empty()) {
        cout << "(No employees found.)\n";
    }
}

// Delete an employee by ID
void EmployeeManager::deleteEmployeeById(const std::string& id) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->id == id) {
            cout << "Deleting employee: " << it->name << " (ID: " << id << ")\n";
            employees.erase(it);
            return;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
}
