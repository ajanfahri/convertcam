import Line from './line.js';
import Rectangle from './rectangle.js';
import Shape from './shape.js';
import Circle from './circle.js';

const templateDiv=`
<div class="column"  >
    <button id="kare">Kare</button><button id="circle">Circle</button><button id="temizle">Temizle</button><button id="line">Line</button>
      Preview<br>
      <canvas  style="margin:0px;padding:0px;border:1px solid rgb(163, 97, 97);" id="my-canvas" 
      width="400" height="400"></canvas>
  </div>
`;

class Drawing extends HTMLElement {

  static get observedAttributes() {
      return ['adet'];
  }

  constructor() {
      super();

      // initialise the props for the component
      this.props = {
          status_play: false,
          fileName: 'bos.mp3',
          baslik: '',
          sozler: '',
          aciklama: '',
          stat_no: 0
      };
      this.month = ["Ocak", "Subat", "Mart", "Nisan", "Mayıs", "Haziran", "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık"];
      this.Link = [];
      this.count = 0;
      this.sohbetNo = 0;
      this.state = {};

      

      // add shadowDOM
      this.attachShadow({ mode: 'open' });
      this.shadowRoot.innerHTML=templateDiv;


      this.firstInit = 1;
      this.addition_constant = 0;
      this.sohbetid = 0;

      const sohbetCount = 0;
      const say = 0;
      this.shape = new Shape();
      var self=this;
      //$(this.shadowRoot.getElementById('kare')).on('click', evet =>{this.ciz();});
      this.shadowRoot.getElementById('kare').onclick = function () {
        self.ciz();
      }
      /*
      this.shadowRoot.getElementById('circle').onclick = function () {
        this.shape.addCircle(new Circle(Math.floor(Math.random() * 100), Math.floor(Math.random() * 100), Math.floor(Math.random() * 100)));
        ciz();
      }
      this.shadowRoot.getElementById('line').onclick = function () {
        this.shape.addLine(new Line(Math.floor(Math.random() * 100), Math.floor(Math.random() * 100), Math.floor(Math.random() * 100), Math.floor(Math.random() * 100)));
        ciz();
      }
      
      this.shadowRoot.getElementById('temizle').onclick = function () {
        this.shape.clearShapes();
        ciz();
      }*/
      /*
      $(document.body).on('touchmove', evet => { this.sayfaKaydir(); });
      $(window).on('scroll', evet => { this.sayfaKaydir(); });
      //$(window).on('beforeunload', evet =>{this.kapaniyor();});
      $(window).on('unload', evet => { this.kapaniyor(); });

      this.addEventListener('x-renkle', this.renkle);

      // ensure our callbacks are bound to the component context
      this.renkle = this.renkle.bind(this);
      this.ip = 0;
      this.uniq = Date.now();
      this.min = 1;

      window.setInterval(evet => { this.statgonder(); }, 30000);
          */
  }

  ciz(){
    this.shape.addRectangle(new Rectangle(Math.floor(Math.random() * 100), Math.floor(Math.random() * 100), Math.floor(Math.random() * 100), Math.floor(Math.random() * 100)));
    const canvas = this.shadowRoot.getElementById('my-canvas');
    const ctx = canvas.getContext('2d');
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.lineWidth = 1;
    ctx.restore();
    this.shape.drawShapes(ctx);
  }

  statgonder() {

      if (this.props.stat_no < 1) { this.postData(yol + 'stats/ekle.php', { sohbet_ilahi: 1, stat_no: this.uniq, ip_address: $("#gfg").val(), sohbetno: "-1", dosyaismi: "SITEYE Girdi", sure: this.formatTime(this.min) }); this.min += 30 }
      else {
          var audio = document.getElementById('audio');

          this.postData(yol + 'stats/ekle.php', { sohbet_ilahi: 1, stat_no: this.props.stat_no, ip_address: $("#gfg").val(), sohbetno: this.sohbetid, dosyaismi: this.props.fileName, sure: this.formatTime(audio.currentTime) });
      }
  }

  formatTime(seconds) {
      const h = Math.floor(seconds / 3600);
      const m = Math.floor((seconds % 3600) / 60);
      const s = parseInt(seconds % 60);
      return [h, m > 9 ? m : h ? '0' + m : m || '0', s > 9 ? s : '0' + s]
          .filter(a => a)
          .join(':')
  }

  kapaniyor() {
      var audio = document.getElementById('audio');
      if (this.sohbetid > 0 && !audio.paused)
          fetch(yol + 'stats/ekle.php', {
              method: 'post',
              headers: {
                  'Content-Type': 'application/json',
              },
              body: JSON.stringify({ sohbet_ilahi: 1, stat_no: this.props.stat_no, ip_address: $("#gfg").val(), sohbetno: this.sohbetid, dosyaismi: this.props.fileName, sure: this.formatTime(audio.currentTime) }),

              keepalive: true // this is important!
          });

  }



