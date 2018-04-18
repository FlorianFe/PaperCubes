
#include <iostream>
#include <vector>
#include <math.h>
#include "Matrix.h"
#include "Face.h"
#include "Edge.h"
#include "OrthogamiEdge.h"
#include "OrthogamiFace.h"
#include "OrthogamiFaceGroup.h"
#include "Blueprint.h"
#include "prepareMatrix.h"
#include "extractBlueprintVector.h"
#include "extractOrthogamiFaces.hpp"
#include "calculatePages.hpp"

unsigned int getWidestBlueprintWidth(std::vector<Blueprint*> blueprintVector)
{
    unsigned int maxWidth = 1;
    
    for(std::vector<Blueprint*>::iterator iterator = blueprintVector.begin(); iterator != blueprintVector.end(); ++iterator)
    {
        unsigned int width = (*iterator)->getWidth();
        
        if(width > maxWidth) maxWidth = width;
    }
    
    return maxWidth;
}

unsigned int getHighestBlueprintHeight(std::vector<Blueprint*> blueprintVector)
{
    unsigned int maxHeight = 1;
    
    for(std::vector<Blueprint*>::iterator iterator = blueprintVector.begin(); iterator != blueprintVector.end(); ++iterator)
    {
        unsigned int height = (*iterator)->getHeight();
        
        if(height > maxHeight) maxHeight = height;
    }
    
    return maxHeight;
}

unsigned int getTilesPerRow(std::vector<Blueprint*> blueprintVector)
{
    unsigned int widestBlueprintWidth = getWidestBlueprintWidth(blueprintVector);
    unsigned int highestBlueprintHeight = getHighestBlueprintHeight(blueprintVector);
    
    unsigned int tilesPerRow;
    
    if(sqrt(2) * widestBlueprintWidth < highestBlueprintHeight)
    {
        tilesPerRow =  floor(highestBlueprintHeight / sqrt(2)) + 1;
    }
    else
    {
        tilesPerRow = widestBlueprintWidth;
    }
    
    return tilesPerRow;
}

unsigned int getRowsPerPage(std::vector<Blueprint*> blueprintVector)
{
    unsigned int widestBlueprintWidth = getWidestBlueprintWidth(blueprintVector);
    unsigned int highestBlueprintHeight = getHighestBlueprintHeight(blueprintVector);
    
    unsigned int rowsPerPage;
    
    if(sqrt(2) * widestBlueprintWidth < highestBlueprintHeight)
    {
        rowsPerPage = highestBlueprintHeight;
    }
    else
    {
        rowsPerPage = floor(widestBlueprintWidth * sqrt(2));
    }
    
    return rowsPerPage + 1;
}

// === NODE JS === //

#include <node.h>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Array;

using namespace v8;

