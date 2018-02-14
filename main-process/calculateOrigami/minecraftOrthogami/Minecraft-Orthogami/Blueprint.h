//
//  Blueprint.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef Blueprint_h
#define Blueprint_h

#include <map>
#include "Vector.h"

class Blueprint
{
private:
    std::map<int, std::map<int, int>> map;
    int minX;
    int minY;
    int maxX;
    int maxY;
    bool empty;
    unsigned int size;
    Vector normal;
    
public:
    Blueprint(Vector normal);
    
    void add(int x, int y, int value);
    int* get2DArray();
    unsigned int getSize();
    unsigned int getWidth();
    Vector getNormal();
    unsigned int getHeight();
    int getMinX();
    int getMinY();
};

#endif /* Blueprint_h */
