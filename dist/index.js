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

  fr.onload=function(){
      document.getElementById('sourceFileText').innerHTML=fr.result;
      var lines = fr.result.split('\n');
      //console.log(lines);
      for(var line = 0; line < lines.length; line++){
        document.getElementById('convertedFileText').innerHTML+=convert(lines[line]);
      }
  }
  fr.readAsText(this.files[0]);

}
document.getElementById("uploadInput").addEventListener("change", updateSize, false);
document.getElementById('convertedFileText').innerHTML+=convert("G1X445.73Y602.26Y76.5F300");

function convert(line){
  let str = "";
  let regex = "";
  let f = "";
  regex = /N(\d+\.\d+|\d+)/;f = line.match(regex); if(f)str += f[0]+" ";
  regex = /X(\d+\.\d+|\d+)/;f = line.match(regex); if(f)str += f[0]+" ";
  regex = /Y(\d+\.\d+|\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  regex = /Z(\d+\.\d+|\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  regex = /F(\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  if(str.length>0)str += '\n';
  return str;
}