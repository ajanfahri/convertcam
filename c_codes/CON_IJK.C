#include<math.h>
	 struct dxfconvert{//25//dec//2002//variable olmadigi icin extern tanimlamaya gerek yok
		unsigned int indx;
		int atrib;
    double rad;
		double xn1,yn1,zn1,xn2,yn2,zn2; //21/Apr/01 float idi.
		                };// oge1[1];


char merkez(struct dxfconvert oge, double *xmer,double *ymer,double *start,double *end){
long double delta=-1,angle,radius,A,B,aa,bb,cc;
   if(oge.indx==2||oge.indx==3){
   radius=oge.rad;
   if(fabs(oge.xn2-oge.xn1)>0.000099)
   angle=atan2l(oge.yn2-oge.yn1,oge.xn2-oge.xn1)*360/2/M_PI;
   else {if(oge.yn2>oge.yn1)angle=90;else angle=270;}
   if(angle<0)angle=angle+360;
   if(angle>=90&&angle<270)radius=-radius;
   if(fabs(oge.xn1-oge.xn2)>0.000099){
   A=(oge.yn1-oge.yn2)/(oge.xn2-oge.xn1);
   B=(oge.yn2*oge.yn2+oge.xn2*oge.xn2-oge.yn1*oge.yn1-oge.xn1*oge.xn1)/(2*(oge.xn2-oge.xn1));
   aa=1+A*A;
   bb=2*(B*A-A*oge.xn1-oge.yn1);
   cc=oge.xn1*oge.xn1+oge.yn1*oge.yn1+B*B-2*B*oge.xn1-radius*radius;
   delta=(bb/aa)*(bb/aa)/4.-cc/aa;
   if(delta<0&&fabs(delta)<0.001)delta=0;//14//feb//2002//haluk delta<0 ilave
   if(radius>=0&&delta>=0){
	 *ymer=(-bb/(2*aa)-sqrtl(delta));
  	 *xmer=B+A**ymer;
 } else if(delta>=0){
 	 *ymer=(-bb/(2*aa)+sqrtl(delta));
	 *xmer=B+A**ymer;}
	 }
else if(fabs(oge.yn1-oge.yn2)>0.000099){
   A=0;
   B=(oge.yn1+oge.yn2)/((double)2);
   aa=1;
   bb=-2*oge.xn1;
   cc=oge.xn1*oge.xn1+oge.yn1*oge.yn1+B*B-2*oge.yn1*B-radius*radius;
   delta=bb*bb-4*aa*cc;
 if(fabs(delta)<0.0001)delta=0;
if(radius>=0&&delta>=0){*xmer=(-bb-sqrtl(delta))/(2*aa);*ymer=B+A**xmer;}
else if(radius<0&&delta>=0){*xmer=(-bb+sqrtl(delta))/(2*aa);*ymer=B+A**xmer;}
                                       }
else  if(delta<0) return 0;
  if((oge.xn1-*xmer)!=0||(oge.yn1-*ymer)!=0)if((oge.xn1-*xmer)!=0){*start=atan2(oge.yn1-*ymer,oge.xn1-*xmer);if(*start<0)*start=*start+2.0*M_PI; }else {if((oge.yn1-*ymer)>0)*start=M_PI_2;else *start=3.0*M_PI_2;}
  if((oge.xn2-*xmer)!=0||(oge.yn2-*ymer)!=0)if((oge.xn2-*xmer)!=0){*end=atan2(oge.yn2-*ymer,oge.xn2-*xmer);if(*end<0)*end=*end+2*M_PI;}else {if((oge.yn2-*ymer)>0)*end=M_PI_2;else *end=3.0*M_PI_2;}

                             }
return 1;
}//void merkez

void convert_ijk(){
double xmer,ymer,start,RADIUS=0,Xs=0,Ys=0,Zs=0,Xe=0,Ye=0,Ze=0,I,J;
dxfconvert oge;
oge.indx=2;//G3 ->3,,G2->2 atamasi yap.
oge.rad=-RADIUS*1000.;
oge.xn1=Xs;
oge.yn1=Ys;
oge.zn1=Zs;
oge.xn2=Xe;
oge.yn2=Ye;
oge.zn2=Ze;
merkez(oge,&xmer,&ymer,&start,&start);
I=J=0;
I=xmer-oge.xn1;
J=ymer-oge.yn1;
                  }
