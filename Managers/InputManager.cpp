//
// Created by adaze on 09.05.2025.
//

#include "InputManager.h"


int InputManager::getInt() {
    std::cout << "enter a number: ";

    int input;
    std::cin >> input;
    std::cout << std::endl;

    while (!std::cin.good())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.";
    }

    return input;
}