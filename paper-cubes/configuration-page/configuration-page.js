const {ipcRenderer} = require('electron');

class ConfigurationPage extends Polymer.Element
{
  static get is()
  {
    return 'configuration-page';
  }

  static get properties()
  {
    return {
      texturePackPath:
      {
        type: String,
        notify: true,
        value: null
      },
      schematic:
      {
        type: String,
        notify: true,
        value: null
      }
    }
  }

  constructor()
  {
    super();

    this.loading = false;
  }

  connectedCallback()
  {
    super.connectedCallback();

    this.$["continue-button"].addEventListener('click', () =>
    {
      if(!this.isNotReadyForCalculation(this.schematic, this.texturePackPath))
      {
        this.dispatchEvent(new CustomEvent('continue', {}));
      }
    });

    this.$["schematic-file-upload"].addEventListener('upload-abort', (data) =>
    {
      this.schematic = null;
    });

    this.$["schematic-file-upload"].addEventListener('upload-success', (data) =>
    {
      let schematicPath = this.$["schematic-file-upload"].files[0].path;

      ipcRenderer.send('parseSchematicFile',
      {
        schematicPath: schematicPath
      });

      ipcRenderer.on('parseSchematicFileFinished', (event, data) =>
      {
        this.schematic = data.schematic;
      });
    });

    this.$["texture-pack-upload"].addEventListener('upload-abort', () =>
    {
      this.texturePackPath = "";
    });

    this.$["texture-pack-upload"].addEventListener('upload-success', () =>
    {
      let texturePackSourcePath = this.$["texture-pack-upload"].files[0].path;

      ipcRenderer.send('uploadTexturePack',
      {
        sourcePath: texturePackSourcePath
      });

      this.loading = true;

      ipcRenderer.on('uploadTexturePackFinished', (event, data) =>
      {
        this.texturePackPath = data.texturePackPath;
        this.loading = false;
      });
    });

    window.addEventListener("error", (exception) =>
    {
      this.$["exception-toast"].text = "Oops, something went wrong";
      this.$["exception-toast"].open();
    });
  }

  not(value)
  {
    return (!value);
  }

  isNotReadyForCalculation(schematic, texturePackPath)
  {
    let condition1 = !!(schematic);
    let condition2 = !!(texturePackPath);

    return !(condition1 && condition2);
  }
}

customElements.define(ConfigurationPage.is, ConfigurationPage);
