//Task1
//Напишите информационную систему "Сотрудники".
//Программа должна обеспечивать ввод данных, редактирование данных сотрудника, удаление сотрудника, поиск сотрудника по фамилии, вывод информации обо всех сотрудниках, указанного возраста, или фамилия которых начинается на указанную букву.
//Организуйте возможность сохранения найденной информации в файл.
//Также весь список сотрудников сохраняется в файл(при выходе из программы – автоматически, в процессе исполнения программы – по команде пользователя).
//При старте программы происходит загрузка списка сотрудников из указанного пользователем файла.



//очередной комментарий


#include "EmployeeManager.h"
#include <iostream>
#include <Windows.h>

void menu() {
    std::cout << "\n1. Добавить\n2. Редактировать\n3. Удалить\n4. Поиск по фамилии\n"
        << "5. Фильтр по возрасту\n6. Фильтр по первой букве\n"
        << "7. Показать всех\n8. Сохранить\n9. Сохранить найденное\n0. Выход\n";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "Привіт з myBranch!" << std::endl;

    EmployeeManager manager;
    char filename[100];

    std::cout << "Введите имя файла для загрузки: (employees.txt) ";
    std::cin.getline(filename, 100);
    manager.loadFromFile(filename);

    int choice;
    do {
        menu();
        std::cout << "> ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            char name[100], position[100];
            int age;
            double salary;
            std::cout << "ФИО: "; std::cin.getline(name, 100);
            std::cout << "Возраст: "; std::cin >> age;
            std::cin.ignore();
            std::cout << "Должность: "; std::cin.getline(position, 100);
            std::cout << "Зарплата: "; std::cin >> salary;
            std::cin.ignore();
            manager.addEmployee(Employee(name, position, age, salary));
            break;
        }
        case 2: {
            char name[100];
            std::cout << "ФИО сотрудника для редактирования: ";
            std::cin.getline(name, 100);
            if (!manager.editEmployee(name))
                std::cout << "Сотрудник не найден.\n";
            break;
        }
        case 3: {
            char name[100];
            std::cout << "ФИО сотрудника для удаления: ";
            std::cin.getline(name, 100);
            if (!manager.deleteEmployee(name))
                std::cout << "Сотрудник не найден.\n";
            break;
        }
        case 4: {
            char lastName[100];
            std::cout << "Введите фамилию: ";
            std::cin.getline(lastName, 100);
            int resultCount = 0;
            Employee* results = manager.searchByLastName(lastName, resultCount);
            for (int i = 0; i < resultCount; ++i) {
                std::cout << results[i].toString() << '\n';
            }
            delete[] results;
            break;
        }
        case 5: {
            int age;
            std::cout << "Введите возраст: ";
            std::cin >> age;
            std::cin.ignore();
            int resultCount = 0;
            Employee* results = manager.filterByAge(age, resultCount);
            for (int i = 0; i < resultCount; ++i) {
                std::cout << results[i].toString() << '\n';
            }
            delete[] results;
            break;
        }
        case 6: {
            char ch;
            std::cout << "Введите первую букву фамилии: ";
            std::cin >> ch;
            std::cin.ignore();
            int resultCount = 0;
            Employee* results = manager.filterByFirstLetter(ch, resultCount);
            for (int i = 0; i < resultCount; ++i) {
                std::cout << results[i].toString() << '\n';
            }
            delete[] results;
            break;
        }
        case 7:
            manager.showAll();
            break;
        case 8:
            manager.saveToFile(filename);
            std::cout << "Сохранено в основной файл.\n";
            break;
        case 9: {
            char outFile[100];
            std::cout << "Введите имя файла для сохранения найденных: (можно ввести любое название и файл создасться автоматом) ";
            std::cin.getline(outFile, 100);
            std::cout << "1 — по возрасту, 2 — по фамилии: ";
            int mode;
            std::cin >> mode;
            std::cin.ignore();
            if (mode == 1) {
                int age;
                std::cout << "Возраст: ";
                std::cin >> age;
                std::cin.ignore();
                int resultCount = 0;
                Employee* results = manager.filterByAge(age, resultCount);
                manager.saveResultsToFile(results, resultCount, outFile);
                delete[] results;
            }
            else {
                char lastName[100];
                std::cout << "Фамилия: ";
                std::cin.getline(lastName, 100);
                int resultCount = 0;
                Employee* results = manager.searchByLastName(lastName, resultCount);
                manager.saveResultsToFile(results, resultCount, outFile);
                delete[] results;
            }
            break;
        }
        case 0:
            manager.saveToFile(filename);
            std::cout << "Выход с сохранением.\n";
            break;
        default:
            std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}

//Просто добавил комментарий вконце, чтоб были изменения для коммита 