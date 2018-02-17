//
//  calculatePages.hpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 05.01.18.
//  Copyright © 2018 Florian Fechner. All rights reserved.
//

#ifndef calculatePages_hpp
#define calculatePages_hpp

#include <vector>
#include "calculateTiles.hpp"
#include "calculateLinks.hpp"
#include "Blueprint.h"
#include "OrthogamiFace.h"
#include "OrthogamiEdge.h"
#include "Matrix.h"

struct Page
{
    std::vector<Tile> tiles;
    std::vector<Link> links;
};

std::vector<Page> calculatePages(std::vector<Blueprint*> blueprintVector, std::vector<OrthogamiFace*> orthogamiFaceVector, std::vector<OrthogamiEdge*> orthogamiEdgeVector, Matrix preparedMatrix, int tilesPerRow, int rowsPerPage);

#endif /* calculatePages_hpp */
