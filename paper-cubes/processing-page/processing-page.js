
class ProcessingPage extends Polymer.Element
{
  static get is()
  {
    return 'processing-page';
  }

  static get properties()
  {
    return {
      label:
      {
        type: String,
        value: "loading"
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
  }
}

customElements.define(ProcessingPage.is, ProcessingPage);
