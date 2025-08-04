#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <string>
#include <vector>

struct Employee {
    std::string name;
    std::string id;
    std::string shift;

    Employee(const std::string& n, const std::string& i, const std::string& s)
        : name(n), id(i), shift(s) {
    }
};

class EmployeeManager {
private:
    std::vector<Employee> employees;

    std::string generateEmployeeID() const;
    bool isValidShift(const std::string& shift) const;
    // Add this near the top or inside the class if you want it private



public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void addEmployee(const std::string& firstName, const std::string& lastName, const std::string& shift);
    void displayEmployees();
    void deleteEmployeeById(const std::string& id);

};

#endif // EMPLOYEEMANAGER_H
