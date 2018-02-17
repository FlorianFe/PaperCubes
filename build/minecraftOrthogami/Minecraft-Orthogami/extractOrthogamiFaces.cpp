//
//  extractOrthogamiFaces.cpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 28.12.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <iostream>

#include "Face.h"
#include "Edge.h"
#include "OrthogamiEdge.h"
#include "extractOrthogamiFaces.hpp"

std::vector<Face>& extractFacesFromMatrix(Matrix& matrix);
std::vector<OrthogamiFace*>& extractOrthogamiFacesFromFaceVector(std::vector<Face>& faceVector, Matrix& matrix);
std::vector<OrthogamiEdge*> extractOrthogamiEdgesFromFaceVector(std::vector<Face>& faceVector, Matrix& matrix);
void printFacesVector(std::vector<Face>& facesVector);
void printOrthogamiEdgesVector(std::vector<OrthogamiEdge*>& orthogamiEdgesVector);
void printOrthogamiFacesVector(std::vector<OrthogamiFace*>& orthogamiFacesVector);

std::vector<OrthogamiFace*> extractOrthogamiFaces(Matrix& matrix)
{
    std::vector<Face> faceVector = extractFacesFromMatrix(matrix);
    std::vector<OrthogamiFace*> orthogamiFacesVector = extractOrthogamiFacesFromFaceVector(faceVector, matrix);
    
    return orthogamiFacesVector;
}

std::vector<OrthogamiEdge*> extractOrthogamiEdges(Matrix& matrix)
{
    std::vector<Face> faceVector = extractFacesFromMatrix(matrix);
    std::vector<OrthogamiEdge*> orthogamiEdgesVector = extractOrthogamiEdgesFromFaceVector(faceVector, matrix);
    
    return orthogamiEdgesVector;
}

