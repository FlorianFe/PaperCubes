const path = require('path');
const fs = require('fs');

const getTextureRotation = require('./handlebars-helpers/getTextureRotation'); // @TODO: Antipattern!

function calculateOrigami(data, onCalculationFinished)
{
  const m2o = require('./minecraftOrthogami/binding');
  const subdivideOrigami = require('./subdivideOrigami/subdivideOrigami');
  const blockIdList = require('./block_id_list.json');
  const Handlebars = require('handlebars');

  registerHandlebarsHelper(Handlebars, blockIdList);

  const blockTexturePath = path.join(data.texturePackPath, "assets/minecraft/textures/blocks");

  fs.readdir(blockTexturePath, (err, files) =>
  {
    let textures = files.map((file) =>
    {
      return file.split(".")[0];
    });

    fs.readFile(path.join(__dirname, 'template.hbs'), "utf8", (err, source) =>
    {
      if (err) throw err;

      let schema = data.schematic;

      let dimension = Math.max(schema.width, schema.height, schema.depth);
      let voxelData = Array(dimension * dimension * dimension).fill({ type: 0, metaType: 0 });

      for(let x=0; x<schema.width; x++)
      {
        for(let y=0; y<schema.height; y++)
        {
          for(let z=0; z<schema.depth; z++)
          {
            let block = schema.blocks[x + y * schema.depth * schema.width + z * schema.depth];

            voxelData[x + dimension * z + dimension * dimension * y] = { type: charToUnsignedChar(block.id), metaType: block.metaData };
          }
        }
      }

      let subdividedVoxelData = subdivideOrigami(voxelData, [dimension, dimension, dimension]);

      for(let i=0; i < dimension * dimension * dimension * 8; i++)
      {
        let source = subdividedVoxelData[i];

        if(blockIdList[source.type] == undefined)
        {
          subdividedVoxelData[i] = { type: 0, metaType: 0, textureOffset: source.textureOffset}; // Air
        }
      }

      let context = m2o.orthogami(
        subdividedVoxelData,
        dimension * 2, dimension * 2, dimension * 2
      );

      context.texturePath = path.join(data.texturePackPath, "assets/minecraft/textures/blocks");
      context.textures = textures;

      let template = Handlebars.compile(source);
      let html = template(context);

      onCalculationFinished(html);
    });
  });
}

function registerHandlebarsHelper(Handlebars, blockIdList)
{
  Handlebars.registerHelper('add', (a, b) =>
  {
    return new Handlebars.SafeString(parseFloat(a) + parseFloat(b));
  });

  Handlebars.registerHelper('mul', (a, b) =>
  {
    return new Handlebars.SafeString(parseFloat(a) * parseFloat(b));
  });

  Handlebars.registerHelper('div', (a, b) =>
  {
    return new Handlebars.SafeString(parseFloat(a) / parseFloat(b));
  });

  Handlebars.registerHelper('rotation', (a) =>
  {
    if(a.x == 0 && a.y == 1) return new Handlebars.SafeString("0");
    if(a.x == -1 && a.y == 0) return new Handlebars.SafeString("90");
    if(a.x == 0 && a.y == -1) return new Handlebars.SafeString("180");
    if(a.x == 1 && a.y == 0) return new Handlebars.SafeString("270");

    return new Handlebars.SafeString("0");
  });

  Handlebars.registerHelper('texture', (type, metaType, normal, textureOffset) =>
  {
    if(!blockIdList[type])
    {
      console.warn("Block with id " + type + " not supported!");
      return Handlebars.SafeString("");
    }

    let textureObject = (blockIdList[type][metaType]) ? blockIdList[type][metaType] : blockIdList[type]["*"];
    let texture;

    if(typeof textureObject === 'object')
    {
      let orientation = "none";

      if(normal.z == -1) orientation = "north";
      if(normal.x == 1) orientation = "east";
      if(normal.z == 1) orientation = "south";
      if(normal.x == -1) orientation = "west";
      if(normal.y == 1) orientation = "top";
      if(normal.y == -1) orientation = "bottom";

      texture = (textureObject[orientation]) ? textureObject[orientation] : textureObject["*"];
    }
    else
    {
      texture = textureObject;
    }

    let textureName = texture.split(":")[0];

    let a = 0;
    let b = 0;
    let c = 0;

    if(normal.x > 0) { a = 0; b = textureOffset.z; c = textureOffset.y }
    if(normal.z > 0) { a = 1; b = textureOffset.x; c = textureOffset.y }
    if(normal.y > 0) { a = 1; b = textureOffset.x; c = textureOffset.z + 1 }

    if(normal.x < 0) { a = 1; b = textureOffset.z; c = textureOffset.y }
    if(normal.z < 0) { a = 0; b = textureOffset.x; c = textureOffset.y }
    if(normal.y < 0) { a = 1; b = textureOffset.x; c = textureOffset.z }


    let texture2dOffset = [(a + b) % 2, c % 2];

    let textureRotation = getTextureRotation(type, metaType, normal, blockIdList);
    let textureRotationSteps = parseInt(textureRotation / 90);

    let rotationVectors = [
      [0, 0],
      [0, 1],
      [1, 1],
      [1, 0]
    ];

    let rotationBase = 0;

    if(texture2dOffset[0] === rotationVectors[0][0] && texture2dOffset[1] === rotationVectors[0][1]) rotationBase = 0;
    if(texture2dOffset[0] === rotationVectors[1][0] && texture2dOffset[1] === rotationVectors[1][1]) rotationBase = 1;
    if(texture2dOffset[0] === rotationVectors[2][0] && texture2dOffset[1] === rotationVectors[2][1]) rotationBase = 2;
    if(texture2dOffset[0] === rotationVectors[3][0] && texture2dOffset[1] === rotationVectors[3][1]) rotationBase = 3;

    let rotationResult = rotationVectors[(rotationBase - textureRotationSteps + 4) % 4];

    textureName += "_" + rotationResult[0] + "_" + rotationResult[1];

    return new Handlebars.SafeString(textureName);
  });

  Handlebars.registerHelper('texturerotation', (type, metaType, normal) =>
  {
    return getTextureRotation(type, metaType, normal, blockIdList);
  });
}

function charToUnsignedChar(char)
{
  if(char > 0) return char;
  return (256 + char);
}

module.exports = calculateOrigami;
