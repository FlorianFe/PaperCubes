const NORTH = [0, 0, -1];
const EAST = [1, 0, 0];
const SOUTH = [0, 0, 1];
const WEST = [-1, 0, 0];
const TOP = [0, 1, 0];
const BOTTOM = [0, -1, 0];
const NULL = [0, 0, 0];

function getIndex(coords, shape)
{
  for(let i=0; i<coords.length; i++)
  {
    if(coords[i] < 0 || coords[i] >= shape[i])
    {
      return null;
    }
  }

  return (
    coords[0] +
    coords[1] * shape[0] +
    coords[2] * shape[0] * shape[1]
  );
}

function getCoordinates(index, shape)
{
  let length = shape.reduce((sum, dimension) => sum + dimension, 0);
  if(index < 0 || index >= length)
  {
    console.error("Invalid Index!");
    return null;
  }

  return [
    index % shape[0],
    parseInt(index / shape[0]) % shape[1],
    parseInt(index / (shape[0] * shape[1]))
  ];
}

function subdivideOrigami(voxelData, shape)
{
  const subdivisionBlockList = {
    44: { "id": 43, "transformationType": "slabs" },
    126: { "id": 125, "transformationType": "slabs" },
    182: { "id": 181, "transformationType": "slabs" },
    205: { "id": 204, "transformationType": "slabs" },

    53: { "id": 125, "meta": 0, "transformationType": "stairs"},
    67: { "id": 4, "meta": 0, "transformationType": "stairs"},
    108: { "id": 43, "meta": 4, "transformationType": "stairs" },
    109: { "id": 98, "meta": 0, "transformationType": "stairs" },
    114: { "id": 112, "meta": 0, "transformationType": "stairs" },
    128: { "id": 24, "meta": 0, "transformationType": "stairs" },
    134: { "id": 5, "meta": 1, "transformationType": "stairs" },
    135: { "id": 5, "meta": 2, "transformationType": "stairs" },
    136: { "id": 5, "meta": 3, "transformationType": "stairs" },
    156: { "id": 155, "meta": 0, "transformationType": "stairs" },
    163: { "id": 5, "meta": 4, "transformationType": "stairs" },
    164: { "id": 5, "meta": 5, "transformationType": "stairs" },
    180: { "id": 179, "meta": 0, "transformationType": "stairs" },
    203: { "id": 201, "meta": 0, "transformationType": "stairs" }
  };


  let result = new Array(voxelData.length * 8);
  const resultShape = shape.map(dimension => dimension * 2);

  for(let x=0; x<resultShape[0]; x++)
  for(let y=0; y<resultShape[1]; y++)
  for(let z=0; z<resultShape[2]; z++)
  {
    let originalX = parseInt(x / 2);
    let originalY = parseInt(y / 2);
    let originalZ = parseInt(z / 2);

    let originalIndex = getIndex([originalX, originalY, originalZ], shape);
    let destinationIndex = getIndex([x, y, z], resultShape);

    let original = voxelData[originalIndex];
    let textureOffset = {x: x % 2, y: y % 2, z: z % 2};
    let subdivisionBlock = subdivisionBlockList[original.type];

    if(subdivisionBlock)
    {
      if(subdivisionBlock.transformationType == "stairs")
      {
        let frontVector, rightVector, backVector, leftVector;

        if(original.metaType % 4 == 0) { frontVector = EAST; rightVector = SOUTH; backVector = WEST; leftVector = NORTH; }
        if(original.metaType % 4 == 1) { frontVector = WEST; rightVector = NORTH; backVector = EAST; leftVector = SOUTH; }
        if(original.metaType % 4 == 2) { frontVector = SOUTH; rightVector = WEST; backVector = NORTH; leftVector = EAST; }
        if(original.metaType % 4 == 3) { frontVector = NORTH; rightVector = EAST; backVector = SOUTH; leftVector = WEST; }

        let frontNeighbourIndex = getIndex(add([originalX, originalY, originalZ], frontVector), shape);
        let rightNeighbourIndex = getIndex(add([originalX, originalY, originalZ], rightVector), shape);
        let backNeighbourIndex = getIndex(add([originalX, originalY, originalZ], backVector), shape);
        let leftNeighbourIndex = getIndex(add([originalX, originalY, originalZ], leftVector), shape);

        let frontNeighbour = (frontNeighbourIndex !== null) ? voxelData[frontNeighbourIndex] : null;
        let rightNeighbour = (rightNeighbourIndex !== null) ? voxelData[rightNeighbourIndex] : null;
        let backNeighbour = (backNeighbourIndex !== null) ? voxelData[backNeighbourIndex] : null;
        let leftNeighbour = (leftNeighbourIndex !== null) ? voxelData[leftNeighbourIndex] : null;

        let frontNeighbourRotation = getRotationOfNeighbour(subdivisionBlockList, original, frontNeighbour);
        let rightNeighbourRotation = getRotationOfNeighbour(subdivisionBlockList, original, rightNeighbour);
        let backNeighbourRotation = getRotationOfNeighbour(subdivisionBlockList, original, backNeighbour);
        let leftNeighbourRotation = getRotationOfNeighbour(subdivisionBlockList, original, leftNeighbour);

        result[destinationIndex] = transformStairs(
          original, subdivisionBlock, textureOffset,
          frontNeighbourRotation,
          rightNeighbourRotation,
          backNeighbourRotation,
          leftNeighbourRotation
        );
      }
      else
      {
        result[destinationIndex] = transformSlabs(original, subdivisionBlock, textureOffset);
      }
    }
    else
    {
      result[destinationIndex] = {
        type: original.type,
        metaType: original.metaType,
        textureOffset: textureOffset
      };
    }
  }

  return result;
}

