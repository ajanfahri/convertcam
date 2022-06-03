//-------------------------------  CONVERT.C  ---------------------------------

#include "dir.h"
#include <alloc.h>
#include <ctype.h>
#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <process.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>
void cerceve(int x1,int y1,int x2,int y2, int w_fcolor);
char *getstring(int x1,int y1,int uzunluk,int fcolor,int back,char *legal);
int menu(void);
int dosya_ac(void);

int satir_oku(int baslangic);
FILE *fptrx;
FILE *yeni;
fpos_t filepos;
int cursorx,cursory;
char strSatir[150];
fpos_t pos[22];
int bassatir=1;
int viscurpos=1,realcurpos;
char dosya_ismi[13]="";
enum{ENTER=13,F1=59+256,F2,F3,F4,F5,F6,F7,F8,F9,F10,UP=72+256,PG_UP,LEFT=75+256,RIGHT=LEFT+2,DOWN=80+256,PG_DN};

int kbhits(void){
	union REGS ireg;
	if(kbhit()){          // A character and 0?
		ireg.h.ah=0x06;
		ireg.h.dl=0xff;
		intdos(&ireg,&ireg);
		if(ireg.h.al==0){   // extended key code
			ireg.h.ah=0x06;
			ireg.h.dl=0xff;
			intdos(&ireg,&ireg);
			return(ireg.h.al+0x100);
			}
		return ireg.h.al ;  // an ASCII character
		}
	return 0;             // no character
	}

