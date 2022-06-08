class Line {
  
  constructor(startx, starty, endx,endy) {
    this.startx = startx;
    this.starty = starty;
    this.endx = endx;
    this.endy = endy;
    
  }

  get length(){
    return Math.sqrt( (Math.abs(this.startx - this.endx) * Math.abs(this.startx - this.endx) ) + ( Math.abs(this.starty - this.endy) * Math.abs(this.starty - this.endy)));
  }

  set cizikekle(cizik){

  }

  
}

export default Line;