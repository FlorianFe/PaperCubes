//
//  OrthogamiEdge.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "OrthogamiEdge.h"

OrthogamiEdge& OrthogamiEdge::createFlatOrthogamiEdge(unsigned int face1, unsigned int face2)
{
    OrthogamiEdge* orthogamiEdge = new OrthogamiEdge(face1, face2, 1);
    return *orthogamiEdge;
}

OrthogamiEdge& OrthogamiEdge::createConcarveOrthogamiEdge(unsigned int face1, unsigned int face2)
{
    OrthogamiEdge* orthogamiEdge = new OrthogamiEdge(face1, face2, 2);
    return *orthogamiEdge;
}

OrthogamiEdge& OrthogamiEdge::createConvexOrthogamiEdge(unsigned int face1, unsigned int face2)
{
    OrthogamiEdge* orthogamiEdge = new OrthogamiEdge(face1, face2, 3);
    return *orthogamiEdge;
}

OrthogamiEdge::OrthogamiEdge()
{
    this->face1 = 0;
    this->face2 = 0;
    this->orientation = 0;
}

OrthogamiEdge::OrthogamiEdge(unsigned int face1, unsigned int face2, int orientation)
{
    this->face1 = face1;
    this->face2 = face2;
    this->orientation = orientation;
}

unsigned int OrthogamiEdge::getOrthogamiFace1()
{
    return this->face1;
}

unsigned int OrthogamiEdge::getOrthogamiFace2()
{
    return this->face2;
}

bool OrthogamiEdge::isFlat()
{
    return this->orientation == 1;
}

bool OrthogamiEdge::isConcarve()
{
    return this->orientation == 2;
}

bool OrthogamiEdge::isConvex()
{
    return this->orientation == 3;
}
