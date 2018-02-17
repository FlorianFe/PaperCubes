
class ResultPage extends Polymer.Element
{
  static get is()
  {
    return 'result-page';
  }

  static get properties()
  {
    return {
      minecraftSchematicPath: String,
      minecraftTexturePackData: String,

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

    this.$["drop-blueprint"].addEventListener("click", () =>
    {
      this.dispatchEvent(new CustomEvent('drop-blueprint', {}));
    });

    this.$["export-to-pdf-button"].addEventListener("click", () =>
    {
      this.$["origami-blueprint"].exportToPDF();
    });

    this.$["origami-blueprint"].addEventListener("start-printing", () =>
    {
      this.dispatchEvent(new CustomEvent('start-printing', {}));
    });

    this.$["origami-blueprint"].addEventListener("printing-finished", () =>
    {
      this.dispatchEvent(new CustomEvent('printing-finished', {}));
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
