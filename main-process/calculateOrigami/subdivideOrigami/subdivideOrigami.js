
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

    console.log("o", originalIndex, "d", destinationIndex);

    let original = voxelData[originalIndex];
    let textureOffsets = [x % 2, y % 2, z % 2];

    result[destinationIndex] = {
      type: original.type,
      metaType: original.metaType,
      textureOffsets: textureOffsets
    };
  }

  return result;
}

module.exports = subdivideOrigami;
