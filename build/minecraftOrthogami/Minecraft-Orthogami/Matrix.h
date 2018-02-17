//
//  Matrix.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 01.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

struct Block
{
    unsigned int type;
    unsigned int metaType;
};

class Matrix
{
    private:
        Block* data;
        int width;
        int height;
        int depth;
    
    public:
        Matrix(Block* data, int width, int height, int depth);
        Matrix(int width, int height, int depth);
        ~Matrix();
    
        Block get(int index);
        Block get(int x, int y, int z);
        void set(int index, Block value);
        void set(int x, int y, int z, Block value);
        int getWidth();
        int getHeight();
        int getDepth();
        int getSize();
        void expand(int amount, Block value);
};

#endif /* Matrix_h */