int dosya_ac()
{
//char chr,krk=0;
cerceve(5,23,28,25,RED);
textcolor(BLUE);
strcpy(dosya_ismi,getstring(6,24,9,13,8,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789abcdefghijklmnopqrstuvwxyz._-=)(&%^"));
strcat(dosya_ismi,".CAM");
	if((yeni = fopen(dosya_ismi,"rt")) == NULL)
                    {
                    cerceve(30,11,60,13,RED);
                    gotoxy(31,12);textcolor(LIGHTGREEN);
                    cprintf("%s Bulunamadi",dosya_ismi);getch();}
  else{fclose(fptrx);fclose(yeni);fptrx = fopen(dosya_ismi,"rt");clrscr();satir_oku(1);}




menu();
return 0;
}




void kaydet()
{

/*while(!feof(fptrx)){
     if (satir==22)break;
     chr=fgetc(fptrx);
      if (chr=='\n'){
                     if(satir2>=baslangic){
                     gotoxy(2,satir+1);textcolor(15);
                     cprintf("%s \n",strSatir);satir++;}
                     strset(strSatir,'\0');i=0;satir2++;}
      else{strSatir[i]=chr;i++;}
}//while

fwrite(&s, sizeof(s), 1, stream);  write struct s to file */
}
int satir_oku(int baslangic)
{
bassatir=baslangic;
clrscr();
//textbackground(BLUE);
cerceve(1,1,79,25,RED);
gotoxy(35,1);
textcolor(15);
cprintf("%s",dosya_ismi);

int satir2=1;
int satir=1;
char chr;
    int i=0;
    fseek(fptrx, 0L, SEEK_SET);
while(!feof(fptrx)){
     if (satir==22)break;
     chr=fgetc(fptrx);
      if (chr=='\n'){
                     if(satir2>=baslangic){
                     fgetpos(fptrx, &pos[satir]);
                     gotoxy(2,satir+1);textcolor(15);
                     cprintf("%s \n",strSatir);satir++;}
                     strset(strSatir,'\0');i=0;satir2++;}
      else{strSatir[i]=chr;i++;}
}//while
//bassatir=baslangic+22;
return 0;

}

void isim_al()
{
//textcolor(WHITE);
//cprintf("Dosya Ismi Giriniz : ");scanf("%s",&dosya_ismi);
//satir_oku();
}


int main(void)
{
FILE *fptr;
int secim;
clrscr();
cursorx=2,cursory=2;

cerceve(1,1,79,25,RED);


   if ((fptrx = fopen("ERCI.CAM", "rt"))
       == NULL)
   {
      fprintf(stderr, "Cannot open input file.\n");
      return 1;
   }

menu();
//textbackground(BLUE);
gotoxy(cursorx,cursory);
while(1){
        switch(secim=kbhits())
         {
                   case UP :  if(cursory>2){cursory--;gotoxy(cursorx,cursory);}break;
                   case DOWN : if(cursory<22){cursory++;gotoxy(cursorx,cursory);}break;
                   case LEFT : if(cursorx>2){cursorx--;gotoxy(cursorx,cursory);}break;
                   case RIGHT :if(cursorx<78){cursorx++; gotoxy(cursorx,cursory);}break;
                   case 8 : if(cursorx>2){cursorx--;gotoxy(cursorx,cursory);printf(" ");gotoxy(cursorx,cursory);}break;
                   case 327:  cursorx=2;gotoxy(cursorx,cursory);break;	//HOME
                   case 335:  cursorx=78;gotoxy(cursorx,cursory);break;	//HOME
                   case PG_UP : satir_oku(bassatir-22);menu();gotoxy(wherex(),wherey());break;
                   case PG_DN : satir_oku(bassatir+22);menu();gotoxy(wherex(),wherey());break;
                   case F1    : dosya_ac();break;
                   case F2    : kaydet();break;
                   case F10   : fclose(fptrx);break;
                   default    :
                              if((secim>=32)&&(secim<126))
                                  {printf("%c",secim);cursorx++;

                                  fptr = fopen(dosya_ismi, "wa");
                                  fsetpos(fptrx, &pos[5]);
                                  fputc(secim, fptrx); /* write struct s to file */
                                  fclose(fptr);
                                  }break;
            }
    }
clrscr();
fclose(fptrx);
return 0;
}

int menu(){
cerceve(1,23,79,25,RED);
textcolor(WHITE);
gotoxy(3,24);
  cprintf("F1.Dosya Ac        ");
  cprintf("F2.Sadelestir       ");
  cprintf("F3.Replace          ");
  cprintf("F10.Cikis");
textcolor(LIGHTGRAY);
return 0;
}


void cerceve(int x1,int y1,int x2,int y2, int w_fcolor)
{
int i;//,x,l,z;
textcolor(w_fcolor);

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
}

}

char *getstring(int x1,int y1,int uzunluk,int fcolor,int back,char *legal){

	int k,cursorcolor=9;
	char symtab[256]="";
	char al=0,xcursor[]="Û";
gotoxy(x1,y1);
	textcolor(GREEN);
cprintf("DOSYA ISMI :");
	textcolor(fcolor);
	for(k=0;k<=uzunluk;k++)printf(xcursor);
  gotoxy(x1+12,y1);
	textcolor(cursorcolor);
//	cprintf((x1+al)*8,y1*4*2-4,xcursor);

	do{
		k=kbhits();
		if(k){
			if(k>256){
				continue;
				}
			if(k==27){ symtab[0]='\0';break;}
			if(k==13) break;
			if(k==8)
				if(al>0){
					textcolor(back);//cprintf((x1+al)*8,y1*4*2-4, xcursor);
          cprintf(xcursor);
					al--; *(symtab+al)='\0';
					}
				else{
   	 			continue;
					}
			textcolor(back);//cprintf((x1+al)*8,y1*4*2-4,xcursor);
      cprintf(xcursor);
			if(k!=8){
        if(strlen(legal)){
					if(strchr(legal,k)!=0){*(symtab+al++)=k;}
					}
        else{ *(symtab+al++)=k;}
        }
      gotoxy(x1+12,y1);
			textcolor(fcolor);//cprintf(x1*8,y1*4*2-4,symtab);
      cprintf("%s",symtab);
			textcolor(cursorcolor);//cprintf((x1+al)*8,y1*4*2-4,xcursor);
      cprintf(xcursor);
			}//if(k)
		}while(al<uzunluk);
	textcolor(back);//cprintf((x1+al)*8,y1*4*2-4,xcursor);
      cprintf(xcursor);
	k=strlen(symtab);if(symtab[k]==' ') while(symtab[k]!=' ') --k;

	symtab[k]='\0';
	return symtab;
	}
