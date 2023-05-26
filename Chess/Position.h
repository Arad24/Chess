#pragma once
#include <iostream>

class Position
{
public:
    // Ctor & Dtor
    Position(char x, int y);
    ~Position();
    Position();

    // Getters
    char getX() const;
    int getY() const;

    // Setters
    void setX(char x);
    void setY(int y);

private:
    char _x;
    int _y;
};