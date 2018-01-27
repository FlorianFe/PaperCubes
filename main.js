const electron = require('electron');

const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const Menu = electron.Menu;
const ipcMain = electron.ipcMain;

const path = require('path');
const url = require('url');
const fs = require('fs');

let browserWindow = null;

console.log(process.versions);

function createWindow()
{
  browserWindow = new BrowserWindow(
  {
    width: 800,
    height: 545,
    backgroundColor: '#fff'
  });

  browserWindow.loadURL(path.join('file://', __dirname, 'index.html'), { "extraHeaders" : "pragma: no-cache\n" });

  browserWindow.on('closed', () =>
  {
    browserWindow = null;
  });

  const template =
  [
    {
      label: 'Edit',
      submenu: [
        {role: 'undo'},
        {role: 'redo'},
        {type: 'separator'},
        {role: 'cut'},
        {role: 'copy'},
        {role: 'paste'},
        {role: 'pasteandmatchstyle'},
        {role: 'delete'},
        {role: 'selectall'}
      ]
    },
    {
      label: 'View',
      submenu: [
        {role: 'reload'},
        {role: 'forcereload'},
        {role: 'toggledevtools'},
        {type: 'separator'},
        {role: 'resetzoom'},
        {role: 'zoomin'},
        {role: 'zoomout'},
        {type: 'separator'},
        {role: 'togglefullscreen'}
      ]
    },
    {
      role: 'window',
      submenu: [
        {role: 'minimize'},
        {role: 'close'}
      ]
    },
    {
      role: 'help',
      submenu: [
        {
          label: 'Learn More',
          click () { require('electron').shell.openExternal('https://github.com/FlorianFe') }
        }
      ]
    }
  ]

  if (process.platform === 'darwin') {
    template.unshift({
      label: app.getName(),
      submenu: [
        {role: 'about'},
        {type: 'separator'},
        {role: 'services', submenu: []},
        {type: 'separator'},
        {role: 'hide'},
        {role: 'hideothers'},
        {role: 'unhide'},
        {type: 'separator'},
        {role: 'quit'}
      ]
    })

    // Edit menu
    template[1].submenu.push(
      {type: 'separator'},
      {
        label: 'Speech',
        submenu: [
          {role: 'startspeaking'},
          {role: 'stopspeaking'}
        ]
      }
    )

    // Window menu
    template[3].submenu = [
      {role: 'close'},
      {role: 'minimize'},
      {role: 'zoom'},
      {type: 'separator'},
      {role: 'front'}
    ]
  }

  let menu = Menu.buildFromTemplate(template);
  Menu.setApplicationMenu(menu);
}

app.on('ready', () =>
{
  createWindow();

  ipcMain.on("startSchematicToOrigamiCalculation", (event, data) =>
  {
    const minecraft = require('./main-process/schematicToOrigami/m2o/binding');
    const blockIdList = require('./main-process/schematicToOrigami/block_id_list.json');
    const Handlebars = require('handlebars');
    const Schematic = require('mc-schematic')('1.9');

    let textures = [];

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
      return new Handlebars.SafeString(parseInt(parseInt(a) / parseInt(b)));
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
      let texture = blockIdList[type][metaType];

      if(typeof texture === 'object')
      {
        let orientation = "side";

        if(normal.y == 1)
        {
          orientation = "top";
        }

        if(normal.y == -1)
        {
          orientation = "bottom";
        }

        texture = texture[orientation];
      }

      return new Handlebars.SafeString(texture);
    });

    const blockTexturePath = path.join(data.texturePackPath, "assets/minecraft/textures/blocks");

    fs.readdir(blockTexturePath, (err, files) =>
    {
      let textures = files.map((file) =>
      {
        return file.split(".")[0];
      });

      fs.readFile(path.join(__dirname, 'main-process/schematicToOrigami/template.hbs'), "utf8", (err, source) =>
      {
        if (err) throw err;

        Schematic.parse(data.schematicData, function (error, schema)
        {
          if (error) throw error;

          let dimension = Math.max(schema.width, schema.height, schema.length);
          let voxelData = Array(dimension * dimension * dimension).fill({type: 0, metaType: 0});

          for(let x=0; x<schema.width; x++)
          {
            for(let y=0; y<schema.height; y++)
            {
              for(let z=0; z<schema.length; z++)
              {
                let block = schema.getBlock(x, y, z);

                if(blockIdList[block.type] != undefined)
                {
                  console.log(block);
                  voxelData[x + dimension * y + dimension * dimension * z] = {type: block.type, metaType: block.metadata};
                }
              }
            }
          }

          console.log(voxelData, voxelData.length, dimension);

          let context = minecraft.orthogami(
            data.boundsX, data.boundsY, data.scale,
            voxelData, dimension, dimension, dimension
          );

          context.strokeWidth = data.strokeWidth;
          context.strokeColor = data.strokeColor;
          context.tabColor = data.tabColor;
          context.pageWidth = data.boundsX;
          context.pageHeight = data.boundsY;
          context.size = data.scale;
          context.texturePath = path.join(data.texturePackPath, "assets/minecraft/textures/blocks");
          context.textures = textures;
          let template = Handlebars.compile(source);
          let html = template(context);

          event.sender.send("schematicToOrigamiCalulationFinished", { html: html });
        });
      });
    });
  });
});

app.on('activate', function ()
{
  if (browserWindow === null)
  {
    createWindow()
  }
});

app.on('window-all-closed', () =>
{
  if(process.platform !== 'darwin')
  {
    app.quit()
  }
});
