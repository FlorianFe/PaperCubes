const path = require('path');
const fs = require('fs');

function parseSchematicFile(fileName, onCalculationFinished)
{
  let nbt = require('nbt');

  let data = fs.readFileSync(fileName);

  let schematic = {};

  nbt.parse(data, (error, data) =>
  {
    if (error) { throw error; }

    let width = data.value.Width.value;
    let height = data.value.Height.value;
    let length = data.value.Length.value;

    let dimension = Math.max(width, height, length);

    let blockIds = data.value.Blocks.value;
    let metaData = data.value.Data.value;

    let blocks = new Array(dimension * dimension * dimension).fill({ id: 0, metaData: 0 });

    for(let x=0; x<width; x++)
    {
      for(let y=0; y<height; y++)
      {
        for(let z=0; z<length; z++)
        {
          let blockId = blockIds[x + y * length * width + z * width];
          let blockMetaData = metaData[x + y * length * width + z * width];

          blocks[x + y * dimension + z * dimension * dimension] = { id: charToUnsignedChar(blockId), metaData: blockMetaData };
        }
      }
    }

    let schematic = { width: dimension, height: dimension, depth: dimension, blocks : blocks };

    onCalculationFinished(schematic);
  });

  return schematic;
}

function charToUnsignedChar(char)
{
  if(char > 0) return char;
  return (256 + char);
}

module.exports = parseSchematicFile;
