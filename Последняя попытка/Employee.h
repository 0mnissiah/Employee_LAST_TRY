#pragma once

struct Employee {
    char* name;
    char* position;
    int age;
    double salary;

    Employee();
    Employee(const char* name_, const char* position_, int age_, double salary_);
    Employee(const Employee& other);
    Employee& operator=(const Employee& other);
    ~Employee();

    char* toString() const;
};

