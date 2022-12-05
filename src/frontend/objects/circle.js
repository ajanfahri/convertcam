class Circle {
  
  constructor(centerx, centery, radius) {
    this.selected = false;
    this.xc = centerx;
    this.yc = centery;
    this.radius = radius;
  }

  setSelected(select){
    this.selected=select;
  }  
  select(px,py,CX,CY,Scale){
    let xmer,ymer;
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
    
    
        let sa=0, ea=360;
        
        
        if (ea < sa) {
            ea += 2 * Math.PI;
        }

        let start = sa, delta_aci = (ea - sa) / 360., min_delta = 0;
        if ((mxe - mxs) > (mye - mys)) {
            min_delta = (mye - mys);
        } else {
            min_delta = (mxe - mxs);
        }
        if ((min_delta != 0) && this.radius != 0 && (delta_aci > min_delta)) {
            delta_aci = min_delta / Math.abs(this.radius);
        }
        while (start < ea) {
            if ((this.xc + Math.abs(this.radius) * Math.cos(start)) >= mxs && (this.xc + Math.abs(this.radius) * Math.cos(start)) <= mxe) {
                if ((this.yc + Math.abs(this.radius) * Math.sin(start)) >= mys && (this.yc + Math.abs(this.radius) * Math.sin(start)) <= mye) {
                    this.selected = true;
                    break;
                }
            }
            start += delta_aci;
        }
    return this.selected;

  }

  draw(ctx){
    ctx.beginPath();
    if(this.selected)ctx.strokeStyle = "red";
    else ctx.strokeStyle = "blue";
    ctx.arc(this.xc, this.yc, this.radius,0,2*Math.PI,true)
    ctx.stroke();
   }  
   
}

export default Circle;