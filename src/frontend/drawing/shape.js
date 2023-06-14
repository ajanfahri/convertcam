
class Shape {
  
  constructor() {
    this.selectNo=0;
    this.shapes = new Array();
    this.secilen = -1;
  }

  addLine(line){
    this.shapes.push(line);
  }

  addRectangle(rectangle){
    this.shapes.push(rectangle)
  }

  addCircle(circle){
    this.shapes.push(circle)
  }

  clearShapes(){
    this.shapes=new Array();
    this.secilen=-1;
  }

  selectObject(px,py,CX,CY,Scale){
   
    for(let i=0;i< this.shapes.length;i++){
      if(this.shapes[i].select(px,py,CX,CY,Scale)){
        this.secilen = i;
        break;
      }
    }
  }
  
  setSelected(select){
    this.shapes.forEach(item => item.setSelected(select));
  }
  isSelected(){
    if (this.secilen == -1) return false; else return true;
  }
  drawShapes(ctx){
    this.shapes.forEach(item => item.draw(ctx,false));
  }

  MoveSelectedObject( ShiftX, ShiftY) {
     this.shapes[this.secilen].MoveToObject(ShiftX,ShiftY);
     /*if(this.shapes[this.secilen] instanceof Line)      this.shapes[this.secilen].MoveToObject(ShiftX,ShiftY);
else if(this.shapes[this.secilen] instanceof Rectangle) this.shapes[this.secilen].MoveToObject(ShiftX,ShiftY);
else if(this.shapes[this.secilen] instanceof Circle)    this.shapes[this.secilen].MoveToObject(ShiftX,ShiftY);*/
}

}

export default Shape;