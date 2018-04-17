//
//  extractBlueprintVector.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <iostream>
#include <vector>
#include "extractBlueprintVector.h"
#include "Blueprint.h"
#include "Matrix.h"
#include "OrthogamiEdge.h"
#include "OrthogamiFace.h"

void extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(std::vector<OrthogamiFace*>& orthogamiFaceVector, std::vector<OrthogamiEdge*>& orthogamiEdgeVector, bool* orthogamiFaceMarkedArray, Blueprint& blueprint, unsigned int index, int x, int y, Matrix& matrix);

std::vector<Blueprint*> extractBlueprintVectorFromOrthogamiFaceVector(std::vector<OrthogamiFace*>& orthogamiFaceVector, std::vector<OrthogamiEdge*>& orthogamiEdgeVector, Matrix& matrix)
{
    std::vector<Blueprint*>* blueprintVector = new std::vector<Blueprint*>();
    
    if(orthogamiFaceVector.size() > 0)
    {
        bool* orthogamiFaceMarkedArray = new bool[orthogamiFaceVector.size()] { false };
        
        unsigned int blueprintIndex = 0;
        
        for(int i=0; i<orthogamiFaceVector.size(); i++)
        {
            if(!orthogamiFaceMarkedArray[i])
            {
                Vector normal = orthogamiFaceVector.at(i)->getNormal();
                Blueprint* blueprint = new Blueprint(normal);
                extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(orthogamiFaceVector, orthogamiEdgeVector, orthogamiFaceMarkedArray, *blueprint, i, 0, 0, matrix);
                blueprintVector->push_back(blueprint);
                //std::cout << "Blueprint size: " << blueprint->getSize() << " width: " << blueprint->getWidth() << " height: " << blueprint->getHeight() << std::endl;
                //std::cout << "x: " << normal.getX() << " y: " << normal.getY() << " z: " << normal.getZ() << std::endl;
                blueprintIndex++;
            }
        }
        
        delete [] orthogamiFaceMarkedArray;
    }
    
    return *blueprintVector;
}

void extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(std::vector<OrthogamiFace*>& orthogamiFaceVector, std::vector<OrthogamiEdge*>& orthogamiEdgeVector, bool* orthogamiFaceMarkedArray, Blueprint& blueprint, unsigned int index, int x, int y, Matrix& matrix)
{
    if(!orthogamiFaceMarkedArray[index])
    {
        orthogamiFaceMarkedArray[index] = true;
        
        OrthogamiFace* orthogamiFace = orthogamiFaceVector.at(index);
        
        OrthogamiEdge orthogamiNorthEdge = *orthogamiEdgeVector.at(orthogamiFace->getNorthEdge());
        OrthogamiEdge orthogamiEastEdge = *orthogamiEdgeVector.at(orthogamiFace->getEastEdge());
        OrthogamiEdge orthogamiSouthEdge = *orthogamiEdgeVector.at(orthogamiFace->getSouthEdge());
        OrthogamiEdge orthogamiWestEdge = *orthogamiEdgeVector.at(orthogamiFace->getWestEdge());
        
        unsigned int orthogamiFaceIndex1;
        unsigned int orthogamiFaceIndex2;
        
        orthogamiFaceIndex1 = orthogamiNorthEdge.getOrthogamiFace1();
        orthogamiFaceIndex2 = orthogamiNorthEdge.getOrthogamiFace2();
        unsigned int orthogamiNorthFaceIndex = (orthogamiFaceIndex1 == index) ? orthogamiFaceIndex2 : orthogamiFaceIndex1;
        
        orthogamiFaceIndex1 = orthogamiEastEdge.getOrthogamiFace1();
        orthogamiFaceIndex2 = orthogamiEastEdge.getOrthogamiFace2();
        unsigned int orthogamiEastFaceIndex = (orthogamiFaceIndex1 == index) ? orthogamiFaceIndex2 : orthogamiFaceIndex1;
        
        orthogamiFaceIndex1 = orthogamiSouthEdge.getOrthogamiFace1();
        orthogamiFaceIndex2 = orthogamiSouthEdge.getOrthogamiFace2();
        unsigned int orthogamiSouthFaceIndex = (orthogamiFaceIndex1 == index) ? orthogamiFaceIndex2 : orthogamiFaceIndex1;
        
        orthogamiFaceIndex1 = orthogamiWestEdge.getOrthogamiFace1();
        orthogamiFaceIndex2 = orthogamiWestEdge.getOrthogamiFace2();
        unsigned int orthogamiWestFaceIndex = (orthogamiFaceIndex1 == index) ? orthogamiFaceIndex2 : orthogamiFaceIndex1;
        
        blueprint.add(x, y, index);
        
        if(orthogamiNorthEdge.isFlat()) extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(orthogamiFaceVector, orthogamiEdgeVector, orthogamiFaceMarkedArray, blueprint, orthogamiNorthFaceIndex, x, y+1, matrix);
        if(orthogamiEastEdge.isFlat()) extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(orthogamiFaceVector, orthogamiEdgeVector, orthogamiFaceMarkedArray, blueprint, orthogamiEastFaceIndex, x+1, y, matrix);
        if(orthogamiSouthEdge.isFlat()) extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(orthogamiFaceVector, orthogamiEdgeVector, orthogamiFaceMarkedArray, blueprint, orthogamiSouthFaceIndex, x, y-1, matrix);
        if(orthogamiWestEdge.isFlat()) extractBlueprintVectorFromOrthogamiFaceVectorRecursivly(orthogamiFaceVector, orthogamiEdgeVector, orthogamiFaceMarkedArray, blueprint, orthogamiWestFaceIndex, x-1, y, matrix);
    }
}

