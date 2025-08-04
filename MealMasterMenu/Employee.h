// Employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

//
// Class: Employee
// ----------------
// This class represents an individual employee with basic information such as:
// - name: the employee's name
// - id: a unique identifier for the employee
// - shift: the employee's work shift (e.g., "Morning", "Evening")
//
class Employee {
public:
    std::string name;  // Employee's name
    std::string id;    // Unique employee ID
    std::string shift; // Assigned work shift

    //
    // Parameterized Constructor:
    // Allows creation of an Employee object with name, ID, and shift set immediately.
    // Used when reading employee data from files or adding new ones in the manager.
    //
    Employee(const std::string& n, const std::string& i, const std::string& s)
        : name(n), id(i), shift(s) {
    }

    //
    // Default Constructor:
    // Useful when you want to declare an Employee object first and assign values later.
    // For example: `Employee emp; emp.name = "John";`
    //
    Employee() = default;
};

#endif // EMPLOYEE_H
