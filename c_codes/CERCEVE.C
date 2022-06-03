/*
void cerceve(char *title,int x1,int y1,int x2,int y2, int w_fcolor,int w_bcolor,int m_fcolor,int m_bcolor)
{
int i,x,l,z;
textcolor(w_fcolor);
textbackground(w_bcolor);
if ((x2>x1)&&(y2>y1)){
   gotoxy(x1,y1);cprintf("%c",201);gotoxy(x2,y1);cprintf("%c",187);
   gotoxy(x1,y2);cprintf("%c",200);gotoxy(x2,y2);cprintf("%c",188);

   for(i=x1+1;i<=(x2-1);++i){
                             gotoxy(i,y1);cprintf("%c",205);
                             gotoxy(i,y2);cprintf("%c",205);
                             }
   for(i=y1+1;i<=(y2-1);++i){
                             gotoxy(x1,i);cprintf("%c",186);
                             gotoxy(x2,i);cprintf("%c",186);
                             }
x=x2-x1; l=strlen(title);z=(int)((x-l)/2);
if((x>l)&&(z!=0)){
                  textcolor(m_fcolor);
                  textbackground(m_bcolor);
                  gotoxy(x1+z,y1);
                  cprintf("%s",title);
}
}
}
*/