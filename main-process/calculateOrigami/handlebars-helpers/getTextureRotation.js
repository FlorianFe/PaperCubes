
function getTextureRotation(type, metaType, normal, blockIdList)
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
}

module.exports = getTextureRotation;
