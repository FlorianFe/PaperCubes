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
      schematic:
      {
        type: Object
      },
      texturePackPath:
      {
        type: String
      }
    }
  }

  connectedCallback()
  {
    super.connectedCallback();

    const {ipcRenderer} = require('electron');

    ipcRenderer.on('schematicToOrigamiCalulationFinished', (event, data) =>
    {
      let html = data.html;

      this.$["result-container"].innerHTML = html;
      document.getElementById("printing-container").innerHTML = html;

      this.dispatchEvent(new CustomEvent('calculation-finished', {}));
    });
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
    const {ipcRenderer} = require('electron');

    ipcRenderer.send('startSchematicToOrigamiCalculation',
    {
      schematic: this.schematic,
      texturePackPath: this.texturePackPath
    });
  }

  not(value)
  {
    return (!value);
  }
}

customElements.define(OrigamiBlueprint.is, OrigamiBlueprint);
