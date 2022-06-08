class Shape {
  
  constructor() {
    
    this.cizikler = new Array();
  }

  
  cizikekle(cizik){
    this.cizikler.push(cizik);
  }

  get emptyCizik(){
    this.cizikler = new Array();
  }

  ciz(ctx){
    this.cizikler.forEach(item => ctx.lineTo(item.endx, item.endy));
  }

  
}

export default Shape;