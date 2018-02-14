
#include <iostream>
#include <vector>
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

std::vector<Blueprint*> orthogami(Matrix& matrix);
/*
   int main(int argc, const char * argv[])
    
    Matrix matrix = Matrix(data, 39, 30, 7);
    
    orthogami(matrix);
    
    std::cout << std::endl;
    (tests::testVector()) ? std::cout << "✔️" : std::cout << "❌";
    (tests::testEdge()) ? std::cout << "✔️" : std::cout << "❌";
    (tests::testFace()) ? std::cout << "✔️" : std::cout << "❌";
    std::cout << std::endl;
    
    return 0;
}

std::vector<Blueprint*> orthogami(Matrix& matrix)
{
    // Step 1: Prepare Matrix for Orthogami
    Matrix preparedMatrix = prepareMatrix(matrix);
    
    // Step 2: Extract Orthogami Faces from prepared Matrix
    std::vector<OrthogamiFace*> orthogamiFaceVector = extractOrthogamiFaces(preparedMatrix);
    
    // Step 3: Extract Orthogami Egdes from prepared Matrix
    std::vector<OrthogamiEdge*> orthogamiEdgeVector = extractOrthogamiEdges(preparedMatrix);
    
    // Step 4: Extract Blueprints from prepared Matrix and Orthogami Faces
    std::vector<Blueprint*> blueprintVector = extractBlueprintVectorFromOrthogamiFaceVector(orthogamiFaceVector, orthogamiEdgeVector, preparedMatrix);
    
    // Step 5: Calculate Pages
    std::vector<Page> pages = calculatePages(blueprintVector, orthogamiFaceVector, preparedMatrix, 10, 16);
    
    // Print data
    for(int i=0; i<blueprintVector.size(); i++)
    {
        Blueprint* blueprint = blueprintVector.at(i);
        
        int* data = blueprint->get2DArray();
        
        for(int j=0; j<blueprint->getWidth() * blueprint->getHeight(); j++)
        {
            std::cout << j << " " << data[j] << std::endl;
        }
    }
    
    return blueprintVector;
}
*/

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

    int pageWidth = (int)(args[0]->NumberValue());
    int pageHeight = (int)(args[1]->NumberValue());
    int tileSize = (int)(args[2]->NumberValue());
    
    Local<Array> node_matrix = Local<Array>::Cast(args[3]);
    int node_matrixLength = node_matrix->Length();
    Block* data = new Block[node_matrixLength];
    
    for(int i = 0; i < node_matrixLength; i++)
    {
        Local<Object> node_matrixElement = node_matrix->Get(i)->ToObject(isolate);
        
        unsigned int type = (unsigned int)(node_matrixElement->Get(String::NewFromUtf8(isolate, "type"))->ToInteger(isolate)->Value());
        unsigned int metaType = (unsigned int)(node_matrixElement->Get(String::NewFromUtf8(isolate, "metaType"))->ToInteger(isolate)->Value());
        
        data[i].type = type;
        data[i].metaType = metaType;
    }
    
    int matrixWidth = (int)(args[4]->NumberValue());
    int matrixHeight = (int)(args[5]->NumberValue());
    int matrixDepth = (int)(args[6]->NumberValue());
    
    int tilesPerRow = pageWidth / tileSize;
    int rowsPerPage = pageHeight / tileSize;
    
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
 
         // Step 5: Calculate Pages
         std::vector<Page> pages = calculatePages(blueprintVector, orthogamiFaceVector, preparedMatrix, tilesPerRow, rowsPerPage);
 
         // blueprint: { ... }
         Local<Object> node_blueprint = Object::New(isolate);
 
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
                node_tile->Set(String::NewFromUtf8(isolate, "type"), Integer::New(isolate, tile.type));
                node_tile->Set(String::NewFromUtf8(isolate, "metaType"), Integer::New(isolate, tile.metaType));
                
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