std::vector<Face>& extractFacesFromMatrix(Matrix& matrix)
{
    std::vector<Face>* faceVector = new std::vector<Face>();
    
    int lastXValue = 0;
    int lastYValue = 0;
    int lastZValue = 0;
    
    for(int x=0; x<matrix.getWidth(); x++)
    {
        for(int y=0; y<matrix.getHeight(); y++)
        {
            for(int z=0; z<matrix.getDepth(); z++)
            {
                int zValue = matrix.get(x, y, z).type;
                
                if(lastZValue == 0 && zValue != 0)
                {
                    Vector blockCoordinates = Vector(x, y, z);
                    Vector vertex1(x, y+1, z);
                    Vector vertex2(x+1, y+1, z);
                    Vector vertex3(x+1, y, z);
                    Vector vertex4(x, y, z);
                    
                    Vector normal = Vector(0, 0, -1);
                    
                    Edge northEdge(vertex3, vertex4);
                    Edge eastEdge(vertex2, vertex3);
                    Edge southEdge(vertex1, vertex2);
                    Edge westEdge(vertex4, vertex1);
                    
                    Face face = Face(blockCoordinates, northEdge, eastEdge, southEdge, westEdge, normal);
                    faceVector->push_back(face);
                }
                
                if(lastZValue != 0 && zValue == 0)
                {
                    Vector blockCoordinates = Vector(x, y, z-1);
                    Vector vertex1(x+1, y+1, z);
                    Vector vertex2(x, y+1, z);
                    Vector vertex3(x, y, z);
                    Vector vertex4(x+1, y, z);
                    
                    Vector normal = Vector(0, 0, 1);
                    
                    Edge northEdge(vertex3, vertex4);
                    Edge eastEdge(vertex2, vertex3);
                    Edge southEdge(vertex1, vertex2);
                    Edge westEdge(vertex4, vertex1);
                    
                    Face face = Face(blockCoordinates, northEdge, eastEdge, southEdge, westEdge, normal);
                    faceVector->push_back(face);
                }
                
                lastZValue = zValue;
            }
        }
    }
    
    for(int x=0; x<matrix.getWidth(); x++)
    {
        for(int z=0; z<matrix.getDepth(); z++)
        {
            for(int y=0; y<matrix.getHeight(); y++)
            {
                int yValue = matrix.get(x, y, z).type;
                
                if(lastYValue == 0 && yValue != 0)
                {
                    Vector blockCoordinates = Vector(x, y, z);
                    Vector vertex1(x+1, y, z);
                    Vector vertex2(x, y, z);
                    Vector vertex3(x, y, z+1);
                    Vector vertex4(x+1, y, z+1);
                    
                    Vector normal = Vector(0, -1, 0);
                    
                    Edge northEdge(vertex1, vertex2);
                    Edge eastEdge(vertex2, vertex3);
                    Edge southEdge(vertex3, vertex4);
                    Edge westEdge(vertex4, vertex1);
                    
                    Face face = Face(blockCoordinates, northEdge, eastEdge, southEdge, westEdge, normal);
                    faceVector->push_back(face);
                }
                
                if(lastYValue != 0 && yValue == 0)
                {
                    Vector blockCoordinates = Vector(x, y-1, z);
                    Vector vertex1(x, y, z);
                    Vector vertex2(x+1, y, z);
                    Vector vertex3(x+1, y, z+1);
                    Vector vertex4(x, y, z+1);
                    
                    Vector normal = Vector(0, 1, 0);
                    
                    Edge southEdge(vertex1, vertex2);
                    Edge westEdge(vertex2, vertex3);
                    Edge northEdge(vertex3, vertex4);
                    Edge eastEdge(vertex4, vertex1);
                    
                    Face face = Face(blockCoordinates, northEdge, eastEdge, southEdge, westEdge, normal);
                    
                    faceVector->push_back(face);
                }
                
                lastYValue = yValue;
            }
        }
    }
    
    for(int z=0; z<matrix.getDepth(); z++)
    {
        for(int y=0; y<matrix.getHeight(); y++)
        {
            for(int x=0; x<matrix.getWidth(); x++)
            {
                int xValue = matrix.get(x, y, z).type;
                
                if(lastXValue == 0 && xValue != 0)
                {
                    Vector blockCoordinates = Vector(x, y, z);
                    Vector vertex1(x, y+1, z+1);
                    Vector vertex2(x, y, z+1);
                    Vector vertex3(x, y, z);
                    Vector vertex4(x, y+1, z);
                    
                    Vector normal = Vector(-1, 0, 0);
                    
                    Edge northEdge(vertex2, vertex3);
                    Edge eastEdge(vertex3, vertex4);
                    Edge southEdge(vertex1, vertex4);
                    Edge westEdge(vertex1, vertex2);
                    
                    Face face = Face(blockCoordinates, northEdge, eastEdge, southEdge, westEdge, normal);
                    faceVector->push_back(face);
                }
                
                if(lastXValue != 0 && xValue == 0)
                {
                    Vector blockCoordinates = Vector(x-1, y, z);
                    Vector vertex1(x, y+1, z);
                    Vector vertex2(x, y, z);
                    Vector vertex3(x, y, z+1);
                    Vector vertex4(x, y+1, z+1);
                    
                    Vector normal = Vector(1, 0, 0);
                    
                    Edge northEdge(vertex2, vertex3);
                    Edge eastEdge(vertex3, vertex4);
                    Edge southEdge(vertex1, vertex4);
                    Edge westEdge(vertex1, vertex2);
                    
                    Face face = Face(blockCoordinates, northEdge, eastEdge, southEdge, westEdge, normal);
                    faceVector->push_back(face);
                }
                
                lastXValue = xValue;
            }
        }
    }
    
    return *faceVector;
}

