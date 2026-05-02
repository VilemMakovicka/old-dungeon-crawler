//
// Created by Vilém on 10/05/2025.
//

#include "Random.h"

int Random::getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    return uni(rng);
}

bool Random::getRandomBool(int percentage) {
    int random = getRandomInt(0, 100);
    return percentage >= random;
}
