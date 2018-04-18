
function getIndex(coords, shape)
{
  return (
    coords[0] +
    coords[1] * shape[0] +
    coords[2] * shape[0] * shape[1]
  );
}

function getCoordinates(index, shape)
{
  return [
    index % shape[0],
    parseInt(index / shape[0]) % shape[1],
    parseInt(index / (shape[0] * shape[1]))
  ];
}

function subdivideOrigami(voxelData, shape)
{
  const subdivisionBlockList = require('./subdivision_block_list.json');

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

    console.log("originalType", original.type, "subdivisionBlock", subdivisionBlock);

    if(subdivisionBlock)
    {
      console.log("transformationType", subdivisionBlock.transformationType);

      if(subdivisionBlock.transformationType == "stairs")
      {
        if(
          original.metaType == 0 && textureOffset.y == 1 && textureOffset.z == 1 ||
          original.metaType == 1 && textureOffset.y == 1 && textureOffset.z == 0 ||
          original.metaType == 2 && textureOffset.y == 1 && textureOffset.x == 1 ||
          original.metaType == 3 && textureOffset.y == 1 && textureOffset.x == 0 ||
          original.metaType == 4 && textureOffset.y == 0 && textureOffset.z == 1 ||
          original.metaType == 5 && textureOffset.y == 0 && textureOffset.z == 0 ||
          original.metaType == 6 && textureOffset.y == 0 && textureOffset.x == 1 ||
          original.metaType == 7 && textureOffset.y == 0 && textureOffset.x == 0
        )
        {
          result[destinationIndex] = {
            type: 0, // air
            metaType: 0,
            textureOffset: textureOffset
          };
        }
        else
        {
          result[destinationIndex] = {
            type: subdivisionBlock.id,
            metaType: subdivisionBlock.meta,
            textureOffset: textureOffset
          };
        }
      }
      else
      {
        console.log("mhm", textureOffset.y, original.metaType);
        if(
          textureOffset.y == 0 && parseInt(original.metaType / 8) == 0 || 
          textureOffset.y == 1 && parseInt(original.metaType / 8) == 1
        )
        {
          result[destinationIndex] = {
            type: subdivisionBlock.id,
            metaType: subdivisionBlock.meta,
            textureOffset: textureOffset
          };
        }
        else
        {
          result[destinationIndex] = {
            type: 0, // air
            metaType: 0,
            textureOffset: textureOffset
          };
        }
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

module.exports = subdivideOrigami;