std::vector<OrthogamiFace*>& extractOrthogamiFacesFromFaceVector(std::vector<Face>& faceVector, Matrix& matrix)
{
    std::vector<OrthogamiFace*>* orthogamiFaceVector = new std::vector<OrthogamiFace*>();
    std::vector<OrthogamiEdge*>* orthogamiEdgeVector = new std::vector<OrthogamiEdge*>();
    
    for(std::vector<Face>::iterator iterator = faceVector.begin(); iterator != faceVector.end(); ++iterator)
    {
        Face face = *iterator;
        Vector normal = face.getNormal();
        Vector blockCoordinates = face.getBlockCoordinates();
        
        OrthogamiFace* orthogamiFace = new OrthogamiFace(blockCoordinates, normal);
        
        orthogamiFaceVector->push_back(orthogamiFace);
    }
    
    int index1 = 0;
    int orthogamiEdgeIndex = 0;
    
    for(std::vector<Face>::iterator iterator1 = faceVector.begin(); iterator1 != faceVector.end(); ++iterator1)
    {
        Face face1 = *iterator1;
        
        int index2 = 0;
        
        for(std::vector<Face>::iterator iterator2 = faceVector.begin(); iterator2 != faceVector.end(); ++iterator2)
        {
            Face face2 = *iterator2;
            
            if(index2 > index1)
            {
                if(face1.isIntersecting(face2, matrix))
                {
                    Vector blockVector1 = face1.getBlockCoordinates();
                    Vector blockVector2 = face2.getBlockCoordinates();
                    Vector normal1 = face1.getNormal();
                    Vector normal2 = face2.getNormal();
                    
                    OrthogamiEdge* orthogamiEdge;
                    
                    OrthogamiFace* orthogamiFace1 = orthogamiFaceVector->at(index1);
                    OrthogamiFace* orthogamiFace2 = orthogamiFaceVector->at(index2);
                    
                    if(normal1.equals(normal2))
                    {
                        orthogamiEdge = &OrthogamiEdge::createFlatOrthogamiEdge(index1, index2);
                    }
                    else
                    {
                        Vector movedBlockVector1 = blockVector1.add(normal1);
                        Vector movedBlockVector2 = blockVector2.add(normal2);
                        
                        if(movedBlockVector1.equals(movedBlockVector2))
                        {
                            orthogamiEdge = &OrthogamiEdge::createConcarveOrthogamiEdge(index1, index2);
                        }
                        else
                        {
                            orthogamiEdge = &OrthogamiEdge::createConvexOrthogamiEdge(index1, index2);
                        }
                    }
                    
                    if(face1.isIntersectingOnNorth(face2)) orthogamiFace1->setNorthEdge(orthogamiEdgeIndex);
                    if(face1.isIntersectingOnEast(face2)) orthogamiFace1->setEastEdge(orthogamiEdgeIndex);
                    if(face1.isIntersectingOnSouth(face2)) orthogamiFace1->setSouthEdge(orthogamiEdgeIndex);
                    if(face1.isIntersectingOnWest(face2)) orthogamiFace1->setWestEdge(orthogamiEdgeIndex);
                    
                    if(face2.isIntersectingOnNorth(face1)) orthogamiFace2->setNorthEdge(orthogamiEdgeIndex);
                    if(face2.isIntersectingOnEast(face1)) orthogamiFace2->setEastEdge(orthogamiEdgeIndex);
                    if(face2.isIntersectingOnSouth(face1)) orthogamiFace2->setSouthEdge(orthogamiEdgeIndex);
                    if(face2.isIntersectingOnWest(face1)) orthogamiFace2->setWestEdge(orthogamiEdgeIndex);
                    
                    orthogamiEdgeVector->push_back(orthogamiEdge);
                    
                    orthogamiEdgeIndex++;
                }
            }
            
            index2++;
        }
        
        index1++;
    }
    
    printOrthogamiEdgesVector(*orthogamiEdgeVector);
    
    return *orthogamiFaceVector;
}


