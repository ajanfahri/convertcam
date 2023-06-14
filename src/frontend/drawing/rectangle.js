import Line from './line.js';

class Rectangle {
  
  lines = new Array;
  constructor(startx, starty, width,height) {
    this.selected = false;
    this.lines.push(new Line(startx, starty,width,starty));
    this.lines.push(new Line(width, starty,width,height));
    this.lines.push(new Line(width, height,startx,height));
    this.lines.push(new Line(startx,height,startx,starty));
    this.startx = startx;
    this.starty = starty;
    this.width = width;
    this.height = height;
    
  }
  setSelected(select){
    this.selected=select;
    this.lines.forEach(item => item.setSelected(select));
  }
  select(px,py,CX,CY,Scale){
    
    for(let i=0;i< this.lines.length;i++){
      if(this.lines[i].select(px,py,CX,CY,Scale)){
        this.selected=true;
        break;
      }
    }
    if(this.selected)this.lines.forEach(item => item.setSelected(true));
    return this.selected;
  }

  

  draw(ctx){
    this.lines.forEach(item => item.draw(ctx));
  } 

  MoveToObject( ShiftX, ShiftY) {
    //console.log("burda");}
    for(let j=0;j<this.lines.length;j++)
        this.lines[j].MoveToObject(ShiftX,ShiftY);
    }
}

export default Rectangle;