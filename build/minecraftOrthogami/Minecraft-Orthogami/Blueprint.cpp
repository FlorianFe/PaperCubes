//
//  Blueprint.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include "Blueprint.h"

Blueprint::Blueprint(Vector normal)
{
    this->minX = 0;
    this->minY = 0;
    this->maxX = 0;
    this->maxY = 0;
    this->empty = true;
    this->size = 0;
    this->normal = normal;
}

void Blueprint::add(int x, int y, int value)
{
    this->map[x][y] = value;
    this->size++;
    
    if(this->empty)
    {
        this->minX = x;
        this->minY = y;
        this->maxX = x;
        this->maxY = y;
        this->empty = false;
    }
    else
    {
        if(x > this->maxX) this->maxX = x;
        if(x < this->minX) this->minX = x;
        if(y > this->maxY) this->maxY = y;
        if(y < this->minY) this->minY = y;
    }
}

int* Blueprint::get2DArray()
{
    unsigned int size = this->getWidth() * this->getHeight();
    int* result = new int[size];
    
    for(int x = this->minX; x <= this->maxX; ++x)
    {
        for(int y = this->minY; y <= this->maxY; ++y)
        {
            if(this->map.count(x) > 0)
            {
                if(this->map[x].count(y) > 0)
                {
                    result[(x - minX) + (y -minY) * this->getWidth()] = this->map[x][y];
                }
                else
                {
                    result[(x - minX) + (y -minY) * this->getWidth()] = -1;
                }
            }
            else
            {
                result[(x - minX) + (y -minY) * this->getWidth()] = -1;
            }
        }
    }
    
    return result;
}

unsigned int Blueprint::getSize()
{
    return this->size;
}

unsigned int Blueprint::getWidth()
{
    return this->maxX - this->minX + 1;
}

unsigned int Blueprint::getHeight()
{
    return this->maxY - this->minY + 1;
}

Vector Blueprint::getNormal()
{
    return this->normal;
}

int Blueprint::getMinX()
{
    return this->minX;
}

int Blueprint::getMinY()
{
    return this->minY;
}
