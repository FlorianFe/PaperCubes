//
//  OrthogamiFaceGroup.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <stdio.h>
#include "OrthogamiFaceGroup.h"

OrthogamiFaceGroup::OrthogamiFaceGroup()
{
    
}

void OrthogamiFaceGroup::pushOrthogamiFace(OrthogamiFace& orthogamiFace)
{
    this->orthogamiFaceVector.push_back(orthogamiFace);
}

OrthogamiFace& OrthogamiFaceGroup::getOrthogamiFace(int index)
{
    if(index < 0 || index >= this->getOrthogamiFaceSize()) throw "Out of Bounds Exception";
    return this->orthogamiFaceVector.at(index);
}

int OrthogamiFaceGroup::getOrthogamiFaceSize()
{
    return (int)(this->orthogamiFaceVector.size());
}
