#include "Employee.h"
#include <cstring>
#include <cstdio>

Employee::Employee() {
    name = new char[1] { '\0' };
    position = new char[1] { '\0' };
    age = 0;
    salary = 0.0;
}

Employee::Employee(const char* name_, const char* position_, int age_, double salary_) {
    size_t nameLen = strlen(name_) + 1;
    name = new char[nameLen];
    strcpy_s(name, nameLen, name_);

    size_t posLen = strlen(position_) + 1;
    position = new char[posLen];
    strcpy_s(position, posLen, position_);

    age = age_;
    salary = salary_;
}

Employee::Employee(const Employee& other) {
    size_t nameLen = strlen(other.name) + 1;
    name = new char[nameLen];
    strcpy_s(name, nameLen, other.name);

    size_t posLen = strlen(other.position) + 1;
    position = new char[posLen];
    strcpy_s(position, posLen, other.position);

    age = other.age;
    salary = other.salary;
}

Employee& Employee::operator=(const Employee& other) {
    if (this != &other) {
        delete[] name;
        delete[] position;

        size_t nameLen = strlen(other.name) + 1;
        name = new char[nameLen];
        strcpy_s(name, nameLen, other.name);

        size_t posLen = strlen(other.position) + 1;
        position = new char[posLen];
        strcpy_s(position, posLen, other.position);

        age = other.age;
        salary = other.salary;
    }
    return *this;
}

Employee::~Employee() {
    delete[] name;
    delete[] position;
}

char* Employee::toString() const {
    const int bufferSize = 256;
    char* buffer = new char[bufferSize];
    sprintf_s(buffer, bufferSize, "Имя: %s, Должность: %s, Возраст: %d, Зарплата: %.2lf", name, position, age, salary);
    return buffer;
}