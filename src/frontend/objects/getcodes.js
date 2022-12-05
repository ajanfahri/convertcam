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
  shape.cizikekle(startx,starty,endx,endy);
  startx=endx;starty=endy;
  if(str.length>0)str += '\n';
  return str;
}