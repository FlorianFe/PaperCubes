//
//  Vector.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 01.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include "Vector.h"
#include <math.h>

Vector::Vector()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector::Vector(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::copy()
{
    return Vector(this->x, this->y, this->z);
}

bool Vector::equals(Vector vector)
{
    return (this->x == vector.getX() && this->y == vector.getY() && this->z == vector.getZ());
}

Vector Vector::add(Vector vector)
{
    int x = this->x + vector.getX();
    int y = this->y + vector.getY();
    int z = this->z + vector.getZ();
    
    return Vector(x, y, z);
}

Vector Vector::subtract(Vector vector)
{
    int x = this->x - vector.getX();
    int y = this->y - vector.getY();
    int z = this->z - vector.getZ();
    
    return Vector(x, y, z);
}

double Vector::getLength()
{
    return sqrt((double)(this->x * this->x + this->y * this->y + this->z * this->z));
}

int Vector::getX()
{
    return this->x;
}

int Vector::getY()
{
    return this->y;
}

int Vector::getZ()
{
    return this->z;
}

void Vector::setX(int x)
{
    this->x = x;
}

void Vector::setY(int y)
{
    this->y = y;
}

void Vector::setZ(int z)
{
    this->z = z;
}
