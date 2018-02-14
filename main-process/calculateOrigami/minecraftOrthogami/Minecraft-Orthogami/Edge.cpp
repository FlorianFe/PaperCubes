//
//  Edge.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "Edge.h"

Edge::Edge()
{
    this->vertex1 = Vector(0, 0, 0);
    this->vertex2 = Vector(0, 0, 0);
}

Edge::Edge(Vector vertex1, Vector vertex2)
{
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
}

Vector Edge::getVertex1()
{
    return this->vertex1;
}

Vector Edge::getVertex2()
{
    return this->vertex2;
}

bool Edge::equals(Edge edge)
{
    if(this->vertex1.equals(edge.getVertex1()) && this->vertex2.equals(edge.getVertex2())) return true;
    if(this->vertex1.equals(edge.getVertex2()) && this->vertex2.equals(edge.getVertex1())) return true;
    
    return false;
}
