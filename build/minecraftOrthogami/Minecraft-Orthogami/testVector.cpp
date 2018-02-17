//
//  testVector.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 03.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "Vector.h"

bool tests::testVector()
{
    Vector vector1 = Vector(1, 0, 0);
    Vector vector2 = Vector(1, 0, 0);
    Vector vector3 = Vector(0, 1, 0);
    
    if(!vector1.equals(vector2)) return false;
    if(vector1.equals(vector3)) return false;
    
    return true;
}