  sayfaKaydir() {
      var addition = ($(window).scrollTop() + window.innerHeight);
      var scrollHeight = (document.body.scrollHeight - 1);
      if (addition > scrollHeight && this.addition_constant < addition && this.bitis < this.toplamsohbet && this.firstInit == 1) {
          this.addition_constant = addition;
          this.firstInit = 0;
          this.count += 20;
          this.connectedCallback();
      }
  }

  async fetchSohbetler(url) {
      //this.loading = true;
      const response = await fetch(url);
      const json = await response.json();
      this.sohbetler = json;
      /*
      this.sohbetler = json.sonuclar;
      this.toplamsohbet = json.toplam;
      this.baslangic = json.baslangic;
      this.bitis = json.bitis;
      this.loading = false;*/

  }
  async connectedCallback() {
      // ensure any initial properties set before the component was initialised our passed
      // through our setters
      Object.keys(this.props).forEach((propName) => {
          if (this.hasOwnProperty(propName)) {
              let value = this[propName];
              delete this[propName];
              this[propName] = value;
          }
      });

      // update the shadowDOM with the intitial props/state
      //await this.fetchSohbetler(yol + `sohbetler/getirek.php?sonadet=${this.count}`);
      //await this.fetchSohbetler(yol);


      //this.render();
      this.firstInit = 1;
  }

  set status_play(value) {
      // update our props with new value
      this.props.status_play = value;

      this.set_play_pause_button(value);
      //console.log(this.props.status_play);
  }

  get status_play() {
      // return the prop
      return this.props.status_play;
  }

  set stat_no(value) {
      this.props.stat_no = value;
  }

  get stat_no() {
      return this.props.status_no;
  }

  set fileName(value) {
      // update our props with new value
      this.props.fileName = value;

      this.updateChildren();
  }

  get fileName() {
      // return the prop
      return this.props.fileName;
  }

  get adet() {
      return +this.getAttribute('adet');
  }

  set adet(value) {
      this.setAttribute('adet', value);
  }
  onUpdatefileName(event) {
      // get value from input
      const fileName = event.target.value;

      // dispatch event to update our container state
      this.dispatchEvent(new CustomEvent('x-update-filename', {
          bubbles: true,
          composed: true,
          detail: {
              fileName,
          },
      }));
  }



  updateChildren() {
      // set the props of our child components (one-way data binding)
      //this.shadowRoot.querySelector('#amount').value = this.props.amount;
      //document.getElementById('toplamBaslik').innerHTML = this.toplamsohbet + ' [' + this.baslangic + '/' + this.bitis + ']<br><br>';
      //document.getElementById('toplamBaslik').innerHTML="";
      //for (let i = 0; i < this.Link.length; i++)document.getElementById('toplamBaslik').innerHTML += '<a href=#' + this.Link[i] + '>' + this.Link[i] + '</a><br>';

  }

  render() {
      //  this.clearSohbetler();

      //for (let i = 0; i < this.sohbetler.length; i++) {
      /*    for (let i = 0; i < 1; i++) {

          i = parseInt(i);
          //const selected = this.rating ? this.rating >= i : false;
          this.createSohbet(0, i);
      }
      this.updateChildren();*/
  }

  clearSohbetler() {
      const nodes = this.element.getElementsByClassName('carf');
      if (nodes) {
          while (nodes.length > 0) {
              nodes[0].parentNode.removeChild(nodes[0]);
          }
      }
  }

