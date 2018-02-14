//
//  OrthogamiEdge.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef OrthogamiEdge_h
#define OrthogamiEdge_h

#include "Vector.h"

class OrthogamiEdge
{
    private:
        unsigned int face1;
        unsigned int face2;
        int orientation;
    
    public:
        static OrthogamiEdge& createConvexOrthogamiEdge(unsigned int face1, unsigned int face2);
        static OrthogamiEdge& createFlatOrthogamiEdge(unsigned int face1, unsigned int face2);
        static OrthogamiEdge& createConcarveOrthogamiEdge(unsigned int face1, unsigned int face2);
    
        OrthogamiEdge();
        OrthogamiEdge(unsigned int face1, unsigned int face2, int orientation);
    
        unsigned int getOrthogamiFace1();
        unsigned int getOrthogamiFace2();
    
        bool isConcarve();
        bool isConvex();
        bool isFlat();
};

#endif /* OrthogamiEdge_h */
