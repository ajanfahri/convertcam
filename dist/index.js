function updateSize() {
  let nBytes = 0,
      oFiles = this.files,
      nFiles = oFiles.length;
  for (let nFileId = 0; nFileId < nFiles; nFileId++) {
    nBytes += oFiles[nFileId].size;
  }
  
  let sOutput = nBytes + " bytes";
  // optional code for multiples approximation
  const aMultiples = ["KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"];
  /*for (nMultiple = 0, nApprox = nBytes / 1024; nApprox > 1; nApprox /= 1024, nMultiple++) {
    sOutput = nApprox.toFixed(3) + " " + aMultiples[nMultiple] + " (" + nBytes + " bytes)";
  }*/
  // end of optional code
  //document.getElementById("fileNum").innerHTML = nFiles;
  //document.getElementById("fileSize").innerHTML = sOutput;
  document.getElementById("orjinalFile").innerHTML = oFiles[0].name + " "+nFiles + " " + sOutput;
  
 

//var file = this.files[0];
document.getElementById('convertedFileText').innerHTML="";
  var fr=new FileReader();
      fr.onload=function(){
          document.getElementById('sourceFileText').innerHTML=fr.result;

  var lines = fr.result.split('\n');
  //console.log(lines);
  for(var line = 0; line < lines.length; line++){
    //console.log(lines[line]);
    document.getElementById('convertedFileText').innerHTML+=convert(lines[line]);
    
  }


      }
      fr.readAsText(this.files[0]);


  
 //};
}
document.getElementById("uploadInput").addEventListener("change", updateSize, false);
document.getElementById('convertedFileText').innerHTML+=convert("G1X445.73Y602.26Y76.5F300");

function convert(line){
  //const regex = /X(\d+\.\d+)(?:Y(\d+\.\d+))?|Y(\d+\.\d+)/;

  let str = "";
  let regex = "";
  let f = "";
  
  regex = /N(\d+\.\d+|\d+)/;f = line.match(regex); if(f)str += f[0]+" ";
  regex = /X(\d+\.\d+|\d+)/;f = line.match(regex); if(f)str += f[0]+" ";
  regex = /Y(\d+\.\d+|\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  regex = /Z(\d+\.\d+|\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  regex = /F(\d+)/;f = line.match(regex);if(f)str += f[0]+" ";
  if(str.length>0)str += '\n';
  //const regex = new RegExp(/^a...s$/);
  //return regex.test(line);
  /*let str="";
  //console.log(line);
  const m = line.match(regex);

  console.log(m);
    if (m) {
          if (m[1]) str+=`X: ${m[1]} `;
          if (m[2]) str+=`Y: ${m[2]} `;
          if (m[3]) str+=`Y: ${m[3]} `;
          if (m[4]) str+=`F: ${m[4]} `;
      }
  */
  return str;
}