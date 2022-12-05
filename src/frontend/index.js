import Line from './objects/line.js';
import Rectangle from './objects/rectangle.js';
import Shape from './objects/shape.js';
import Circle from './objects/circle.js';

//let Cizgiler = new Array();
let shape= new Shape();

function updateSize() {
  let nBytes = 0,
  oFiles = this.files,
  nFiles = oFiles.length;
  for (let nFileId = 0; nFileId < nFiles; nFileId++) nBytes += oFiles[nFileId].size;
  let sOutput = nBytes + " bytes";
  const aMultiples = ["KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"];
  document.getElementById("orjinalFile").innerHTML = oFiles[0].name + " "+nFiles + " " + sOutput;
  document.getElementById('convertedFileText').innerHTML="";
  var fr=new FileReader();
  //Cizgiler = new Array();
  shape.clearShapes();
  fr.onload=function(){
      document.getElementById('sourceFileText').innerHTML=fr.result;
      var lines = fr.result.split('\n');
      //console.log(lines);
      for(var line = 0; line < lines.length; line++){
        document.getElementById('convertedFileText').innerHTML+=convert(lines[line]);
      }
      //console.log(Cizgiler);
      ciz();
  }
  fr.readAsText(this.files[0]);

}
document.getElementById("uploadInput").addEventListener("change", updateSize, false);
//document.getElementById('convertedFileText').innerHTML+=convert("G1X445.73Y602.26Y76.5F300");
var startx=0,starty=0;
function convert(line){
  let str = "";
  let regex = "";
  let f = "";
  let endx=0,endy=0,endz=0;
  regex = /N(\d+\.\d+|\d+)/;f = line.match(regex); if(f){str += f[0]+" ";}
  regex = /X(\d+\.\d+|\d+)/;f = line.match(regex); if(f){str += f[0]+" ";  endx=parseFloat(f[1]);console.log(f[1]+" f " + endx);}
  regex = /Y(\d+\.\d+|\d+)/;f = line.match(regex); if(f){str += f[0]+" ";  endy=parseFloat(f[1]);}
  regex = /Z(\d+\.\d+|\d+)/;f = line.match(regex); if(f){str += f[0]+" ";  endz=parseFloat(f[1]);}
  regex = /F(\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  console.log(endx);
  ///Cizgiler.push(new Line(startx,starty,endx,endy));
  shape.addLine(new Line(startx,starty,endx,endy));
  startx=endx;starty=endy;
  if(str.length>0)str += '\n';
  return str;
}

function yaz(){
  alert("TEst");
}
function ciz(){
  const canvas = document.getElementById('my-canvas');
  const ctx = canvas.getContext('2d');
  ctx.clearRect(0, 0, canvas.width , canvas.height);
  ctx.lineWidth = 1;
  ctx.restore();
  shape.drawShapes(ctx);
    
}


 function Degerleri_Yenile(){
  shape.emptyCizik;
  document.getElementById('convertedFileText').innerHTML="";
 }
 function Cizgileri_Olustur(source){
  var lines = source.split('\n');
      console.log(lines);
      for(var line = 0; line < lines.length; line++){
        document.getElementById('convertedFileText').innerHTML+=convert(lines[line]);
      }
 }



 //Eventler
 document.getElementById('sourceFileText').onkeydown=function() { 
  Degerleri_Yenile();
  Cizgileri_Olustur(document.getElementById('sourceFileText').value);
  ciz();
 }

 document.getElementById('kare').onclick=function() { 
  shape.addRectangle(new Rectangle(Math.floor(Math.random() * 100),Math.floor(Math.random() * 100),Math.floor(Math.random() * 100),Math.floor(Math.random() * 100)));
  ciz();
 }
 document.getElementById('circle').onclick=function() { 
  shape.addCircle(new Circle(Math.floor(Math.random() * 100),Math.floor(Math.random() * 100),Math.floor(Math.random() * 100)));
  ciz();
 }
 document.getElementById('line').onclick=function() { 
  shape.addLine(new Line(Math.floor(Math.random() * 100),Math.floor(Math.random() * 100),Math.floor(Math.random() * 100),Math.floor(Math.random() * 100)));
  ciz();
 }

 document.getElementById('temizle').onclick=function() { 
  shape.clearShapes();
  ciz();
 }

 document.getElementById('my-canvas').onclick=function(e) { 
  var rect = document.getElementById('my-canvas').getBoundingClientRect();
  shape.setSelected(false);
  shape.selectObject(e.clientX-rect.left,e.clientY-rect.top,0,0,1);
  ciz();
 }