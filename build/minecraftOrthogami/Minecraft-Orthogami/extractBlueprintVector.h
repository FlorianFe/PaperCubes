//
//  extractBlueprintVector.h
//  Minecraft-Orthogami
//
//  Created by Florian Fechner on 04.10.17.
//  Copyright © 2017 Florian Fechner. All rights reserved.
//

#ifndef extractBlueprintVector_h
#define extractBlueprintVector_h

#include <vector>
#include "OrthogamiFace.h"
#include "OrthogamiEdge.h"
#include "Blueprint.h"
#include "Matrix.h"

std::vector<Blueprint*> extractBlueprintVectorFromOrthogamiFaceVector(std::vector<OrthogamiFace*>& orthogamiFaceVector, std::vector<OrthogamiEdge*>& orthogamiEdgeVector, Matrix& matrix);

#endif /* extractBlueprintVector_h */
