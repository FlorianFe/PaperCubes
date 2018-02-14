//
//  OrthogamiFace.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "OrthogamiFace.h"

OrthogamiFace::OrthogamiFace()
{
    this->northEdge = -1;
    this->westEdge = -1;
    this->southEdge = -1;
    this->eastEdge = -1;
    
    this->normal = Vector(0, 0, 0);
    this->blockCoordinates = Vector(0, 0, 0);
}

OrthogamiFace::OrthogamiFace(Vector blockCoordinates, Vector normal)
{
    this->northEdge = -1;
    this->westEdge = -1;
    this->southEdge = -1;
    this->eastEdge = -1;
    
    this->normal = normal;
    this->blockCoordinates = blockCoordinates;
}

void OrthogamiFace::setNorthEdge(int orthogamiEdge)
{
    if(this->northEdge != -1) throw "Edge already setted";
    this->northEdge = orthogamiEdge;
}

void OrthogamiFace::setEastEdge(int orthogamiEdge)
{
    if(this->eastEdge != -1) throw "Edge already setted";
    this->eastEdge = orthogamiEdge;
}

void OrthogamiFace::setSouthEdge(int orthogamiEdge)
{
    if(this->southEdge != -1) throw "Edge already setted";
    this->southEdge = orthogamiEdge;
}

void OrthogamiFace::setWestEdge(int orthogamiEdge)
{
    if(this->westEdge != -1) throw "Edge already setted";
    this->westEdge = orthogamiEdge;
}

int OrthogamiFace::getNorthEdge()
{
    if(this->northEdge == -1) throw "Nullpoiter Exception";
    return this->northEdge;
}

int OrthogamiFace::getWestEdge()
{
    if(this->westEdge == -1) throw "Nullpoiter Exception";
    return this->westEdge;
}

int OrthogamiFace::getSouthEdge()
{
    if(this->southEdge == -1) throw "Nullpoiter Exception";
    return this->southEdge;
}

int OrthogamiFace::getEastEdge()
{
    if(this->eastEdge == -1) throw "Nullpoiter Exception";
    return this->eastEdge;
}

Vector OrthogamiFace::getBlockCoordinates()
{
    return this->blockCoordinates;
}

Vector OrthogamiFace::getNormal()
{
    return this->normal;
}

bool OrthogamiFace::isFullyConnected()
{
    if(this->northEdge == -1) return false;
    if(this->eastEdge == -1) return false;
    if(this->southEdge == -1) return false;
    if(this->westEdge == -1) return false;
    
    return true;
}

bool OrthogamiFace::isConnectedOnNorth()
{
    return (this->northEdge != -1);
}

bool OrthogamiFace::isConnectedOnEast()
{
    return (this->eastEdge != -1);
}

bool OrthogamiFace::isConnectedOnSouth()
{
    return (this->southEdge != -1);
}

bool OrthogamiFace::isConnectedOnWest()
{
    return (this->westEdge != -1);
}
