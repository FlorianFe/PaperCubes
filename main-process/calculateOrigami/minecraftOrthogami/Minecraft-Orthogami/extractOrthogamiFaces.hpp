//
//  extractOrthogamiFaces.hpp
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 28.12.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#include <vector>
#include "Matrix.h"
#include "OrthogamiFace.h"

#ifndef extractOrthogamiFaces_hpp
#define extractOrthogamiFaces_hpp

std::vector<OrthogamiFace*> extractOrthogamiFaces(Matrix& matrix);
std::vector<OrthogamiEdge*> extractOrthogamiEdges(Matrix& matrix);

#endif /* extractOrthogamiFaces_hpp */
