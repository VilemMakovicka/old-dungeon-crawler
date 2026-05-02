//
// Created by alaf4 on 09.05.2025.
//

#include "Vector2.h"


Vector2& Vector2::operator += (const Vector2& operand){
    x += operand.x;
    y += operand.y;
    return *this;
}

Vector2 Vector2::operator + (const Vector2& operand) const{
    return {x + operand.x, y + operand.y};
}

Vector2 Vector2::operator - (const Vector2& operand) const{
    return {x - operand.x, y - operand.y};
}

Vector2 Vector2::operator * (const Vector2& operand) const{
    return {x * operand.x, y * operand.y};
}

Vector2 Vector2::operator * (const int& operand) const{
    return {x * operand, y * operand};
}

bool Vector2::operator == (const Vector2& operand) const {
    return x == operand.x && y == operand.y;
}

std::string Vector2::toString() const {
    return std::to_string(x) + " ," + std::to_string(y);
}

const Vector2 Vector2::up = {0, 1};
const Vector2 Vector2::down = {0, -1};
const Vector2 Vector2::right = {1, 0};
const Vector2 Vector2::left = {-1, 0};

const Vector2 Vector2::zero = {0, 0};
const Vector2 Vector2::one = {1, 1};

int Vector2::length() {
    return abs(x) + abs(y);
}