//
// Created by Vilém on 10/05/2025.
//

#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <algorithm>

class Random {
public:
    static int getRandomInt(int min, int max);
    static bool getRandomBool(int percentage);
};



#endif //RANDOM_H
