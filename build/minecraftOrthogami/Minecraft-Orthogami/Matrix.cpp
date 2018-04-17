//
//  Matrix.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 01.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "Matrix.h"

Matrix::Matrix(Block* data, int width, int height, int depth)
{
    this->data = data;
    this->width = width;
    this->height = height;
    this->depth = depth;
}

Matrix::~Matrix()
{
    //delete this->data;
}

Matrix::Matrix(int width, int height, int depth)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    
    this->data = new Block[width * height * depth];
    
    for(int i=0; i<this->getSize(); i++)
    {
        this->data[i].type = 0;
        this->data[i].metaType = 0;
    }
}

Block Matrix::get(int index)
{
    if(index < 0 || index >= this->getSize())
    {
        throw "Out of Bounds Exception";
    }
    
    return this->data[index];
}

void Matrix::set(int index, Block value)
{
    if(index < 0 || index >= this->getSize())
    {
        throw "Out of Bounds Exception";
    }
    
    this->data[index] = value;
}

Block Matrix::get(int x, int y, int z)
{
    int index = x + this->width * y + this->width * this->height * z;
    int width = this->width;
    int height = this->height;
    int depth = this->depth;
    int size = width*height*depth;
    
    if(index < 0 || index >= size)
    {
        throw "Out of Bounds Exception";
    }
    
    return this->data[index];
}

void Matrix::set(int x, int y, int z, Block value)
{
    int index = x + this->width * y + this->width * this->height * z;
    
    if(index < 0 || index >= this->getSize())
    {
        throw "Out of Bounds Exception";
    }
    
    this->data[index] = value;
}

int Matrix::getSize()
{
    return (this->width * this->height * this->depth);
}

int Matrix::getWidth()
{
    return this->width;
}

int Matrix::getHeight()
{
    return this->height;
}

int Matrix::getDepth()
{
    return this->depth;
}
