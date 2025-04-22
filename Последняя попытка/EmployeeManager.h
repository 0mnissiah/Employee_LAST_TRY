#pragma once
#include "Employee.h"

class EmployeeManager {
private:
    Employee* employees;
    int count;

public:
    EmployeeManager();
    ~EmployeeManager();

    void loadFromFile(const char* filename);
    void saveToFile(const char* filename);
    void saveResultsToFile(Employee* results, int resultCount, const char* filename);

    void addEmployee(const Employee& emp);
    bool editEmployee(const char* name);
    bool deleteEmployee(const char* name);

    Employee* searchByLastName(const char* lastName, int& resultCount);
    Employee* filterByAge(int age, int& resultCount);
    Employee* filterByFirstLetter(char letter, int& resultCount);

    void showAll();
};