// (pageWidth, pageHeight, tileSize, matrixData, matrixWidth, matrixHeight, matrixDepth)
void orthogami(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    
    Local<Array> node_matrix = Local<Array>::Cast(args[0]);
    int node_matrixLength = node_matrix->Length();
    Block* data = new Block[node_matrixLength];
    
    for(int i = 0; i < node_matrixLength; i++)
    {
        Local<Object> node_matrixElement = node_matrix->Get(i)->ToObject(isolate);
        Local<Object> node_textureOffset = node_matrixElement->Get(String::NewFromUtf8(isolate, "textureOffset"))->ToObject(isolate);
        
        unsigned int type = (unsigned int)(node_matrixElement->Get(String::NewFromUtf8(isolate, "type"))->ToInteger(isolate)->Value());
        unsigned int metaType = (unsigned int)(node_matrixElement->Get(String::NewFromUtf8(isolate, "metaType"))->ToInteger(isolate)->Value());
        
        unsigned int textureOffsetX = (unsigned int)(node_textureOffset->Get(String::NewFromUtf8(isolate, "x"))->ToInteger(isolate)->Value());
        unsigned int textureOffsetY = (unsigned int)(node_textureOffset->Get(String::NewFromUtf8(isolate, "y"))->ToInteger(isolate)->Value());
        unsigned int textureOffsetZ = (unsigned int)(node_textureOffset->Get(String::NewFromUtf8(isolate, "z"))->ToInteger(isolate)->Value());
        
        data[i].type = type;
        data[i].metaType = metaType;
        data[i].textureOffset.x = textureOffsetX;
        data[i].textureOffset.y = textureOffsetY;
        data[i].textureOffset.z = textureOffsetZ;
    }
    
    int matrixWidth = (int)(args[1]->NumberValue());
    int matrixHeight = (int)(args[2]->NumberValue());
    int matrixDepth = (int)(args[3]->NumberValue());
    
    Matrix matrix = Matrix(data, matrixWidth, matrixHeight, matrixDepth);

    try
    {
         // Step 1: Prepare Matrix for Orthogami
         Matrix preparedMatrix = prepareMatrix(matrix);
 
         // Step 2: Extract Orthogami Faces from prepared Matrix
         std::vector<OrthogamiFace*> orthogamiFaceVector = extractOrthogamiFaces(preparedMatrix);
 
         // Step 3: Extract Orthogami Egdes from prepared Matrix
         std::vector<OrthogamiEdge*> orthogamiEdgeVector = extractOrthogamiEdges(preparedMatrix);
 
         // Step 4: Extract Blueprints from prepared Matrix and Orthogami Faces
         std::vector<Blueprint*> blueprintVector = extractBlueprintVectorFromOrthogamiFaceVector(orthogamiFaceVector, orthogamiEdgeVector, preparedMatrix);
 
        // Step 4.2: calculate tilesPerRow and rowsPerPage
        unsigned int tilesPerRow = getTilesPerRow(blueprintVector);
        unsigned int rowsPerPage = getRowsPerPage(blueprintVector);
        
         // Step 5: Calculate Pages
         std::vector<Page> pages = calculatePages(blueprintVector, orthogamiFaceVector, orthogamiEdgeVector, preparedMatrix, tilesPerRow, rowsPerPage);
 
         // blueprint: { ... }
         Local<Object> node_blueprint = Object::New(isolate);
        
        node_blueprint->Set(String::NewFromUtf8(isolate, "width"), Integer::New(isolate, tilesPerRow));
        node_blueprint->Set(String::NewFromUtf8(isolate, "height"), Integer::New(isolate, rowsPerPage));
 
        // pages: [ ... ]
        Local<Array> node_pages = Array::New(isolate, pages.size());
        
        for(unsigned int j=0; j<pages.size(); j++)
        {
            // tiles: [ ... ]
            std::vector<Tile> tiles = pages.at(j).tiles;
            Local<Array> node_tiles = Array::New(isolate, tiles.size());
            
            for(unsigned int i=0; i<tiles.size(); i++)
            {
                Tile tile = tiles.at(i);
                
                // Tile: { x: Number, y: Number, type: Number, normal: { x: Number, y: Number, z: Number } }
                Local<Object> node_tile = Object::New(isolate);
                
                node_tile->Set(String::NewFromUtf8(isolate, "x"), Integer::New(isolate, tile.x));
                node_tile->Set(String::NewFromUtf8(isolate, "y"), Integer::New(isolate, tile.y));
                node_tile->Set(String::NewFromUtf8(isolate, "type"), Integer::New(isolate, tile.block.type));
                node_tile->Set(String::NewFromUtf8(isolate, "metaType"), Integer::New(isolate, tile.block.metaType));
                
                Local<Object> node_textureOffset = Object::New(isolate);
                
                node_textureOffset->Set(String::NewFromUtf8(isolate, "x"), Integer::New(isolate, tile.block.textureOffset.x));
                node_textureOffset->Set(String::NewFromUtf8(isolate, "y"), Integer::New(isolate, tile.block.textureOffset.y));
                node_textureOffset->Set(String::NewFromUtf8(isolate, "z"), Integer::New(isolate, tile.block.textureOffset.z));
                
                node_tile->Set(String::NewFromUtf8(isolate, "textureOffset"), node_textureOffset);
                
                Local<Object> node_normal = Object::New(isolate);
                node_normal->Set(String::NewFromUtf8(isolate, "x"), Integer::New(isolate, tile.normal.getX()));
                node_normal->Set(String::NewFromUtf8(isolate, "y"), Integer::New(isolate, tile.normal.getY()));
                node_normal->Set(String::NewFromUtf8(isolate, "z"), Integer::New(isolate, tile.normal.getZ()));
                
                node_tile->Set(String::NewFromUtf8(isolate, "normal"), node_normal);
                
                node_tiles->Set(i, node_tile);
            }
            
            // links: [ ... ]
            std::vector<Link> links = pages.at(j).links;
            Local<Array> node_links = Array::New(isolate, links.size());
            
            for(unsigned int i=0; i<links.size(); i++)
            {
                Link link = links.at(i);
                
                // Link: { index: Number, x: Number, y: Number, orientation: { x: Number, y: Number } }
                Local<Object> node_link = Object::New(isolate);
                
                node_link->Set(String::NewFromUtf8(isolate, "index"), Integer::New(isolate, link.index));
                node_link->Set(String::NewFromUtf8(isolate, "x"), Integer::New(isolate, link.x));
                node_link->Set(String::NewFromUtf8(isolate, "y"), Integer::New(isolate, link.y));
                node_link->Set(String::NewFromUtf8(isolate, "opened"), Boolean::New(isolate, link.opened));
                node_link->Set(String::NewFromUtf8(isolate, "concarve"), Boolean::New(isolate, link.concarve));
                
                Local<Object> node_orientation = Object::New(isolate);
                node_orientation->Set(String::NewFromUtf8(isolate, "x"), Integer::New(isolate, link.orientationX));
                node_orientation->Set(String::NewFromUtf8(isolate, "y"), Integer::New(isolate, link.orientationY));
                
                node_link->Set(String::NewFromUtf8(isolate, "orientation"), node_orientation);
                
                node_links->Set(i, node_link);
            }
            
            Local<Object> node_page = Object::New(isolate);
            
            node_page->Set(String::NewFromUtf8(isolate, "tiles"), node_tiles);
            node_page->Set(String::NewFromUtf8(isolate, "links"), node_links);
            
            node_pages->Set(j, node_page);
        }
        
        node_blueprint->Set(String::NewFromUtf8(isolate, "pages"), node_pages);
        
        args.GetReturnValue().Set(node_blueprint);
        
        delete[] data;
    }
    catch(const char* message)
    {
         std::cout << message << std::endl;
    }
    catch(...)
    {
        std::cout << "Something else happend" << std::endl;
    }
}

void initialize(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "orthogami", orthogami);
}

NODE_MODULE(minecraft, initialize);
