#include "EmployeeManager.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>

EmployeeManager::EmployeeManager() {
    employees = nullptr;
    count = 0;
}

EmployeeManager::~EmployeeManager() {
    delete[] employees;
}

void EmployeeManager::loadFromFile(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << " для чтения\n";
        return;
    }

    in >> count;
    in.ignore();

    delete[] employees;
    employees = new Employee[count];

    char name[51];
    char position[51];
    int age;
    double salary;

    for (int i = 0; i < count; ++i) {
        in.getline(name, 51, ';');
        in.getline(position, 51, ';');
        in >> age;
        in.ignore();
        in >> salary;
        in.ignore();

        employees[i] = Employee(name, position, age, salary);
    }

    in.close();
}

void EmployeeManager::saveToFile(const char* filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи\n";
        return;
    }

    out << count << '\n';

    for (int i = 0; i < count; ++i) {
        out << employees[i].name << ';'
            << employees[i].position << ';'
            << employees[i].age << ';'
            << employees[i].salary << '\n';
    }

    out.close();
}

void EmployeeManager::saveResultsToFile(Employee* results, int resultCount, const char* filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Ошибка сохранения результатов в файл.\n";
        return;
    }

    out << resultCount << '\n';
    for (int i = 0; i < resultCount; ++i) {
        out << results[i].name << ';'
            << results[i].position << ';'
            << results[i].age << ';'
            << results[i].salary << '\n';
    }

    out.close();
}

void EmployeeManager::addEmployee(const Employee& emp) {
    Employee* newArr = new Employee[count + 1];
    for (int i = 0; i < count; ++i)
        newArr[i] = employees[i];
    newArr[count] = emp;

    delete[] employees;
    employees = newArr;
    ++count;
}

bool EmployeeManager::editEmployee(const char* name) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(employees[i].name, name) == 0) {
            char newName[100], newPosition[100];
            int newAge;
            double newSalary;

            std::cout << "Новое имя: ";
            std::cin.getline(newName, 100);
            std::cout << "Новый возраст: ";
            std::cin >> newAge;
            std::cin.ignore();
            std::cout << "Новая должность: ";
            std::cin.getline(newPosition, 100);
            std::cout << "Новая зарплата: ";
            std::cin >> newSalary;
            std::cin.ignore();

            employees[i] = Employee(newName, newPosition, newAge, newSalary);
            return true;
        }
    }
    return false;
}

bool EmployeeManager::deleteEmployee(const char* name) {
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (strcmp(employees[i].name, name) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    Employee* newArr = new Employee[count - 1];
    for (int i = 0, j = 0; i < count; ++i) {
        if (i != index) {
            newArr[j++] = employees[i];
        }
    }

    delete[] employees;
    employees = newArr;
    --count;
    return true;
}

Employee* EmployeeManager::searchByLastName(const char* lastName, int& resultCount) {
    Employee* results = new Employee[count];
    resultCount = 0;

    for (int i = 0; i < count; ++i) {
        char* space = strchr(employees[i].name, ' ');
        if (space != nullptr) {
            char currentLastName[51];
            size_t len = space - employees[i].name;
            strncpy_s(currentLastName, 51, employees[i].name, len);
            currentLastName[len] = '\0';
            if (strcmp(currentLastName, lastName) == 0) {
                results[resultCount++] = employees[i];
            }
        }
    }

    Employee* finalResults = new Employee[resultCount];
    for (int i = 0; i < resultCount; ++i)
        finalResults[i] = results[i];

    delete[] results;
    return finalResults;
}

Employee* EmployeeManager::filterByAge(int age, int& resultCount) {
    Employee* results = new Employee[count];
    resultCount = 0;

    for (int i = 0; i < count; ++i) {
        if (employees[i].age == age) {
            results[resultCount++] = employees[i];
        }
    }

    Employee* finalResults = new Employee[resultCount];
    for (int i = 0; i < resultCount; ++i)
        finalResults[i] = results[i];

    delete[] results;
    return finalResults;
}

Employee* EmployeeManager::filterByFirstLetter(char letter, int& resultCount) {
    Employee* results = new Employee[count];
    resultCount = 0;

    for (int i = 0; i < count; ++i) {
        if (tolower(employees[i].name[0]) == tolower(letter)) {
            results[resultCount++] = employees[i];
        }
    }

    Employee* finalResults = new Employee[resultCount];
    for (int i = 0; i < resultCount; ++i)
        finalResults[i] = results[i];

    delete[] results;
    return finalResults;
}

void EmployeeManager::showAll() {
    for (int i = 0; i < count; ++i) {
        char* info = employees[i].toString();
        std::cout << info << '\n';
        delete[] info;
    }
}