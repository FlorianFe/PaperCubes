const path = require('path');
const fs = require('fs');

function calculateOrigami(data, onCalculationFinished)
{
  const m2o = require('./minecraftOrthogami/binding');
  const blockIdList = require('./block_id_list.json');
  const Handlebars = require('handlebars');

  registerHandlebarsHelper(Handlebars, blockIdList);

  const blockTexturePath = path.join(data.texturePackPath, "assets/minecraft/textures/blocks");

  console.log("DATA:", data);

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

      console.log(schema.width, schema.height, schema.depth);

      let dimension = Math.max(schema.width, schema.height, schema.depth);
      let voxelData = Array(dimension * dimension * dimension).fill({type: 0, metaType: 0});

      for(let x=0; x<schema.width; x++)
      {
        for(let y=0; y<schema.height; y++)
        {
          for(let z=0; z<schema.depth; z++)
          {
            let block = schema.blocks[x + y * schema.depth * schema.width + z * schema.depth];

            if(blockIdList[charToUnsignedChar(block.id)] != undefined)
            {
              voxelData[x + dimension * y + dimension * dimension * z] = { type: charToUnsignedChar(block.id), metaType: block.metaData };
            }
          }
        }
      }

      let context = m2o.orthogami(
        voxelData, dimension, dimension, dimension
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

  Handlebars.registerHelper('texture', (type, metaType, normal) =>
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

    return new Handlebars.SafeString(textureName);
  });

  Handlebars.registerHelper('texturerotation', (type, metaType, normal) =>
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

    let textureArray = texture.split(":");

    return (textureArray.length <= 1) ? 0 : textureArray[1];
  });
}

function charToUnsignedChar(char)
{
  if(char > 0) return char;
  return (256 + char);
}

module.exports = calculateOrigami;
