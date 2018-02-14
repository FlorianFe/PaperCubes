//
//  testEdge.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "Edge.h"

bool tests::testEdge()
{
    Vector vector1 = Vector(1, 0, 0);
    Vector vector2 = Vector(1, 1, 0);
    Vector vector3 = Vector(0, 1, 0);
    
    Edge edge1 = Edge(vector1, vector2);
    Edge edge2 = Edge(vector1, vector2);
    Edge edge3 = Edge(vector2, vector1);
    Edge edge4 = Edge(vector1, vector3);
    
    if(!edge1.equals(edge2)) return false;
    if(!edge1.equals(edge3)) return false;
    if(edge1.equals(edge4)) return false;
    
    return true;
}
