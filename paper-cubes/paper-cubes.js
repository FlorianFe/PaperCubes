
class PaperCubes extends Polymer.Element
{
  static get is()
  {
    return 'paper-cubes';
  }

  static get properties()
  {
    return {
      selectedPage:
      {
        type: Number,
        value: 0
      }
    }
  }

  connectedCallback()
  {
    super.connectedCallback();

    this.$["configuration-page"].addEventListener('continue', () =>
    {
      this.selectedPage = 1;
      this.$["result-page"].calculate();
    });

    this.$["result-page"].addEventListener('calculation-finished', () =>
    {
      this.selectedPage = 2;
    });

    this.$["result-page"].addEventListener("drop-blueprint", () =>
    {
      this.selectedPage = 0;
    });
  }
}

customElements.define(PaperCubes.is, PaperCubes);
