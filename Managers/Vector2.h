//
// Created by alaf4 on 09.05.2025.
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

// Pomocny epicky vilem struct B-)

struct Vector2 {
    int x, y;

    static const Vector2 up; ///Vraci {0, 1}
    static const Vector2 down; ///Vraci {0, -1}
    static const Vector2 left; ///Vraci {-1, 0}
    static const Vector2 right; ///Vraci {1, 0}

    static const Vector2 zero; ///Vraci {0, 0}
    static const Vector2 one; ///Vraci {1, 1}

    int length(); ///Tato metoda je tu pro pripad ze sila zbrani/monster bude zaviset na vzdalenosti hrače od {0, 0} (pocatecniho bodu)

    Vector2& operator += (const Vector2& operand);
    Vector2 operator + (const Vector2& operand) const;
    Vector2 operator - (const Vector2& operand) const;
    Vector2 operator * (const Vector2& operand) const;
    Vector2 operator * (const int& operand) const;
    bool operator == (const Vector2& operand) const;

    std::string toString() const;

};



#endif //VECTOR2_H
