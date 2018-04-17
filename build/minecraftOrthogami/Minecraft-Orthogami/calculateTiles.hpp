//
//  calculateTiles.hpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 28.12.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef calculateTiles_hpp
#define calculateTiles_hpp

#include <vector>
#include "Vector.h"
#include "Blueprint.h"
#include "OrthogamiFace.h"
#include "Matrix.h"
#include "Block.h"

struct Tile
{
    unsigned int x;
    unsigned int y;
    Block block;
    Vector normal;
};

#endif /* calculateTiles_hpp */
