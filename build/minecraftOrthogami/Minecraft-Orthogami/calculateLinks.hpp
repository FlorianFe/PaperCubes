//
//  calculateLinks.hpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 28.12.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef calculateLinks_hpp
#define calculateLinks_hpp

#include <vector>
#include "Blueprint.h"
#include "OrthogamiFace.h"

struct Link
{
    unsigned int index;
    unsigned int x;
    unsigned int y;
    unsigned int orientationX;
    unsigned int orientationY;
    bool opened;
    bool concarve;
};

std::vector<Link> calculateLinks(std::vector<Blueprint*> blueprintVector, std::vector<OrthogamiFace*> orthogamiFaceVector);

#endif /* calculateLinks_hpp */
