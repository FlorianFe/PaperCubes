const electron = require('electron');

const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const Menu = electron.Menu;
const ipcMain = electron.ipcMain;

const path = require('path');
const url = require('url');
const fs = require('fs');
const calculateOrigami = require('./main-process/calculateOrigami/calculateOrigami');

let browserWindow = null;

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
    /*{
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
    },*/
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
          click ()
          {
            let shell = require('electron').shell;
            shell.openExternal('https://github.com/FlorianFe/PaperCubes');
          }
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
    /*
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
    */
  }

  let menu = Menu.buildFromTemplate(template);
  Menu.setApplicationMenu(menu);
}

app.on('ready', () =>
{
  createWindow();

  ipcMain.on("startSchematicToOrigamiCalculation", (event, data) =>
  {
    calculateOrigami(data, (html) =>
    {
      event.sender.send("schematicToOrigamiCalulationFinished", { html: html });
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
