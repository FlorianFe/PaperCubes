//
//  calculatePages.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 05.01.18.
//  Copyright © 2018 Florian Fechner. All rights reserved.
//

#include "calculatePages.hpp"
#include <iostream>

std::vector<Tile> getTilesOfBlueprint(Blueprint blueprint, Matrix matrix, std::vector<OrthogamiFace*> orthogamiFaceVector, unsigned int BaseX, unsigned int baseY);
std::vector<Link> getLinksOfBlueprint(Blueprint blueprint, std::map<unsigned int, unsigned int>* map, unsigned int* mapIndex, std::vector<OrthogamiFace*> orthogamiFaceVector, unsigned int baseX, unsigned int baseY);

std::vector<Page> calculatePages(std::vector<Blueprint*> blueprintVector, std::vector<OrthogamiFace*> orthogamiFaceVector, Matrix matrix, int tilesPerRow, int rowsPerPage)
{
    std::vector<Page> pagesVector;
    
    Page page;
    int offsetWidthThisPage = 0;
    int offsetHeightThisPage = 0;
    int greatestHeightThisRow = 0;
    
    std::map<unsigned int, unsigned int> map;
    unsigned int mapIndex = 0;
    
    for(unsigned int i=0; i<blueprintVector.size(); i++)
    {
        Blueprint* blueprint = blueprintVector.at(i);
        int blueprintWidth = blueprint->getWidth();
        int blueprintHeight = blueprint->getHeight();
        
        std::cout << "Offset height: " << offsetHeightThisPage << " rowsPerPage: " << rowsPerPage << " blueprint height:  " << blueprintHeight << std::endl;
        
        if(blueprintHeight + greatestHeightThisRow + 2 > rowsPerPage - offsetHeightThisPage)
        {
            pagesVector.push_back(page);
            
            page.tiles.clear();
            page.links.clear();
            
            offsetWidthThisPage = 0;
            offsetHeightThisPage = 0;
            greatestHeightThisRow = 0;
        }
        
        if(blueprintWidth + 2 > tilesPerRow - offsetWidthThisPage)
        {
            offsetHeightThisPage += greatestHeightThisRow + 1;
            offsetWidthThisPage = 0;
        }
        
        std::vector<Tile> tilesOfBlueprint = getTilesOfBlueprint(*blueprint, matrix, orthogamiFaceVector, offsetWidthThisPage, offsetHeightThisPage);
        page.tiles.insert(page.tiles.end(), tilesOfBlueprint.begin(), tilesOfBlueprint.end());
        
        std::vector<Link> linksOfBlueprint = getLinksOfBlueprint(*blueprint, &map, &mapIndex, orthogamiFaceVector, offsetWidthThisPage, offsetHeightThisPage);
        page.links.insert(page.links.end(), linksOfBlueprint.begin(), linksOfBlueprint.end());
        
        offsetWidthThisPage += blueprintWidth + 1;
        
        if(blueprintHeight > greatestHeightThisRow)
        {
            greatestHeightThisRow = blueprintHeight;
        }
        
        std::cout << "Offset width: " << offsetWidthThisPage << " tilesPerRow: " << tilesPerRow << " blueprintWidth: " << blueprintWidth << std::endl;
    }
    
    pagesVector.push_back(page);
    
    return pagesVector;
}

std::vector<Tile> getTilesOfBlueprint(Blueprint blueprint, Matrix matrix, std::vector<OrthogamiFace*> orthogamiFaceVector, unsigned int baseX, unsigned int baseY)
{
    std::vector<Tile> tiles;
    
    unsigned int blueprintWidth = blueprint.getWidth();
    unsigned int blueprintHeight = blueprint.getHeight();
    unsigned int typesSize = blueprintWidth * blueprintHeight;
    int* orthogamiFaceIndices = blueprint.get2DArray();
    
    for(unsigned int j=0; j<typesSize; j++)
    {
        unsigned int x = j % blueprintWidth;
        unsigned int y = j / blueprintWidth;
        
        if(orthogamiFaceIndices[j] >= 0)
        {
            Tile tile;
            tile.x = x + baseX + 1;
            tile.y = y + baseY + 1;
            
            OrthogamiFace* orthogamiFace = orthogamiFaceVector.at(orthogamiFaceIndices[j]);
            Vector blockCoordinates = orthogamiFace->getBlockCoordinates();
            tile.type = matrix.get(blockCoordinates.getX(), blockCoordinates.getY(), blockCoordinates.getZ()).type;
            tile.metaType = matrix.get(blockCoordinates.getX(), blockCoordinates.getY(), blockCoordinates.getZ()).metaType;
            tile.normal = blueprint.getNormal();
            
            tiles.push_back(tile);
        }
    }
    
    return tiles;
}

