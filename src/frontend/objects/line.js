class Line {
  
  constructor(xn1, yn1, xn2,yn2) {
    this.xn1 = xn1;
    this.yn1 = yn1;
    this.xn2 = xn2;
    this.yn2 = yn2;
    this.selected=false;
    
  }

  get length(){
    return Math.sqrt( (Math.abs(this.xn1 - this.xn2) * Math.abs(this.xn1 - this.xn2) ) + ( Math.abs(this.yn1 - this.yn2) * Math.abs(this.yn1 - this.yn2)));
  }

  setSelected(select){
    this.selected=select;
  }

  select(px,py,CX,CY,Scale){
    let xs, xe, ys, ye,xmer,ymer;
    let Xsize=5,Ysize=5;
    let mxs = px - Xsize,
        mxe = px + Xsize, 
        mys = py - Ysize, 
        mye = py + Ysize;
        
        xmer = (px - CX) / Scale;
        ymer = (py - CY) / Scale;
        mxs  = (mxs - CX) / Scale;
        mxe  = (mxe - CX) / Scale;
        mys  = (mys - CX) / Scale;
        mye  = (mye - CY) / Scale;
    
    
    if (this.xn1 > this.xn2) {
        xs = this.xn2;
        xe = this.xn1;
    } else {
        xs = this.xn1;
        xe = this.xn2;
    }
    if (this.yn1 > this.yn2) {
        ys = this.yn2;
        ye = this.yn1;
    } else {            
        ys = this.yn1;
        ye = this.yn2;
    }

    if ((mxe > xs && mxs < xe) && (mye > ys && mys < ye)) {
    
        let distance = Math.abs(((this.xn2 - this.xn1) * (this.yn1 - ymer) - (this.yn2 - this.yn1) * (this.xn1 - xmer)))
                    / Math.sqrt((this.yn2 - this.yn1) * (this.yn2 - this.yn1) + (this.xn2 - this.xn1) * (this.xn2 - this.xn1));
            
        let distanceW = Math.sqrt((mxe - mxs) * (mxe - mxs) / 4. + (mye - mys) * (mye - mys) / 4.);
        if (distance < distanceW) this.selected = true;
    }

    return this.selected;

  }

  draw(ctx){
    ctx.beginPath();
    if(this.selected)ctx.strokeStyle = "red";
    else ctx.strokeStyle = "blue";
    ctx.moveTo(this.xn1,this.yn1);
    ctx.lineTo(this.xn2,this.yn2);
    ctx.stroke();
   }
   
   MoveToObject(ShiftX,ShiftY) {
    this.xn1-=ShiftX;this.yn1+=ShiftY;
    this.xn2-=ShiftX;this.yn2+=ShiftY;
}

}

export default Line;