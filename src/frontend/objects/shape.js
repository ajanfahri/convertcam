
class Shape {
  
  constructor() {
    this.selectNo=0;
    this.shapes = new Array();
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
  }

  selectObject(px,py,CX,CY,Scale){
   let secilen =-1;
    for(let i=0;i< this.shapes.length;i++){
      if(this.shapes[i].select(px,py,CX,CY,Scale)){
        secilen = i;
        break;
      }
    }
  }
  
  setSelected(select){
    this.shapes.forEach(item => item.setSelected(select));
  }
  drawShapes(ctx){
    this.shapes.forEach(item => item.draw(ctx,false));
  }


}

export default Shape;