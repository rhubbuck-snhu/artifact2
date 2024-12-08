#include <vector>
#include <string>
#include "functions.h"
#include <iostream>

// Function to display the user menu
void displayMenu() {
    std::cout << std::string(32, '*') << std::endl;
    std::cout << "* Course Planner Main Menu:    *" << std::endl;
    std::cout << "*" <<  std::string(30, '_') << "*" << std::endl;
    std::cout << "*  1. Load Data Structure.     *" << std::endl;
    std::cout << "*  2. Print Course List.       *" << std::endl;
    std::cout << "*  3. Print Course.            *" << std::endl;
    std::cout << "*  4. Delete a Course.         *" << std::endl;
    std::cout << "*  5. Add a new Course.        *" << std::endl;
    std::cout << "*  6. Manage Prerequisites.    *" << std::endl;
    std::cout << "*  9. Exit                     *" << std::endl;
    std::cout << std::string(32, '*') << std::endl;
    std::cout << std::endl <<  "Enter an option: ";
}

// Function to display user submenu
void displaySubMenu() {
    std::cout << std::string(28, '*') << std::endl;
    std::cout << "*  1. Add prerequisite.    *" << std::endl;
    std::cout << "*  2. Delete prerequisite. *" << std::endl;
    std::cout << "*  3. Back.                *" << std::endl;
    std::cout << std::string(28, '*') << std::endl;
    std::cout << "Enter an option:";
}