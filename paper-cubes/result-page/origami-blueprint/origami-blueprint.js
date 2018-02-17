const fs = require("fs");
const path = require("path");

class OrigamiBlueprint extends Polymer.Element
{
  static get is()
  {
    return 'origami-blueprint';
  }

  static get properties()
  {
    return {
      minecraftSchematicPath: String,
      texturePackUploadPath: String,
      texturePackPath: String
    }
  }

  connectedCallback()
  {
    super.connectedCallback();
  }

  exportToPDF()
  {
    const {dialog} = require('electron').remote;

    dialog.showSaveDialog(undefined,
    {
      title: "Export PDF",
      defaultPath: '~/origami.pdf'
    },
    (filename) =>
    {
      if(filename != undefined)
      {
        this.dispatchEvent(new CustomEvent('start-printing', {}));

        let browserWindow = require('electron').remote.getCurrentWindow();

        browserWindow.webContents.printToPDF({ pageSize: "A4" }, (err, data) =>
        {
          fs.writeFile(filename, data, (err) =>
          {
            if(err)
            {
              throw new Error("Printing PDF failed")
            }
            else
            {
              console.log("Printing success!");
            }

            this.dispatchEvent(new CustomEvent('printing-finished', {}));
          });
        });
      }
    });
  }

  calculate()
  {
    const fs = require("fs");
    const unzip = require("unzip");
    const path = require('path');
    const app = require('electron').remote.app;
    const applicationName = require(__dirname + '/package.json').name;
    const appDataPath = app.getPath("appData");
    const fileStoragePath = path.join(appDataPath, applicationName);

    const texturePackPath = path.join(fileStoragePath, "texture-pack");
    this.texturePackPath = texturePackPath;

    console.log(this.texturePackUploadPath);

    fs.createReadStream(this.texturePackUploadPath)
    .pipe(
      unzip.Extract({ path: texturePackPath })
      .on('close', () =>
      {
        const {ipcRenderer} = require('electron');

        console.log("EZ; ", this.schematicData, this.texturePackPath);

        ipcRenderer.send('startSchematicToOrigamiCalculation',
        {
          minecraftSchematicPath: this.minecraftSchematicPath,
          texturePackPath: this.texturePackPath
        });

        ipcRenderer.on('schematicToOrigamiCalulationFinished', (event, data) =>
        {
          let html = data.html;

          this.$["result-container"].innerHTML = html;
          document.getElementById("printing-container").innerHTML = html;

          this.dispatchEvent(new CustomEvent('calculation-finished', {}));
        });
      })
    );
  }

  not(value)
  {
    return (!value);
  }
}

customElements.define(OrigamiBlueprint.is, OrigamiBlueprint);
