
let alternate = false;

function uploadTexturePack(filePath, callback)
{
  const fs = require('fs');
  const app = require('electron').app;
  const path = require("path");
  const unzip = require("unzip");

  const applicationPath = path.join('../../package.json');
  const applicationName = require(applicationPath).name;
  const appDataPath = app.getPath("appData");
  const fileStoragePath = path.join(appDataPath, applicationName);

  const texturePackPath = path.join(fileStoragePath, "texture-pack", path.basename(filePath, '.zip'));


  alternate = !alternate;

  fs.createReadStream(filePath)
  .pipe(
    unzip.Extract({ path: texturePackPath })
    .on('close', () =>
    {
      callback(texturePackPath);
    })
  );
}

module.exports = uploadTexturePack;
