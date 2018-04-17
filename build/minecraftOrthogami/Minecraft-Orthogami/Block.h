//
//  Block.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 17.04.18.
//  Copyright © 2018 Florian Fechner. All rights reserved.
//

#ifndef Block_h
#define Block_h

struct TextureOffset
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
}

struct Block
{
    unsigned int type;
    unsigned int metaType;
    TextureOffset textureOffset;
};



#endif /* Block_h */
