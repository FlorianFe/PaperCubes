//
//  Vector.hpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 01.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

class Vector
{
    private:
        int x;
        int y;
        int z;
    
    public:
        Vector();
        Vector(int x, int y, int z);
        Vector copy();
        bool equals(Vector vector);
        Vector add(Vector vector);
        Vector subtract(Vector vector);
        double getLength();
        int getX();
        int getY();
        int getZ();
        void setX(int x);
        void setY(int y);
        void setZ(int z);
};

namespace tests
{
    bool testVector();
}


#endif /* Vector_h */
