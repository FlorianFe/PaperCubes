//
//  prepareMatrix.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <iostream>
#include <vector>
#include "prepareMatrix.h"

Matrix& expandMatrix(Matrix& matrix);
Matrix& fillVoids(Matrix& matrix);

Matrix& prepareMatrix(Matrix& matrix)
{
    //std::cout << "Original Matrix" << std::endl;
    //printMatrix(matrix);
    
    Matrix expandedMatrix = expandMatrix(matrix);
    //std::cout << "Expanded Matrix" << std::endl;
    //printMatrix(expandedMatrix);
    
    Matrix* filledMatrix = &fillVoids(expandedMatrix);
    //std::cout << "Filled Matrix" << std::endl;
    //printMatrix(filledMatrix);
    
    return *filledMatrix;
}

Matrix& expandMatrix(Matrix& sourceMatrix)
{
    Matrix* resultMatrix = new Matrix(sourceMatrix.getWidth() + 2, sourceMatrix.getHeight() + 2, sourceMatrix.getDepth() + 2);
    
    for(int x=0; x < resultMatrix->getWidth(); x++)
    {
        for(int y=0; y < resultMatrix->getHeight(); y++)
        {
            for(int z=0; z < resultMatrix->getDepth(); z++)
            {
                if(x == 0 || y == 0 || z == 0 || x == resultMatrix->getWidth() - 1 || y == resultMatrix->getHeight() - 1 || z == resultMatrix->getDepth() - 1)
                {
                    resultMatrix->set(x, y, z, {0, 0});
                }
                else
                {
                    Block value = sourceMatrix.get(x-1, y-1, z-1);
                    resultMatrix->set(x, y, z, value);
                }
            }
        }
    }
    
    return *resultMatrix;
}

struct Vector
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
};

Matrix& fillVoids(Matrix& sourceMatrix)
{
    Matrix alreadyReachedMatrix(sourceMatrix.getWidth(), sourceMatrix.getHeight(), sourceMatrix.getDepth());
    Matrix* resultMatrix = new Matrix(sourceMatrix.getWidth(), sourceMatrix.getHeight(), sourceMatrix.getDepth());
    
    Vector startPosition = { 0, 0, 0 };
    
    std::vector<Vector> queue;
    
    queue.push_back(startPosition);
    
    while(queue.size() != 0)
    {
        Vector position = queue.back();
        
        unsigned int x = position.x;
        unsigned int y = position.y;
        unsigned int z = position.z;
        
        queue.pop_back();
        
        Block voxelValue = sourceMatrix.get(x, y, z);
        bool alreadyReached = alreadyReachedMatrix.get(x, y, z).type == 1;
        
        if(voxelValue.type == 0 && !alreadyReached)
        {
            alreadyReachedMatrix.set(x, y, z, { 1, 0 });
            
            if(x > 0)
            {
                queue.push_back( { x - 1, y, z } );
            }
            if(x < sourceMatrix.getWidth() - 1)
            {
                queue.push_back( { x + 1, y, z } );
            }
            
            if(y > 0)
            {
                queue.push_back( { x, y - 1, z } );
            }
            if(y < sourceMatrix.getHeight() - 1)
            {
                queue.push_back( { x, y + 1, z } );
            }
            
            if(z > 0)
            {
                queue.push_back( { x, y, z - 1 } );
            }
            if(z < sourceMatrix.getDepth() - 1)
            {
                queue.push_back( { x, y, z + 1 } );
            }
        }
    }
    
    for(int i=0; i<alreadyReachedMatrix.getSize(); i++)
    {
        bool alreadyReached = alreadyReachedMatrix.get(i).type == 1;
        bool isVoid = sourceMatrix.get(i).type == 0;
        
        if(!alreadyReached)
        {
            if(isVoid)
            {
                resultMatrix->set(i, { 1, 0 });
            }
            else
            {
                Block value = sourceMatrix.get(i);
                resultMatrix->set(i, value);
            }
        }
    }
    
    return *resultMatrix;
}

void printMatrix(Matrix& matrix)
{
    std::cout <<  std:: endl << "================================================" << std::endl << std::endl;
    
    for(int x=0; x<matrix.getWidth(); x++)
    {
        for(int y=0; y<matrix.getHeight(); y++)
        {
            for(int z=0; z<matrix.getDepth(); z++)
            {
                std::cout << matrix.get(x, y, z).type << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
    
    std::cout << "================================================" << std::endl << std::endl;
}



