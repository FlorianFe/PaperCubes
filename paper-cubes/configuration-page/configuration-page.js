
class ConfigurationPage extends Polymer.Element
{
  static get is()
  {
    return 'configuration-page';
  }

  static get properties()
  {
    return {
      texturePackUploadPath:
      {
        type: String,
        notify: true
      },
      minecraftSchematicPath:
      {
        type: String,
        notify: true
      },
      condition1:
      {
        type: Boolean,
        value: false
      },
      condition2:
      {
        type: Boolean,
        value: false
      }
    }
  }

  constructor()
  {
    super();
  }

  connectedCallback()
  {
    super.connectedCallback();

    this.$["continue-button"].addEventListener('click', () =>
    {
      if(!this.isNotReadyForCalculation(this.condition1, this.condition2))
      {
        this.dispatchEvent(new CustomEvent('continue', {}));
      }
    });

    this.$["minecraft-schematic-file-upload"].addEventListener('upload-success', (data) =>
    {
      this.minecraftSchematicPath = this.$["minecraft-schematic-file-upload"].files[0].path;
      this.condition1 = true;
    });

    this.$["minecraft-texture-pack-upload"].addEventListener('upload-success', () =>
    {
      this.texturePackUploadPath = this.$["minecraft-texture-pack-upload"].files[0].path;
      this.condition2 = true;
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

  isNotReadyForCalculation(condition1, condition2)
  {
    return !(condition1 && condition2);
  }
}

customElements.define(ConfigurationPage.is, ConfigurationPage);