// TODO: Enthält ggf. viel Redundanz!
std::vector<OrthogamiEdge*> extractOrthogamiEdgesFromFaceVector(std::vector<Face>& faceVector, Matrix& matrix)
{
    std::vector<OrthogamiFace*>* orthogamiFaceVector = new std::vector<OrthogamiFace*>();
    std::vector<OrthogamiEdge*>* orthogamiEdgeVector = new std::vector<OrthogamiEdge*>();
    
    for(std::vector<Face>::iterator iterator = faceVector.begin(); iterator != faceVector.end(); ++iterator)
    {
        Face face = *iterator;
        Vector normal = face.getNormal();
        Vector blockCoordinates = face.getBlockCoordinates();
        
        OrthogamiFace* orthogamiFace = new OrthogamiFace(blockCoordinates, normal);
        
        orthogamiFaceVector->push_back(orthogamiFace);
    }
    
    int index1 = 0;
    int orthogamiEdgeIndex = 0;
    
    for(std::vector<Face>::iterator iterator1 = faceVector.begin(); iterator1 != faceVector.end(); ++iterator1)
    {
        Face face1 = *iterator1;
        
        int index2 = 0;
        
        for(std::vector<Face>::iterator iterator2 = faceVector.begin(); iterator2 != faceVector.end(); ++iterator2)
        {
            Face face2 = *iterator2;
            
            if(index2 > index1)
            {
                if(face1.isIntersecting(face2, matrix))
                {
                    Vector blockVector1 = face1.getBlockCoordinates();
                    Vector blockVector2 = face2.getBlockCoordinates();
                    Vector normal1 = face1.getNormal();
                    Vector normal2 = face2.getNormal();
                    
                    OrthogamiEdge* orthogamiEdge;
                    
                    OrthogamiFace* orthogamiFace1 = orthogamiFaceVector->at(index1);
                    OrthogamiFace* orthogamiFace2 = orthogamiFaceVector->at(index2);
                    
                    if(normal1.equals(normal2))
                    {
                        orthogamiEdge = &OrthogamiEdge::createFlatOrthogamiEdge(index1, index2);
                    }
                    else
                    {
                        Vector movedBlockVector1 = blockVector1.add(normal1);
                        Vector movedBlockVector2 = blockVector2.add(normal2);
                        
                        if(movedBlockVector1.equals(movedBlockVector2))
                        {
                            orthogamiEdge = &OrthogamiEdge::createConcarveOrthogamiEdge(index1, index2);
                        }
                        else
                        {
                            orthogamiEdge = &OrthogamiEdge::createConvexOrthogamiEdge(index1, index2);
                        }
                    }
                    
                    if(face1.isIntersectingOnNorth(face2)) orthogamiFace1->setNorthEdge(orthogamiEdgeIndex);
                    if(face1.isIntersectingOnEast(face2)) orthogamiFace1->setEastEdge(orthogamiEdgeIndex);
                    if(face1.isIntersectingOnSouth(face2)) orthogamiFace1->setSouthEdge(orthogamiEdgeIndex);
                    if(face1.isIntersectingOnWest(face2)) orthogamiFace1->setWestEdge(orthogamiEdgeIndex);
                    
                    if(face2.isIntersectingOnNorth(face1)) orthogamiFace2->setNorthEdge(orthogamiEdgeIndex);
                    if(face2.isIntersectingOnEast(face1)) orthogamiFace2->setEastEdge(orthogamiEdgeIndex);
                    if(face2.isIntersectingOnSouth(face1)) orthogamiFace2->setSouthEdge(orthogamiEdgeIndex);
                    if(face2.isIntersectingOnWest(face1)) orthogamiFace2->setWestEdge(orthogamiEdgeIndex);
                    
                    orthogamiEdgeVector->push_back(orthogamiEdge);
                    
                    orthogamiEdgeIndex++;
                }
            }
            
            index2++;
        }
        
        index1++;
    }
    
    printOrthogamiEdgesVector(*orthogamiEdgeVector);
    
    delete orthogamiFaceVector;
    
    return *orthogamiEdgeVector;
}

