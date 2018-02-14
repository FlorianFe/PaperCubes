//
//  calculateLinks.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 28.12.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include "calculateLinks.hpp"
#include <map>

std::vector<Link> calculateLinks(std::vector<Blueprint*> blueprintVector, std::vector<OrthogamiFace*> orthogamiFaceVector)
{
    std::vector<Link> links;
    unsigned int writeHead = 0;
    
    std::map<unsigned int, unsigned int> map;
    unsigned int mapIndex = 0;
    
    for(unsigned int i=0; i<blueprintVector.size(); i++)
    {
        Blueprint* blueprint = blueprintVector.at(i);
        unsigned int blueprintWidth = blueprint->getWidth();
        unsigned int blueprintHeight = blueprint->getHeight();
        unsigned int typesSize = blueprintWidth*blueprintHeight;
        int* orthogamiFaceIndices = blueprint->get2DArray();
        
        for(unsigned int j=0; j<typesSize; j++)
        {
            unsigned int x = j % blueprintWidth;
            unsigned int y = j / blueprintWidth;
            
            if(orthogamiFaceIndices[j] >= 0)
            {
                if(x == 0)
                {
                    Link link;
                    link.x = x;
                    link.y = y + writeHead + 1;
                    link.orientationX = -1;
                    link.orientationY = 0;
                    
                    OrthogamiFace* orthogamiFace = orthogamiFaceVector.at(orthogamiFaceIndices[j]);
                    unsigned int edgeIndex = orthogamiFace->getWestEdge();
                    
                    if(map.count(edgeIndex) == 0)
                    {
                        map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                        mapIndex++;
                    }
                    
                    link.index = map.at(edgeIndex);
                    
                    links.push_back(link);
                }
                
                if(y == 0)
                {
                    Link link;
                    link.x = x + 1;
                    link.y = y + writeHead;
                    link.orientationX = 0;
                    link.orientationY = -1;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j])->getSouthEdge();
                    
                    if(map.count(edgeIndex) == 0)
                    {
                        map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                        mapIndex++;
                    }
                    
                    link.index = map.at(edgeIndex);
                    
                    links.push_back(link);
                }
                
                if(x == blueprintWidth - 1)
                {
                    Link link;
                    link.x = x + 2;
                    link.y = y + writeHead + 1;
                    link.orientationX = 1;
                    link.orientationY = 0;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j])->getEastEdge();
                    
                    if(map.count(edgeIndex) == 0)
                    {
                        map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                        mapIndex++;
                    }
                    
                    link.index = map.at(edgeIndex);
                    
                    links.push_back(link);
                }
                
                if(y == blueprintHeight - 1)
                {
                    Link link;
                    link.x = x + 1;
                    link.y = y + writeHead + 2;
                    link.orientationX = 0;
                    link.orientationY = 1;
                    
                    unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j])->getNorthEdge();
                    
                    if(map.count(edgeIndex) == 0)
                    {
                        map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                        mapIndex++;
                    }
                    
                    link.index = map.at(edgeIndex);
                    
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
                        link.x = x + 1;
                        link.y = y + writeHead + 1;
                        link.orientationX = 1;
                        link.orientationY = 0;
                        
                        unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j-1])->getWestEdge();
                        
                        if(map.count(edgeIndex) == 0)
                        {
                            map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                            mapIndex++;
                        }
                        
                        link.index = map.at(edgeIndex);
                        
                        links.push_back(link);
                    }
                }
                
                if(x < blueprintWidth - 1)
                {
                    if(orthogamiFaceIndices[j+1] >= 0)
                    {
                        Link link;
                        link.x = x + 1;
                        link.y = y + writeHead + 1;
                        link.orientationX = -1;
                        link.orientationY = 0;
                        
                        unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j+1])->getEastEdge();
                        
                        if(map.count(edgeIndex) == 0)
                        {
                            map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                            mapIndex++;
                        }
                        
                        link.index = map.at(edgeIndex);
                        
                        links.push_back(link);
                    }
                }
                
                if(y > 0)
                {
                    if(orthogamiFaceIndices[j-blueprintWidth] >= 0)
                    {
                        Link link;
                        link.x = x + 1;
                        link.y = y + writeHead + 1;
                        link.orientationX = 0;
                        link.orientationY = 1;
                        
                        unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j-blueprintWidth])->getSouthEdge();
                        
                        if(map.count(edgeIndex) == 0)
                        {
                            map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                            mapIndex++;
                        }
                        
                        link.index = map.at(edgeIndex);
                        
                        links.push_back(link);
                    }
                }
                
                if(y < blueprintHeight - 1)
                {
                    if(orthogamiFaceIndices[j+blueprintWidth] >= 0)
                    {
                        Link link;
                        link.x = x + 1;
                        link.y = y + writeHead + 1;
                        link.orientationX = 0;
                        link.orientationY = -1;
                        
                        unsigned int edgeIndex = orthogamiFaceVector.at(orthogamiFaceIndices[j+blueprintWidth])->getNorthEdge();
                        
                        if(map.count(edgeIndex) == 0)
                        {
                            map.insert(std::pair<unsigned int , unsigned int>(edgeIndex, mapIndex));
                            mapIndex++;
                        }
                        
                        link.index = map.at(edgeIndex);
                        
                        links.push_back(link);
                    }
                }
            }
        }
        
        writeHead += blueprintHeight + 1;
    }
    
    return links;
}
