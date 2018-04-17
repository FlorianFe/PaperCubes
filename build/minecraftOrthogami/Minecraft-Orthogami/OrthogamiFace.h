//
//  OrthogamiFace.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef OrthogamiFace_h
#define OrthogamiFace_h

#include "Vector.h"

class OrthogamiFace
{
    private:
        int northEdge;
        int eastEdge;
        int southEdge;
        int westEdge;
    
        Vector normal;
        Vector blockCoordinates;
    
    public:
        OrthogamiFace();
        OrthogamiFace(Vector blockCoordinates, Vector normal);
    
        void setNorthEdge(int orthogamiEdge);
        void setEastEdge(int orthogamiEdge);
        void setSouthEdge(int orthogamiEdge);
        void setWestEdge(int orthogamiEdge);
        int getNorthEdge();
        int getEastEdge();
        int getSouthEdge();
        int getWestEdge();
        Vector getBlockCoordinates();
        Vector getNormal();
        bool isFullyConnected();
        bool isConnectedOnNorth();
        bool isConnectedOnEast();
        bool isConnectedOnSouth();
        bool isConnectedOnWest();
};


#endif /* OrthogamiFace_h */