std::vector<Link> getLinksOfBlueprint(Blueprint blueprint, std::map<unsigned int, unsigned int>* map, unsigned int* mapIndex, std::vector<OrthogamiFace*> orthogamiFaceVector, unsigned int baseX, unsigned int baseY)
{
    std::vector<Link> links;
    
    unsigned int blueprintWidth = blueprint.getWidth();
    unsigned int blueprintHeight = blueprint.getHeight();
    unsigned int typesSize = blueprintWidth*blueprintHeight;
    int* orthogamiFaceIndices = blueprint.get2DArray();
    
    for(unsigned int j=0; j<typesSize; j++)
    {
        unsigned int x = j % blueprintWidth;
        unsigned int y = j / blueprintWidth;
        
        if(orthogamiFaceIndices[j] >= 0)
        {
            if(x == 0)
            {
                Link link;
                link.x = x + baseX;
                link.y = y + baseY + 1;
                link.orientationX = -1;
                link.orientationY = 0;
                
                OrthogamiFace* orthogamiFace = orthogamiFaceVector.at(orthogamiFaceIndices[j]);
                unsigned int edgeIndex = orthogamiFace->getWestEdge();
                
                if(map->count(edgeIndex) == 0)
                {
                    map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                    *mapIndex = *mapIndex + 1;
                    link.opened = true;
                }
                else
                {
                    link.opened = false;
                }
                
                link.index = map->at(edgeIndex);
                
                links.push_back(link);
            }
            
            if(y == 0)
            {
                Link link;
                link.x = x + baseX + 1;
                link.y = y + baseY;
                link.orientationX = 0;
                link.orientationY = -1;
                
                unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j])->getSouthEdge();
                
                if(map->count(edgeIndex) == 0)
                {
                    map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                    *mapIndex = *mapIndex + 1;
                    link.opened = true;
                }
                else
                {
                    link.opened = false;
                }
                
                link.index = map->at(edgeIndex);
                
                links.push_back(link);
            }
            
            if(x == blueprintWidth - 1)
            {
                Link link;
                link.x = x + baseX + 2;
                link.y = y + baseY + 1;
                link.orientationX = 1;
                link.orientationY = 0;
                
                unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j])->getEastEdge();
                
                if(map->count(edgeIndex) == 0)
                {
                    map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                    *mapIndex = *mapIndex + 1;
                    link.opened = true;
                }
                else
                {
                    link.opened = false;
                }
                
                link.index = map->at(edgeIndex);
                
                links.push_back(link);
            }
            
            if(y == blueprintHeight - 1)
            {
                Link link;
                link.x = x + baseX + 1;
                link.y = y + baseY + 2;
                link.orientationX = 0;
                link.orientationY = 1;
                
                unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j])->getNorthEdge();
                
                if(map->count(edgeIndex) == 0)
                {
                    map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                    *mapIndex = *mapIndex + 1;
                    link.opened = true;
                }
                else
                {
                    link.opened = false;
                }
                
                link.index = map->at(edgeIndex);
                
                links.push_back(link);
            }
        }
        else
        {
            if(x > 0)
            {
                if(orthogamiFaceIndices[j-1] >= 0)
                {
                    Link link;
                    link.x = x + baseX + 1;
                    link.y = y + baseY + 1;
                    link.orientationX = 1;
                    link.orientationY = 0;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j-1])->getEastEdge();
                    
                    if(map->count(edgeIndex) == 0)
                    {
                        map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                        *mapIndex = *mapIndex + 1;
                        link.opened = true;
                    }
                    else
                    {
                        link.opened = false;
                    }
                    
                    link.index = map->at(edgeIndex);
                    
                    links.push_back(link);
                }
            }
            
            if(x < blueprintWidth - 1)
            {
                if(orthogamiFaceIndices[j+1] >= 0)
                {
                    Link link;
                    link.x = x + baseX + 1;
                    link.y = y + baseY + 1;
                    link.orientationX = -1;
                    link.orientationY = 0;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j+1])->getWestEdge();
                    
                    if(map->count(edgeIndex) == 0)
                    {
                        map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                        *mapIndex = *mapIndex + 1;
                        link.opened = true;
                    }
                    else
                    {
                        link.opened = false;
                    }
                    
                    link.index = map->at(edgeIndex);
                    
                    links.push_back(link);
                }
            }
            
            if(y > 0)
            {
                if(orthogamiFaceIndices[j-blueprintWidth] >= 0)
                {
                    Link link;
                    link.x = x + baseX + 1;
                    link.y = y + baseY + 1;
                    link.orientationX = 0;
                    link.orientationY = 1;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j-blueprintWidth])->getNorthEdge();
                    
                    if(map->count(edgeIndex) == 0)
                    {
                        map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                        *mapIndex = *mapIndex + 1;
                        link.opened = true;
                    }
                    else
                    {
                        link.opened = false;
                    }
                    
                    link.index = map->at(edgeIndex);
                    
                    links.push_back(link);
                }
            }
            
            if(y < blueprintHeight - 1)
            {
                if(orthogamiFaceIndices[j+blueprintWidth] >= 0)
                {
                    Link link;
                    link.x = x + baseX + 1;
                    link.y = y + baseY + 1;
                    link.orientationX = 0;
                    link.orientationY = -1;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j+blueprintWidth])->getSouthEdge();
                    
                    if(map->count(edgeIndex) == 0)
                    {
                        map->insert(std::pair<unsigned int , unsigned int>(edgeIndex, *mapIndex));
                        *mapIndex = *mapIndex + 1;
                        link.opened = true;
                    }
                    else
                    {
                        link.opened = false;
                    }
                    
                    link.index = map->at(edgeIndex);
                    
                    links.push_back(link);
                }
            }
        }
    }
    
    return links;
}

