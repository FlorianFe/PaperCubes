//
//  calculateTiles.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 28.12.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <iostream>
#include "calculateTiles.hpp"

std::vector<Tile> calculateTiles(std::vector<Blueprint*> blueprintVector, std::vector<OrthogamiFace*> orthogamiFaceVector, Matrix matrix, unsigned int width, unsigned int height)
{
    std::vector<Tile> tiles;
    unsigned int writeHead = 0;
    
    for(unsigned int i=0; i<blueprintVector.size(); i++)
    {
        Blueprint* blueprint = blueprintVector.at(i);
        unsigned int blueprintWidth = blueprint->getWidth();
        unsigned int blueprintHeight = blueprint->getHeight();
        unsigned int typesSize = blueprintWidth * blueprintHeight;
        int* orthogamiFaceIndices = blueprint->get2DArray();
        int blueprintMinX = blueprint->getMinX();
        int blueprintMinY = blueprint->getMinY();
        
        std::cout << "Blueprint width: " << blueprintWidth << " width: " << width;
        std::cout << "Blueprint height: " << blueprintHeight << " height: " << height;
        
        for(unsigned int j=0; j<typesSize; j++)
        {
            unsigned int x = j % blueprintWidth;
            unsigned int y = j / blueprintWidth;
            
            if(orthogamiFaceIndices[j] >= 0)
            {
                Tile tile;
                tile.x = x + 1;
                tile.y = y + writeHead + 1;
                
                OrthogamiFace orthogamiFace = *orthogamiFaceVector.at(orthogamiFaceIndices[j]);
                Vector blockCoordinates = orthogamiFace.getBlockCoordinates();
                tile.type = matrix.get(blockCoordinates.getX(), blockCoordinates.getY(), blockCoordinates.getZ()).type;
                tile.metaType = matrix.get(blockCoordinates.getX(), blockCoordinates.getY(), blockCoordinates.getZ()).metaType;
                tile.normal = blueprint->getNormal();
                
                tiles.push_back(tile);
                
                std::cout << "Blueprint: min-x: " << blueprintMinX << " min-y: " << blueprintMinY << " index: " << i << " Tile: " << " x: " << tile.x << " y: " << tile.y << " type: " << tile.type << std::endl;
            }
        }
        
        writeHead += blueprintHeight + 1;
    }
    
    return tiles;
}
