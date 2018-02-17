//
//  Face.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 01.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include "Face.h"
#include <stdlib.h>

Face::Face()
{
    this->northEdge = Edge();
    this->eastEdge = Edge();
    this->southEdge = Edge();
    this->westEdge = Edge();
    this->normal = Vector(0, 0, 0);
    this->blockCoordinates = Vector(0, 0, 0);
}

Face::Face(Vector blockCoordinates, Edge northEdge, Edge eastEdge, Edge southEdge, Edge westEdge, Vector normal)
{
    this->northEdge = northEdge;
    this->eastEdge = eastEdge;
    this->southEdge = southEdge;
    this->westEdge = westEdge;
    
    this->blockCoordinates = blockCoordinates;
    this->normal = normal;
}

Vector Face::getBlockCoordinates()
{
    return this->blockCoordinates;
}

bool Face::equals(Face face)
{
    if(!this->getNorthEdge().equals(face.getNorthEdge())) return false;
    if(!this->getEastEdge().equals(face.getEastEdge())) return false;
    if(!this->getSouthEdge().equals(face.getSouthEdge())) return false;
    if(!this->getWestEdge().equals(face.getWestEdge())) return false;
    
    return true;
}

bool Face::isIntersecting(Face face, Matrix& matrix)
{
    Vector differenceVector = face.getBlockCoordinates().subtract(this->getBlockCoordinates());
    int differenceSum = abs(differenceVector.getX()) + abs(differenceVector.getX()) + abs(differenceVector.getX());
    
    if(differenceSum != 1)
    {
        Vector blockCoordinates1 = this->getBlockCoordinates();
        Vector blockCoordinates2 = face.getBlockCoordinates();
        
        int x1 = blockCoordinates1.getX();
        int y1 = blockCoordinates1.getY();
        int z1 = blockCoordinates1.getZ();
        
        int x2 = blockCoordinates2.getX();
        int y2 = blockCoordinates2.getY();
        int z2 = blockCoordinates2.getZ();
        
        if(x1 == x2)
        {
            int v1 = matrix.get(x1, y2, z1).type;
            int v2 = matrix.get(x1, y1, z2).type;
            
            if(v1 <= 0 && v2 <= 0) return false;
        }
        
        if(y1 == y2)
        {
            int v1 = matrix.get(x2, y1, z1).type;
            int v2 = matrix.get(x1, y1, z2).type;
            
            if(v1 <= 0 && v2 <= 0) return false;
        }
        
        if(z1 == z2)
        {
            int v1 = matrix.get(x2, y1, z1).type;
            int v2 = matrix.get(x1, y2, z1).type;
            
            if(v1 <= 0 && v2 <= 0) return false;
        }
    }
    
    if(this->isIntersectingOnNorth(face)) return true;
    if(this->isIntersectingOnEast(face)) return true;
    if(this->isIntersectingOnSouth(face)) return true;
    if(this->isIntersectingOnWest(face)) return true;
    
    return false;
}

bool Face::isIntersectingOnNorth(Face face)
{
    if(this->getNorthEdge().equals(face.getNorthEdge())) return true;
    if(this->getNorthEdge().equals(face.getEastEdge())) return true;
    if(this->getNorthEdge().equals(face.getSouthEdge())) return true;
    if(this->getNorthEdge().equals(face.getWestEdge())) return true;
    
    return false;
}

bool Face::isIntersectingOnEast(Face face)
{
    if(this->getEastEdge().equals(face.getNorthEdge())) return true;
    if(this->getEastEdge().equals(face.getEastEdge())) return true;
    if(this->getEastEdge().equals(face.getSouthEdge())) return true;
    if(this->getEastEdge().equals(face.getWestEdge())) return true;
    
    return false;
}

bool Face::isIntersectingOnSouth(Face face)
{
    if(this->getSouthEdge().equals(face.getNorthEdge())) return true;
    if(this->getSouthEdge().equals(face.getEastEdge())) return true;
    if(this->getSouthEdge().equals(face.getSouthEdge())) return true;
    if(this->getSouthEdge().equals(face.getWestEdge())) return true;
    
    return false;
}

bool Face::isIntersectingOnWest(Face face)
{
    if(this->getWestEdge().equals(face.getNorthEdge())) return true;
    if(this->getWestEdge().equals(face.getEastEdge())) return true;
    if(this->getWestEdge().equals(face.getSouthEdge())) return true;
    if(this->getWestEdge().equals(face.getWestEdge())) return true;
    
    return false;
}

Edge Face::getintersectingEdge(Face face)
{    
    if(this->getNorthEdge().equals(face.getNorthEdge())) return this->northEdge;
    if(this->getNorthEdge().equals(face.getEastEdge())) return this->northEdge;
    if(this->getNorthEdge().equals(face.getSouthEdge())) return this->northEdge;
    if(this->getNorthEdge().equals(face.getWestEdge())) return this->northEdge;
    
    if(this->getEastEdge().equals(face.getEastEdge())) return this->eastEdge;
    if(this->getEastEdge().equals(face.getSouthEdge())) return this->eastEdge;
    if(this->getEastEdge().equals(face.getWestEdge())) return this->eastEdge;
    
    if(this->getSouthEdge().equals(face.getSouthEdge())) return this->southEdge;
    if(this->getSouthEdge().equals(face.getWestEdge())) return this->southEdge;
    
    if(this->getWestEdge().equals(face.getWestEdge())) return this->westEdge;
    
    throw "Faces are not intersecting";
    return Edge();
}

Edge Face::getNorthEdge()
{
    return this->northEdge;
}

Edge Face::getEastEdge()
{
    return this->eastEdge;
}

Edge Face::getSouthEdge()
{
    return this->southEdge;
}

Edge Face::getWestEdge()
{
    return this->westEdge;
}

Vector Face::getNormal()
{
    return this->normal;
}
