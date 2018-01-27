
class ResultPage extends Polymer.Element
{
  static get is()
  {
    return 'result-page';
  }

  static get properties()
  {
    return {
      pageWidth:
      {
        type: Number
      },
      pageHeight:
      {
        type: Number
      },
      tileSize:
      {
        type: Number
      },
      lineWidth:
      {
        type: Number
      },

      minecraftSchematicData: String,
      minecraftTexturePackData: String,

      tabColor:
      {
        type: String
      },
      strokeColor:
      {
        type: String
      },
      concaveLineColor:
      {
        type: String
      },
      convexLineColor:
      {
        type: String
      },
      texturePackUploadPath:
      {
        type: String
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

    this.$["origami-blueprint"].addEventListener("drop-blueprint", () =>
    {
      this.dispatchEvent(new CustomEvent('drop-blueprint', {}));
    });

    this.$["origami-blueprint"].addEventListener('calculation-finished', () =>
    {
      this.dispatchEvent(new CustomEvent('calculation-finished', {}));
    });
  }

  calculate()
  {
    this.$["origami-blueprint"].calculate();
  }
}

customElements.define(ResultPage.is, ResultPage);
