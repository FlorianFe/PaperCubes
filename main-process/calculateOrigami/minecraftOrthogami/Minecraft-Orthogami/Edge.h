//
//  Edge.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef Edge_h
#define Edge_h

#include "Vector.h"

class Edge
{
    private:
        Vector vertex1;
        Vector vertex2;
    
    public:
        Edge();
        Edge(Vector vertex1, Vector vertex2);
        Vector getVertex1();
        Vector getVertex2();
    
        bool equals(Edge edge);
};

namespace tests
{
    bool testEdge();
}


#endif /* Edge_h */
