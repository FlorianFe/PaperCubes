//
//  OrthogamiFaceGroup.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef OrthogamiFaceGroup_h
#define OrthogamiFaceGroup_h

#include <vector>
#include "OrthogamiFace.h"

class OrthogamiFaceGroup
{
    private:
        std::vector<OrthogamiFace> orthogamiFaceVector;
    
    public:
        OrthogamiFaceGroup();
    
        void pushOrthogamiFace(OrthogamiFace& orthogamiFace);
        OrthogamiFace& getOrthogamiFace(int index);
        int getOrthogamiFaceSize();
};

#endif /* OrthogamiFaceGroup_h */
