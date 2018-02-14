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

struct Tile
{
    unsigned int x;
    unsigned int y;
    unsigned int type;
    unsigned int metaType;
    Vector normal;
};

std::vector<Tile> calculateTiles(std::vector<Blueprint*> blueprintVector, std::vector<OrthogamiFace*> orthogamiFaceVector, Matrix matrix, unsigned int width, unsigned int height);

#endif /* calculateTiles_hpp */