function getRotationOfNeighbour(subdivisionBlockList, original, neighbour)
{
  let originalDirection;

  if(original === null) return NULL;
  if(neighbour === null) return NULL;

  if(original.metaType % 4 == 0) originalDirection = EAST;
  if(original.metaType % 4 == 1) originalDirection = WEST;
  if(original.metaType % 4 == 2) originalDirection = SOUTH;
  if(original.metaType % 4 == 3) originalDirection = NORTH;

  let neighbourDirection = getDirectionOfNeighbour(subdivisionBlockList, original, neighbour);

  let rotation = 0;

  if(equals(originalDirection, NULL)) return null;
  if(equals(neighbourDirection, NULL)) return null;

  if(equals(originalDirection, NORTH)) rotation += 0;
  if(equals(originalDirection, EAST)) rotation += 270;
  if(equals(originalDirection, SOUTH)) rotation += 180;
  if(equals(originalDirection, WEST)) rotation += 90;

  if(equals(neighbourDirection, NORTH)) rotation += 0;
  if(equals(neighbourDirection, EAST)) rotation += 90;
  if(equals(neighbourDirection, SOUTH)) rotation += 180;
  if(equals(neighbourDirection, WEST)) rotation += 270;

  return rotation % 360;
}

function getDirectionOfNeighbour(subdivisionBlockList, original, neighbour)
{
  if(subdivisionBlockList[neighbour.type])
  {
    if(subdivisionBlockList[neighbour.type].transformationType === "stairs")
    {
      if(parseInt(original.metaType / 4) === parseInt(neighbour.metaType / 4))
      {
        if(neighbour.metaType % 4 == 0) return EAST;
        if(neighbour.metaType % 4 == 1) return WEST;
        if(neighbour.metaType % 4 == 2) return SOUTH;
        if(neighbour.metaType % 4 == 3) return NORTH;
      }
    }
  }

  return NULL;
}