  createSohbet(selected, itemId) {


      const card = document.createElement('div');
      const paragraf = document.createElement('p');
      
      const maddeler = document.createElement('ul');
      
      var keyNames = Object.keys(this.sohbetler[itemId]);
      console.log(keyNames[1]);

      Object.entries(this.sohbetler[itemId]).forEach( ([key, value]) => {
          //if(key != 398)
            var li=document.createElement('li');
            maddeler.appendChild(li);    
            li.innerHTML=li.innerHTML + key + " : " + value;
        })
        

      /*for (let i = 0; i < 5; i++) {
          var li=document.createElement('li');
          maddeler.appendChild(li);
          li.innerHTML=li.innerHTML + keyNames[i];*/
        //madde.innerHTML = keyNames[i];// + " : "+ this.sohbetler[itemId];
      /*madde.innerHTML = "Material : "+ this.sohbetler[itemId].material;maddeler.appendChild(madde);
      madde.innerHTML = "Akım : "+ this.sohbetler[itemId].amper;maddeler.appendChild(madde);
      madde.innerHTML = "Thickness : "+ this.sohbetler[itemId].thickness;maddeler.appendChild(madde);
      madde.innerHTML = "Gaz  : "+ this.sohbetler[itemId].gasType;maddeler.appendChild(madde);-*/
      //maddeler.appendChild(madde);
      //}

      //maddeler.appendChild(madde);
      card.appendChild(paragraf);
      card.appendChild(maddeler);
      this.element.appendChild(card);
      /*
      //let playbut = document.createElement('button');
     // carfplay.classList.add("carf-play");
      playbut.classList.add("play-but");
      //playbut.addEventListener('click',this.onUpdatefileName);

      //playbut.setAttribute('filename',this.sohbetler[itemId].filename);
      playbut.innerHTML = `<i class="fas fa-play"></i>`;
      playbut.setAttribute('id', 'but-' + this.sohbetler[itemId].id);
      playbut.setAttribute('data-id', this.sohbetler[itemId].id);
      playbut.setAttribute('data-filename', this.sohbetler[itemId].filename);
      playbut.setAttribute('data-baslik', this.sohbetler[itemId].baslik);
      playbut.setAttribute('data-sozler', this.sohbetler[itemId].sozler);
      playbut.setAttribute('data-aciklama', this.sohbetler[itemId].aciklama);
      playbut.addEventListener('click', value => {

          const fileName = value.currentTarget.getAttribute('data-filename');
          const baslik = value.currentTarget.getAttribute('data-baslik');
          const sozler = value.currentTarget.getAttribute('data-sozler');
          const aciklama = value.currentTarget.getAttribute('data-aciklama');
          const s_id = value.currentTarget.getAttribute('data-id');

          this.sohbetid = s_id;

          //console.log(this.sohbetler[itemId].filename);
          // dispatch event to update our container state
          //this.postData('http://localhost/test/versiyon/stats/ekle.php', { ip_address:$("#gfg").val(),sohbetno:s_id,dosyaismi:fileName,sure:"00:33" });

          this.dispatchEvent(new CustomEvent('x-update-filename', {
              bubbles: true,
              composed: true,
              detail: {
                  fileName, baslik, sozler, aciklama, s_id
              },
          }));
          this.dispatchEvent(new CustomEvent('x-renkle', {
              bubbles: true,
              composed: true,
              detail: {
                  s_id
              },
          }));


      });
      carfplay.appendChild(playbut);
      this.sohbetNo++;
      const carf = document.createElement('div');
      carf.className = "carf";

      const d = new Date(this.sohbetler[itemId].kayit_tarihi);
      let name = d.getFullYear() + '-' + this.month[d.getMonth()];
      if (!this.Link.find((str) => str === name)) this.Link.push(name);
      carf.setAttribute('id', name);
      carf.setAttribute('data-id', this.sohbetler[itemId].id);
      //carf.innerHTML=sohbetDiv;
      const baslik = document.createElement('b');
      const aciklama = document.createElement('p');
      const carfinfo = document.createElement('div');
      carfinfo.classList.add('carf-info');
      baslik.innerHTML = this.sohbetler[itemId].baslik;
      aciklama.innerHTML = this.sohbetler[itemId].aciklama;
      carfinfo.appendChild(baslik);
      carfinfo.appendChild(aciklama);
      carf.appendChild(carfplay);
      carf.appendChild(carfinfo);
      this.element.appendChild(carf);
      */
  }

  async postData(url = '', data = {}) {

      await this.posttData(url, data);


  }


  async posttData(url = '', data = {}) {
      // Default options are marked with *


      const response = await fetch(url, {
          method: 'POST', // *GET, POST, PUT, DELETE, etc.
          mode: 'cors', // no-cors, *cors, same-origin
          cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
          credentials: 'same-origin', // include, *same-origin, omit
          headers: {
              'Content-Type': 'application/json',
              // 'Content-Type': 'application/x-www-form-urlencoded',
          },
          redirect: 'follow', // manual, *follow, error
          referrerPolicy: 'no-referrer', // no-referrer, *no-referrer-when-downgrade, origin, origin-when-cross-origin, same-origin, strict-origin, strict-origin-when-cross-origin, unsafe-url
          body: JSON.stringify(data) // body data type must match "Content-Type" header
      });
  }
  renkle(event) {
      //var carf = document.getElementById(e.getAttribute('data-id').toString());
      //console.log(event.detail.sohbetid);
      let li = document.getElementsByClassName("carf")
      //console.log(li.length);
      // Loop through all list items, and hide those who don't match the search query
      for (let i = 0; i < li.length; i++) {
          if (li[i].getAttribute('data-id') == event.detail.s_id) li[i].classList.add('aktif');
          else li[i].classList.remove('aktif');
      }
  }

  set_play_pause_button(value) {
      //console.log("girdi - "+value);
      let li = document.getElementsByClassName("play-but")
      //console.log(li.length);
      // Loop through all list items, and hide those who don't match the search query
      for (let i = 0; i < li.length; i++) {
          if (li[i].getAttribute('id') == "but-" + this.sohbetid) {
              if (value) li[i].innerHTML = '<i class="fas fa-pause"></i>';
              else li[i].innerHTML = '<i class="fas fa-play"></i>';
          }
          else li[i].innerHTML = '<i class="fas fa-play"></i>';

      }
  }

}

export default Drawing;