void printFacesVector(std::vector<Face>& facesVector)
{
    int count = 0;
    
    for(std::vector<Face>::iterator iterator = facesVector.begin(); iterator != facesVector.end(); ++iterator)
    {
        Face face = *iterator;
        Vector blockCoordinates = face.getBlockCoordinates();
        Edge edge1 = face.getNorthEdge();
        Edge edge2 = face.getEastEdge();
        Edge edge3 = face.getSouthEdge();
        Edge edge4 = face.getWestEdge();
        
        std::cout << blockCoordinates.getX() << " " << blockCoordinates.getY() << " " << blockCoordinates.getZ() << " " << std:: endl;
        
        std::cout << "Edge 1 : ";
        std::cout << edge1.getVertex1().getX() << " " << edge1.getVertex1().getY() << " " << edge1.getVertex1().getZ() << " / ";
        std::cout << edge1.getVertex2().getX() << " " << edge1.getVertex2().getY() << " " << edge1.getVertex2().getZ() << std:: endl;
        
        std::cout << "Edge 2 : ";
        std::cout << edge2.getVertex1().getX() << " " << edge2.getVertex1().getY() << " " << edge2.getVertex1().getZ() << " / ";
        std::cout << edge2.getVertex2().getX() << " " << edge2.getVertex2().getY() << " " << edge2.getVertex2().getZ() << std:: endl;
        
        std::cout << "Edge 3 : ";
        std::cout << edge3.getVertex1().getX() << " " << edge3.getVertex1().getY() << " " << edge3.getVertex1().getZ() << " / ";
        std::cout << edge3.getVertex2().getX() << " " << edge3.getVertex2().getY() << " " << edge3.getVertex2().getZ() << std:: endl;
        
        std::cout << "Edge 4 : ";
        std::cout << edge4.getVertex1().getX() << " " << edge4.getVertex1().getY() << " " << edge4.getVertex1().getZ() << " / ";
        std::cout << edge4.getVertex2().getX() << " " << edge4.getVertex2().getY() << " " << edge4.getVertex2().getZ() << std:: endl;
        
        std::cout << "---------------------------" << std::endl;
        
        count ++;
    }
    
    std::cout << count << " faces found " << std::endl;
}

void printOrthogamiFacesVector(std::vector<OrthogamiFace*>& orthogamiFacesVector)
{
    int index = 0;
    for(std::vector<OrthogamiFace*>::iterator iterator = orthogamiFacesVector.begin(); iterator != orthogamiFacesVector.end(); ++iterator)
    {
        OrthogamiFace* orthogamiFace = *iterator;
        
        std::cout << index << " " << orthogamiFace->isConnectedOnNorth() << orthogamiFace->isConnectedOnEast() << orthogamiFace->isConnectedOnSouth() << orthogamiFace->isConnectedOnWest() << std::endl;
        index++;
    }
}

void printOrthogamiEdgesVector(std::vector<OrthogamiEdge*>& orthogamiEdgesVector)
{
    int countOrthogamiEdges = 0;
    int countFlat = 0;
    int countConvex = 0;
    int countConcarve = 0;
    
    for(std::vector<OrthogamiEdge*>::iterator iterator = orthogamiEdgesVector.begin(); iterator != orthogamiEdgesVector.end(); ++iterator)
    {
        OrthogamiEdge* orthogamiEdge = *iterator;
        
        countOrthogamiEdges++;
        
        if(orthogamiEdge->isFlat()) countFlat++;
        if(orthogamiEdge->isConvex()) countConvex++;
        if(orthogamiEdge->isConcarve()) countConcarve++;
    }
    
    std::cout << countOrthogamiEdges << " edges found (flat: " << countFlat << ", convex " << countConvex << ", concarve " << countConcarve << ")" << std::endl << std::endl;
}

