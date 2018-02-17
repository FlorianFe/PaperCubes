//
//  Face.hpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 01.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef Face_h
#define Face_h

#include "Vector.h"
#include "Edge.h"
#include "Matrix.h"

class Face
{
    private:
        Edge northEdge;
        Edge eastEdge;
        Edge southEdge;
        Edge westEdge;
        Vector normal;
        Vector blockCoordinates;
    
    public:
        Face();
        Face(Vector blockCoordinates, Edge northEdge, Edge eastEdge, Edge southEdge, Edge westEdge, Vector normal);
        bool equals(Face face);
        bool isIntersecting(Face face, Matrix& matrix);
        bool isIntersectingOnNorth(Face face);
        bool isIntersectingOnEast(Face face);
        bool isIntersectingOnSouth(Face face);
        bool isIntersectingOnWest(Face face);
        Edge getintersectingEdge(Face face);
        Vector getBlockCoordinates();
        Edge getNorthEdge();
        Edge getEastEdge();
        Edge getSouthEdge();
        Edge getWestEdge();
        Vector getNormal();
};

namespace tests
{
    bool testFace();
}

#endif /* Face_h */