function transformStairs(original, subdivisionBlock, textureOffset, frontNeighbourRotation, rightNeighbourRotation, backNeighbourRotation, leftNeighbourRotation)
{
  const AIR = {
    type: 0, // air
    metaType: 0,
    textureOffset: textureOffset
  };

  const MATERIAL = {
    type: subdivisionBlock.id,
    metaType: subdivisionBlock.meta,
    textureOffset: textureOffset
  };

  if(
    original.metaType % 8 == 0 && textureOffset.y == 0 || // East - bottom
    original.metaType % 8 == 1 && textureOffset.y == 0 || // West - bottom
    original.metaType % 8 == 2 && textureOffset.y == 0 || // South - bottom
    original.metaType % 8 == 3 && textureOffset.y == 0 || // North - bottom

    original.metaType % 8 == 4 && textureOffset.y == 1 || // East - top
    original.metaType % 8 == 5 && textureOffset.y == 1 || // West- top
    original.metaType % 8 == 6 && textureOffset.y == 1 || // South - top
    original.metaType % 8 == 7 && textureOffset.y == 1    // North - top
  )
  {
    // definitly Material
    return MATERIAL;
  }
  else
  {
    // Air or Material - depends on Neighbourhood Directions

    // Case 1 - highest Priority
    if(
      frontNeighbourRotation === 270 && rightNeighbourRotation === 0 ||
      frontNeighbourRotation === 90 && leftNeighbourRotation === 0
    )
    {
      if(original.metaType % 4 == 0 /* East */ )
      {
        if(textureOffset.x == 1) return MATERIAL;
        if(textureOffset.x == 0) return AIR;
      }

      if(original.metaType % 4 == 1 /* West */ )
      {
        if(textureOffset.x == 0) return MATERIAL;
        if(textureOffset.x == 1) return AIR;
      }

      if(original.metaType % 4 == 2 /* South */)
      {
        if(textureOffset.z == 1) return MATERIAL;
        if(textureOffset.z == 0) return AIR;
      }

      if(original.metaType % 4 == 3 /* North */)
      {
        if(textureOffset.z == 0) return MATERIAL;
        if(textureOffset.z == 1) return AIR;
      }
    }

    // Case 2.1
    if(frontNeighbourRotation === 270)
    {
      if(original.metaType % 4 == 0 /* East */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 0) ? MATERIAL : AIR;
      }

      if(original.metaType % 4 == 1 /* West */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 1) ? MATERIAL : AIR;
      }

      if(original.metaType % 4 == 2 /* South */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 1) ? MATERIAL : AIR;
      }

      if(original.metaType % 4 == 3 /* North */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 0) ? MATERIAL : AIR;
      }
    }

    // Case 2.2
    if(frontNeighbourRotation === 90)
    {
      if(original.metaType % 4 == 0 /* East */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 1) ? MATERIAL : AIR;
      }

      if(original.metaType % 4 == 1 /* West */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 0) ? MATERIAL : AIR;
      }

      if(original.metaType % 4 == 2 /* South */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 1) ? MATERIAL : AIR;
      }

      if(original.metaType % 4 == 3 /* North */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 0) ? MATERIAL : AIR;
      }
    }

    // Case 3.1
    if(backNeighbourRotation === 270)
    {
      if(original.metaType % 4 == 0 /* East */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 0) ? AIR : MATERIAL;
      }

      if(original.metaType % 4 == 1 /* West */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 1) ? AIR : MATERIAL;
      }

      if(original.metaType % 4 == 2 /* South */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 0) ? AIR : MATERIAL;
      }

      if(original.metaType % 4 == 3 /* North */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 1) ? AIR : MATERIAL;
      }
    }

    // Case 3.2
    if(backNeighbourRotation === 90)
    {
      if(original.metaType % 4 == 0 /* East */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 1) ? AIR : MATERIAL;
      }

      if(original.metaType % 4 == 1 /* West */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 0) ? AIR : MATERIAL;
      }

      if(original.metaType % 4 == 2 /* South */)
      {
        return (textureOffset.x == 0 && textureOffset.z == 0) ? AIR : MATERIAL;
      }

      if(original.metaType % 4 == 3 /* North */)
      {
        return (textureOffset.x == 1 && textureOffset.z == 1) ? AIR : MATERIAL;
      }
    }

    // Case 4
    if(original.metaType % 4 == 0 /* East */)
    {
      return (textureOffset.x == 1) ? MATERIAL : AIR;
    }

    if(original.metaType % 4 == 1 /* West */)
    {
      return (textureOffset.x == 0) ? MATERIAL : AIR;
    }

    if(original.metaType % 4 == 2 /* South */)
    {
      return (textureOffset.z == 1) ? MATERIAL : AIR;
    }

    if(original.metaType % 4 == 3 /* North */)
    {
      return (textureOffset.z == 0) ? MATERIAL : AIR;
    }

    console.error("ERROR while Stairs Transformation");
    return AIR;
  }
}

function transformSlabs(original, subdivisionBlock, textureOffset)
{
  if(
    textureOffset.y == 0 && parseInt(original.metaType / 8) == 0 || // bottom
    textureOffset.y == 1 && parseInt(original.metaType / 8) == 1    // top
  )
  {
    return {
      type: subdivisionBlock.id,
      metaType: original.metaType % 8,
      textureOffset: textureOffset
    };
  }
  else
  {
    return {
      type: 0, // air
      metaType: 0,
      textureOffset: textureOffset
    };
  }
}

function equals(a, b)
{
  if(a.length != b.length) return false;

  for(let i=0; i<a.length; i++)
  {
    if(a[i] !== b[i]) return false;
  }

  return true;
}

function add(a, b)
{
  if(!b) return a;
  if(!a) return b;

  let minLength = Math.min(a.length, b.length);

  let c = new Array(minLength)

  for(let i=0; i<minLength; i++)
  {
    c[i] = a[i] + b[i];
  }

  return c;
}

module.exports = subdivideOrigami;
