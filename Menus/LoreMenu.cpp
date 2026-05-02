//
// Created by adaze on 12.06.2025.
//

#include "LoreMenu.h"
#include <fstream>

#include "../Managers/StringExtensions.h"

int LoreMenu::printAndGetChoice() {
    ConsoleManager::clear();
    std::vector<std::string> lore;

    int maximumLineLength = 35;

    std::string line;
    std::ifstream myfile ("../TXT/Lore.txt");
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {
            if (line.length() > maximumLineLength) maximumLineLength = line.length();
            lore.push_back(line);
        }
        myfile.close();
    }

    ConsoleManager::printBoxView(lore, "Lore", maximumLineLength, ForegroundConsoleColor::Magenta, ForegroundConsoleColor::Magenta);

    int difficulty = printAndReturnChoiceMenu(
        "",
        {1, 1}
    );
    return difficulty;
}
