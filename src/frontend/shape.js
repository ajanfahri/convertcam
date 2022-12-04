class Shape {
  
  constructor() {
    
    this.lines = new Array();
    this.rectangles = new Array();
    this.circles = new Array();

  }

  addLine(line){
    this.lines.push(line);
  }

  addRectangle(rectangle){
    this.rectangles.push(rectangle)
  }

  addCircle(circle){
    this.circles.push(circle)
  }

  clearShapes(){
    this.rectangles=new Array();
    this.lines=new Array();
    this.circles=new Array();
  }

  
  drawShapes(ctx){
    if(this.lines.length>0)
    this.lines.forEach(item => ctx.lineTo(item.endx, item.endy));
    if(this.rectangles.length>0)
    this.rectangles.forEach(item => ctx.rect(item.startx, item.starty, item.width,item.height));
    if(this.circles.length>0)
    /*this.circles.forEach(function (item) {
      //ctx.beginPath();
      ctx.arc(item.centerx, item.centery, item.radius,0,2*Math.PI,true);
      ctx.closePath();
  });*/
    this.circles.forEach(item => ctx.arc(item.centerx, item.centery, item.radius,0,2*Math.PI,true));
    
  }


}

export default Shape;