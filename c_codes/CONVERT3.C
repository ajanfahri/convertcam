//-------------------------------  CONVERT.C  ---------------------------------
//20//nov//2016//rev0// aranan konulacak (*) karakteri ile aranan ile baslayan tum satir siliniyo
//------------------------------------
#define MAIN

#include "global.h"
void baslik_yaz(void);
extern int settings(void);
char CloseQuery();
int scroll(int baslangic,long int toplamsatir);
void cerceve(int x1,int y1,int x2,int y2, int w_fcolor,int bcolor);
void incecerceve(int x1,int y1,int x2,int y2, int w_fcolor,int bcolor);
char *stringal(int x1,int y1,int uzunluk,char *legal,int gelen);
int menu(void);
void analiz(void);
int dosya_ac(void);
void kaydet();
void sadelestir(int convert_type);
int dosya_penceresi(char kayit);
int satir_oku(int baslangic);
void kodlar(void);
void bosluk(void);
void satirno(void);
int history(int x1,int y1,int x2,int y2,int gelen);
void replace_penceresi(void);
void replace(int baslangic,char *aranan,char *konulacak);
void degistir3(char *aranan,char *konulacak);
void degistir(char *aranan,char *konulacak);
int farkli_kaydet(void);
void ayar_oku(void);
void ayar_kaydet(void);
void convert(void);
//////////////
char aranan[37]="",konulacak[37]="";
FILE *fptrx;
double I,J;

int key,oncekiscroll=3;
long int toplamsatir=0;
char strSatir[150];
char yeniSatir[150];
char degisiklik=0;
fpos_t pos[22];
int bassatir=1;
char dosya_ismi[13]="";
char yol[80]="C:\\BORLANDC\\CONVERT";
char kokdizin[80]="C:\\BORLANDC\\CONVERT";
char gecici[80]="";
char yazilan_isim[13]="";
char file_name[13]="";
char sozcuk=1;
unsigned int gtip=0;
char hata_mesaji(char *mesaj);


struct message read_msg(int msg_number){//3//mar//2003//mesaj artik hard drive dan okunuyor
int msg_handle;
struct message mesaj;
if(parameters.dil==1)msg_number+=600;
if((msg_handle =open("message.msg",O_BINARY,S_IREAD)) == -1){
perror("Error:");  printf("\n check the file message.msg in directory\n message.msg dosyasini dizinde oldugunu kontrol et");
getch();
exit (0);
                                                            }
lseek(msg_handle,80.*msg_number,SEEK_SET);
read(msg_handle,mesaj.out,80.);
close(msg_handle);
return mesaj;
}
//----------------------------------------------------------------------------
void ekran_sil(void)
{
asm{
    mov ah,6
    mov al,0
    mov ch,1
    mov cl,1
    mov dh,21
    mov dl,77
    mov bh,7
    int 0x10
}
}

char hata_mesaji(char *mesaj)
{
char key;
char hata_buf[1096];        //60
int width=80;
int sx=(width/2)-(strlen(mesaj)/2)-3;
int ex=(width/2)+(strlen(mesaj)/2)+3;
gettext(sx, 11, ex, 13, hata_buf);
_setcursortype(0);
//textbackground(0);
cerceve(sx,11,ex,13,RED,0);
for(int i=sx+1;i<ex;++i){gotoxy(i,12);cprintf(" ");}
gotoxy(sx+3,12);textcolor(LIGHTGREEN);
cprintf("%s",mesaj);
key=getch();
puttext(sx, 11, ex, 13, hata_buf);
return key;
}


	 struct dxfconvert{//25//dec//2002//variable olmadigi icin extern tanimlamaya gerek yok
		unsigned int indx;
		int atrib;
    double rad;
		double xn1,yn1,zn1,xn2,yn2,zn2; //21/Apr/01 float idi.
		                };


char merkez(struct dxfconvert oge, double *xmer,double *ymer,double *start,double *end){
long double delta=-1,radius,A,B,aa,bb,cc;

struct CENTER{
              double x,y;
              }root[2];

if(oge.indx==2||oge.indx==3){
   radius=oge.rad;

   if(fabs(oge.xn1-oge.xn2)>0.000099){
       A=(oge.yn1-oge.yn2)/(oge.xn2-oge.xn1);
       B=(oge.yn2*oge.yn2+oge.xn2*oge.xn2-oge.yn1*oge.yn1-oge.xn1*oge.xn1)/(2*(oge.xn2-oge.xn1));
       aa=1+A*A;
       bb=2*(B*A-A*oge.xn1-oge.yn1);
       cc=oge.xn1*oge.xn1+oge.yn1*oge.yn1+B*B-2*B*oge.xn1-radius*radius;
       delta=(bb/aa)*(bb/aa)/4.-cc/aa;
       if(delta<0&&fabs(delta)<0.001)delta=0;//14//feb//2002//haluk delta<0 ilave

       if(delta>=0){
           root[0].y=(-bb/(2*aa)-sqrtl(delta));
           root[0].x=B+A*root[0].y;
           root[1].y=(-bb/(2*aa)+sqrtl(delta));
           root[1].x=B+A*root[1].y;
               }//if(delta>=0){
        else if(delta<0) return 0;

	                                    }//if(fabs(oge.xn1-oge.xn2)>0.000099){
       else if(fabs(oge.yn1-oge.yn2)>0.000099){
       A=0;
       B=(oge.yn1+oge.yn2)/((double)2);
       aa=1;
       bb=-2*oge.xn1;
       cc=oge.xn1*oge.xn1+oge.yn1*oge.yn1+B*B-2*oge.yn1*B-radius*radius;
       delta=bb*bb-4*aa*cc;
       if(fabs(delta)<0.0001)delta=0;
       if(delta>=0){
         root[0].x=(-bb-sqrtl(delta))/(2*aa);
         root[0].y=B+A*root[0].x;
         root[1].x=(-bb+sqrtl(delta))/(2*aa);
         root[1].y=B+A*root[1].y;
         }//if(delta>=0)
                                       }//else if(fabs(oge.yn1-oge.yn2)>0.000099){

      else  if(delta<0) return 0;

  double first_start_to_end,second_start_to_end;

  if((oge.xn1-root[0].x)!=0||(oge.yn1-root[0].y)!=0)if((oge.xn1-root[0].x)!=0){*start=atan2(oge.yn1-root[0].y,oge.xn1-root[0].x);if(*start<0)*start=*start+2.0*M_PI; }else {if((oge.yn1-root[0].y)>0)*start=M_PI_2;else *start=3.0*M_PI_2;}
  if((oge.xn2-root[0].x)!=0||(oge.yn2-root[0].y)!=0)if((oge.xn2-root[0].x)!=0){*end=atan2(oge.yn2-root[0].y,oge.xn2-root[0].x);if(*end<0)*end=*end+2*M_PI;}else {if((oge.yn2-root[0].y)>0)*end=M_PI_2;else *end=3.0*M_PI_2;}
  if(oge.indx==3){
  if(*end<*start)first_start_to_end=2*M_PI-fabs(*end-*start);
  else first_start_to_end=*end-*start;
               }//if(oge.indx==3){
  else if(oge.indx==2){
  if(*end>*start)first_start_to_end=2*M_PI-fabs(*end-*start);
  else first_start_to_end=*start-*end;
               }//else if(oge.indx==2){

  if((oge.xn1-root[1].x)!=0||(oge.yn1-root[1].y)!=0)if((oge.xn1-root[1].x)!=0){*start=atan2(oge.yn1-root[1].y,oge.xn1-root[1].x);if(*start<0)*start=*start+2.0*M_PI; }else {if((oge.yn1-root[1].y)>0)*start=M_PI_2;else *start=3.0*M_PI_2;}
  if((oge.xn2-root[1].x)!=0||(oge.yn2-root[1].y)!=0)if((oge.xn2-root[1].x)!=0){*end=atan2(oge.yn2-root[1].y,oge.xn2-root[1].x);if(*end<0)*end=*end+2*M_PI;}else {if((oge.yn2-root[1].y)>0)*end=M_PI_2;else *end=3.0*M_PI_2;}
  if(oge.indx==3){
  if(*end<*start)second_start_to_end=2*M_PI-fabs(*end-*start);
  else second_start_to_end=*end-*start;
               }//if(oge.indx==3){
   else if(oge.indx==2){
   if(*end>*start)second_start_to_end=2*M_PI-fabs(*end-*start);
   else second_start_to_end=*start-*end;
               }//else if(oge.indx==2){

  if(radius>0){
      if(first_start_to_end<second_start_to_end){*xmer=root[0].x;*ymer=root[0].y;}
      else{*xmer=root[1].x;*ymer=root[1].y;}
              }//if(radius>0)
  else {
  if(first_start_to_end>second_start_to_end){*xmer=root[0].x;*ymer=root[0].y;}
  else{*xmer=root[1].x;*ymer=root[1].y;}
            }//else {

                             }//if(oge.indx==2||oge.indx==3){
return 1;
}//void merkez

void convert_ijk(){
double startt=0,endt=0;//RADIUS=,Xs=0,Ys=0,Zs=0,Xe=0,Ye=0,Ze=0,I,J;
double xmer=0,ymer=0;
dxfconvert oge;
oge.indx=gtip;//G3 ->3,,G2->2 atamasi yap.
oge.rad=RADYUS;
oge.xn1=start.x;
oge.yn1=start.y;
oge.zn1=start.z;
oge.xn2=end.x;
oge.yn2=end.y;
oge.zn2=end.z;
merkez(oge,&xmer,&ymer,&startt,&endt);
I=J=0;
I=xmer-oge.xn1;
J=ymer-oge.yn1;
                  }

char *menu1[6]={" New                    ",
                " Open                   ",
                " Save                   ",
                " Save As                ",
                " Exit                   ",NULL};


char historysec[6][37]={"","","","","",""};
char historykon[6][37]={"","","","","",""};
char *menu2[5]={" Only Code Line         ",
                " Delete Line Numbers    ",
                " Put Space              ",
                " Convert to AJAN        ",NULL};

void ayar_oku(void)
{
FILE *fptrx;
if ((fptrx = fopen("convert.ini", "rt"))!= NULL)
{fseek(fptrx, 0L, SEEK_SET);
int i=0,satir=0,j=0,k=0;char chr;
while(!feof(fptrx))
{if (satir==10)break;
     chr=fgetc(fptrx);
           if (chr=='\n'){
                      if(satir==0||satir==2||satir==4||satir==6||satir==8){
                     strcpy(historysec[j],strSatir);j++;}
                     else if(satir==1||satir==3||satir==5||satir==7||satir==9){
                     strcpy(historykon[k],strSatir);k++;}
                     satir++;
                     strset(strSatir,'\0');i=0;}
      else{strSatir[i]=chr;i++;}
}//while
fclose(fptrx);
}

if((fptrx = fopen("setting.ini", "rt"))!=NULL){
fread(&parameters, sizeof(parameters), 1, fptrx);
fclose(fptrx);}
}

void ayar_kaydet(void)
{
 FILE *fptrx;
fptrx=fopen("convert.ini","wt");
 for(int i=0;i<5;i++)
 {
 if(strlen(historysec[i])>0)
    {
    fwrite(&historysec[i], strlen(historysec[i]), 1, fptrx);fputc('\n', fptrx);
    }
 if(strlen(historykon[i])>0)
    {
    fwrite(&historykon[i], strlen(historykon[i]), 1, fptrx);fputc('\n', fptrx);
    }
 }
fclose(fptrx);
fptrx=fopen("setting.ini","wt");
fwrite(&parameters, sizeof(parameters), 1, fptrx); /* write struct s to file */
fclose(fptrx);
}

int scroll(int baslangic,long int toplamsatir)
{
 if(toplamsatir>21){
 int toplamsayfa,sayfa,cursorpos;
 toplamsayfa=toplamsatir/21.;
 sayfa=baslangic/21;
 cursorpos=(sayfa*19)/toplamsayfa;
 if(cursorpos<=0){cursorpos=3;}else if(cursorpos>=19){cursorpos=21;}
 else{cursorpos+=3;}
 char c;
 if(cursorpos!=oncekiscroll){
  gotoxy(79,oncekiscroll);c=176;cprintf("%c",c);
  oncekiscroll=cursorpos;
  }
  gotoxy(79,cursorpos);c=219;cprintf("%c",c);

}
return 0;
}

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
//////////////////
unsigned oldc;
struct text_info c;

unsigned getfirstcolor(struct text_info *cl)
{
  gettextinfo(cl);
  return (cl->attribute);
}

void putcolor(unsigned oldcolor)
{
 textattr(oldcolor);
}

void cerceve_ciz(char *title,int x1,int y1,int x2,int y2, int w_fcolor,int w_bcolor,int m_fcolor,int m_bcolor)
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
    x=x2-x1;l=strlen(title);z=(int)((x-l)/2);
    if((x>l)&&(z!=0)){
    textcolor(m_fcolor);
    textbackground(m_bcolor);
    gotoxy(x1+z,y1);
    cprintf("%s",title);
   }
}
textbackground(BLACK);
}

void menu_doldur()
{
char msggg[56]="";
sprintf(msggg," %s ",read_msg(374).out);strcpy(menu1[0],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(375).out);strcpy(menu1[1],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(376).out);strcpy(menu1[2],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(377).out);strcpy(menu1[3],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(4).out);strcpy(menu1[4],msggg); strset(msggg,'\0');
/**menu1={" New           ",
        " Open          ",
        " Save          ",
        " Save As       ",
        " Exit          ",NULL};
*/
sprintf(msggg," %s ",read_msg(384).out);strcpy(menu2[0],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(385).out);strcpy(menu2[1],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(386).out);strcpy(menu2[2],msggg);strset(msggg,'\0');
sprintf(msggg," %s ",read_msg(387).out);strcpy(menu2[3],msggg);strset(msggg,'\0');

/*
*menu2={" Only Code Line      ",
        " Delete Line Numbers ",
        " Put Space           ",
        " Convert to AJAN        ",NULL};*/
}
int menu_secim(int x, int y, char *sec[],int reversecolor,int charcolor)
{
menu_doldur();
 int i, key1, key2;
 int nsec=0;
 oldc=getfirstcolor(&c);
 textcolor(charcolor);
 textbackground(reversecolor);
 for(i=0;sec[i]!=NULL;++i)
 {
  gotoxy(x,y+i);
  cprintf("%s",sec[i]);
  nsec++;
 }
 highvideo();i=0;--nsec;
 do{
      gotoxy(x,i+y);
      textcolor(reversecolor);
      textbackground(charcolor);
      cprintf("%s",sec[i]);
      textcolor(charcolor);
      textbackground(reversecolor);
      gotoxy(x,i+y);
      key1=getch();
      if((key1!=13)&&(key1==0))
      {
      key2=getch();
      if((key2==80)&&(i<nsec))
      {//asagi
         cprintf("%s",sec[i]);
         ++i;
      }
      else if((key2==80)&&(i==nsec)){//asagi
          cprintf("%s",sec[i]);
          i=0;
      }
      else if((key2==72)&&(i>0)){  //yukari
          cprintf("%s",sec[i]);
          --i;
      }
      else if((key2==72)&&(i==0)){  //yukari
          cprintf("%s",sec[i]);
          i=nsec;
      }
      else if(!(key1==13)) printf("a");
      }
      else if(!(key1==13)) printf("a");
      if(key1==27) i=27;
 }while (key1!=13&&key1!=27);
 putcolor(oldc);
 ++i;
 return i;
}

void DropDownMenu(int x1,int y1,int x2,int y2,char *baslik)
{
int secim,i,j;
_setcursortype(0);
gettext(x1, y1, x2, y2, buffer);
_setcursortype(0);
for(i=y1;i<=y2;i++){
  for(j=x1;j<=x2;j++){gotoxy(j,i);cprintf(" ");}}
if(strstr(baslik,"FILE")!=NULL){
cerceve_ciz(read_msg(373).out,2,17,19,23,RED,BLACK,GREEN,RED);
secim=menu_secim(3,18,menu1, BLACK, WHITE);
}else
{
cerceve_ciz(read_msg(383).out,28,18,53,23,RED,BLACK,GREEN,RED);
secim=menu_secim(29,19,menu2, BLACK, WHITE);
}
for(i=y1;i<=y2;i++){
for(j=x1;j<=x2;j++){gotoxy(j,i);cprintf(" ");}}
puttext(x1, y1, x2, y2, buffer);
if(strstr(baslik,"FILE")!=NULL){
switch(secim)
             {
             case 1 : break;
             case 2 : if(dosya_penceresi(0))
                      {dosya_ac();}break;
             case 3 : kaydet();break;
             case 4 : if(dosya_penceresi(1))
                      {farkli_kaydet();}
                      break;
             case 5 :if(degisiklik){
                      if(CloseQuery()){
                      textbackground(BLACK);textcolor(LIGHTGRAY);clrscr();ayar_kaydet();exit(0);}}
                      else{textbackground(BLACK);textcolor(LIGHTGRAY);clrscr();exit(0);}
                      break;
             case 27: break;
             default: break;
             }
}
else
{
switch(secim)
             {
             case 1 :sadelestir(0);satir_oku(1);menu();baslik_yaz();break;
             case 2 : sadelestir(1);satir_oku(bassatir);menu();baslik_yaz();break;
             case 3 : sadelestir(2);satir_oku(bassatir);menu();baslik_yaz();break;
             case 4 : sadelestir(0);sadelestir(3);satir_oku(1);menu();baslik_yaz();break;
             case 27: break;
             default: break;
             }
}
}

char CloseQuery()
{
int i,j;
char deger,chr;
gettext(5, 10, 70, 15, buffer);
for(i=10;i<=15;i++){
  for(j=5;j<=70;j++){gotoxy(j,i);cprintf(" ");}}
cerceve(5,10,70,15,RED,0);
gotoxy(30,10);
textcolor(LIGHTGREEN);
textbackground(1);
//cprintf("   SAVE FILE   ");
cprintf("   ");cprintf(read_msg(376).out);cprintf("  ");cprintf(read_msg(373).out);cprintf("   ");
textbackground(0);
gotoxy(8,14);
textcolor(RED);
textbackground(LIGHTGRAY);
cprintf(read_msg(400).out);//cprintf("   (E)NTER YES   ");
gotoxy(30,14);
cprintf(read_msg(401).out);//cprintf("   (N)  NO     ");
gotoxy(50,14);
cprintf(read_msg(402).out);//cprintf("    ESC  CANCEL    ");
gotoxy(8,12);
textbackground(0);
textcolor(GREEN);
cprintf(read_msg(403).out);//cprintf(" SAVE Changes ? ");
chr=255;
while(chr!='E'&&chr!='e'&&chr!='Y'&&chr!='y'&&chr!='H'&&chr!='h'&&chr!='N'&&chr!='n'&&chr!=13&&chr!=27){
chr=getch();
switch(chr){
						case 'E' : kaydet();deger=1;break;
						case 'e' : kaydet();deger=1;break;
						case 'Y' : kaydet();deger=1;break;
            case 'y' : kaydet();deger=1;break;
            case 'N' : deger=1;break;
            case 'n' : deger=1;break;
            case 'H' : deger=1;break;
            case 'h' : deger=1;break;
            case 13  : kaydet();deger=1;break;
            case 27  : deger=0;break;
            default  : break;}
         }
for(i=10;i<=15;i++)
{ for(j=5;j<=70;j++){gotoxy(j,i);cprintf(" ");}}
puttext(5, 10, 70, 15, buffer);
return deger;
}

void kayityolu()
{
strcpy(gecici,yol);
if(strcmp(yol,"C:\\"))
strcat(gecici,"\\");
strcat(gecici,dosya_ismi);
}

int dosya_ac()
{
kayityolu();
char command[120]="copy ";
  if(strlen(gecici)<1){/*clrscr();*/satir_oku(1);}
  else{
       if ((fptrx = fopen(gecici, "rt")) == NULL)
                    {
                    cerceve(30,11,60,13,RED,0);
                    gotoxy(31,12);textcolor(LIGHTGREEN);
                    cprintf("Cant find %s",gecici);getch();/*clrscr();*/satir_oku(1);fclose(fptrx);}
  else{fclose(fptrx);
       strcpy(yazilan_isim,dosya_ismi);
       strcat(command,gecici);strcat(command," temp.cam");system(command);
       strcpy(dosya_ismi,"temp.cam");/*clrscr();*/satir_oku(1);}
  }
//menu();
baslik_yaz();
return 0;
}

int farkli_kaydet()
{
int satir2=1;
char chr;
int i=0;
char *ptr,key;
strcpy(dosya_ismi,"temp.cam");
if(strlen(file_name)>0){

	if(strlen(file_name)!=0) {
	ptr=strchr(file_name,'.');
	if(ptr) file_name[(int)(ptr-file_name)]='\0';
  }

strcat(file_name,".CAM");strupr(file_name);
strcpy(gecici,yol);
if(strcmp(yol,"C:\\"))
strcat(gecici,"\\");
strcat(gecici,file_name);
FILE *temp;
//temp=fopen (gecici,"w+b");
//fptrx = fopen(dosya_ismi, "r+b");


if((temp=fopen (gecici,"rb"))!=NULL)
{
  char hata[60];
  strcpy(hata,read_msg(404).out);
  key=hata_mesaji(&hata[0]);
  fclose(temp);
  if(key=='N'||key=='n')
                        return 0;
}


temp=fopen (gecici,"w+b");
fptrx = fopen(dosya_ismi, "r+b");

fseek(fptrx, 0L, SEEK_SET);
fseek(temp, 0L, SEEK_SET);
i=0;
                                          //filepos=(pos[y-2]+x-1);
while(!feof(fptrx)){
     //if (satir==22)break;
     chr=fgetc(fptrx);
      if (chr=='\n')
                   {
                     fwrite(&strSatir, i, 1, temp);fputc('\n', temp);
                     strset(strSatir,'\0');i=0;satir2++;
                 }
            else
                 {
                     strSatir[i]=chr;i++;
                 }
      }//while

fclose(fptrx);
fclose(temp);
degisiklik=0;
strcpy(yazilan_isim,file_name);
baslik_yaz();
satir_oku(1);
return 0;
}
return 0;
}

void kaydet()
{
int satir2=1;
int satir=1;
char chr;
int i=0;
FILE *temp;
if ((fptrx = fopen(dosya_ismi,"r+b"))!= NULL)
{
temp=fopen (gecici,"w+b");
//fptrx = fopen(dosya_ismi,"r+b" );
fseek(fptrx, 0L, SEEK_SET);
/*while(!feof(fptrx)){
     chr=fgetc(fptrx);
      if (chr=='\n')
                   {
                     if(satir2>=1)
                     {
                     fgetpos(fptrx, &pos[satir]);
                     fwrite(&strSatir, i, 1, temp);fputc('\n', temp);}
                     strset(strSatir,'\0');i=0;satir2++;
                 }
            else
                 {strSatir[i]=chr;i++;}
      }//while*/
			while(!feof(fptrx)){
     //if (satir==22)break;
     chr=fgetc(fptrx);
      if (chr=='\n')
                   {
                     fwrite(&strSatir, i, 1, temp);fputc('\n', temp);
                     strset(strSatir,'\0');i=0;satir2++;
                 }
            else
                 {
                     strSatir[i]=chr;i++;
                 }
      }//while

fclose(fptrx);
fclose(temp);
degisiklik=0;
satir_oku(1);
}
else
{
  char hata[50];
  strcpy(hata,read_msg(57).out);//" FILE CANT OPEN... ");57
  hata_mesaji(&hata[0]);
}


}

int satir_oku(int baslangic)
{
bassatir=baslangic;
//clrscr();
int satir2=1;
int satir=1;
char chr;
    int i=0;
ekran_sil();
if(strlen(dosya_ismi)<1)
                    {
/*                    menu();
                    cerceve(20,11,60,13,RED);
                    gotoxy(23,12);textcolor(LIGHTGREEN);
                    cprintf(" F1 Tusuna Basarak Dosya Acmalisiniz.");
                    getch();
                    clrscr();menu();*/
                    menu();
                    baslik_yaz();
                    }
else {
   if ((fptrx = fopen(dosya_ismi, "rt")) == NULL)
   {
      fprintf(stderr, "Cannot open input file.\n");
      return 1;
   }
fseek(fptrx, 0L, SEEK_SET);
toplamsatir=0;
while(!feof(fptrx))
{
 chr=fgetc(fptrx);
 if (chr=='\n'){toplamsatir++;}
 i++;
}//while
fseek(fptrx, 0L, SEEK_SET);
//menu();//burasi
i=0;

while(!feof(fptrx)){
     if (satir==22)break;
     if(i>76)chr='\n';else
     chr=fgetc(fptrx);
      if (chr=='\n'){
                     if(satir2>=baslangic){
                     fgetpos(fptrx, &pos[satir]);
                     gotoxy(2,satir+1);textcolor(15);
                     cprintf("%s \n",strSatir);satir++;
                     }
                     strset(strSatir,'\0');i=0;satir2++;}
      else{strSatir[i]=chr;i++;}
}//while

scroll(baslangic,toplamsatir);
fclose(fptrx);
}
return 1;
}

void convert(void)
{
////////////////////////////////////////////////////////////////////////////////////////
FILE *fptrx;
if(strlen(dosya_ismi)<1)
                    {
                    char hata[40];
                    strcpy(hata,read_msg(405).out);//" PRESS F1 TO OPEN FILE.");
                    hata_mesaji(&hata[0]);
                    }
else
{
if((fptrx=fopen(parameters.filename,"rt"))!=NULL)
{
fseek(fptrx, 0L, SEEK_SET);
fread(&parameters, sizeof(parameters), 1, fptrx);
int k=0;
for(int i=0;i<parameters.listbox[0].itemindex;i++){
           if(strcmp(parameters.listbox[0].item[i],"")!=0){
					  replace(1,parameters.listbox[0].item[i],parameters.listbox[1].item[i]);
            k++;
						}
}
parameters.listbox[1].itemindex=parameters.listbox[0].itemindex=k;
/*
div_t x;
int i=0;long int satir=0;char chr;
char strSatir[30]="";
char str1[30]="";
char str2[30]="";
i=0;
long int satir2=0;

 while(!feof(fptrx)){
     x=div(satir,2);
     chr=fgetc(fptrx);
      if (chr=='\n'){
                     if(x.rem==0){
                     strcpy(str1,strSatir);
                     }
                     else{
                     strcpy(str2,strSatir);
                     }
                     strset(strSatir,'\0');i=0;satir++;
                     if(strlen(str1)>0&&strlen(str2)>0)
                        {
                        replace(1,str1,str2);
                        strset(str1,'\0');strset(str2,'\0');
                        }
                     if(satir>0&&x.rem!=0)satir2++;
                     }
      else{strSatir[i]=chr;i++;}
   }//while
*/
fclose(fptrx);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
star_satir_aktif=1;
sadelestir(0);
star_satir_aktif=0;
sadelestir(2);//}
if(parameters.satirno_yaz==1){sadelestir(1);}
sadelestir(2);
sadelestir(3);
satir_oku(1);
}

}

int main(void)
{

int secim,x=0;
clrscr();
_setcursortype(0);
ayar_oku();
getcwd(kokdizin,80);
strcpy(yol,kokdizin);
cerceve(1,1,79,25,RED,0);
menu();
baslik_yaz();


while(x!=2){
        switch(secim=kbhits())
         {
                   case PG_UP : if(bassatir-21>0){satir_oku(bassatir-21);gotoxy(wherex(),wherey());}break;
                   case PG_DN : if(bassatir+21<toplamsatir){satir_oku(bassatir+21);gotoxy(wherex(),wherey());}break;
                   case 327   : satir_oku(1);gotoxy(wherex(),wherey());break;//HOME
                   case 335   : if(toplamsatir>21){satir_oku(toplamsatir-20.);gotoxy(wherex(),wherey());}break;//END
                   case F1    :
									 DropDownMenu(2,17,19,23," FILE ");break;
                   case F2    : replace_penceresi();satir_oku(bassatir);break;
                   case F3    : DropDownMenu(28,18,53,23," OPERATIONS");break;
                   case F8    : convert();break;
                   case F9    : if(parameters.dil==0)parameters.dil=1;else parameters.dil=0;
																menu();baslik_yaz();
																break;
                   case F5    : settings();
                                break;

        /*           case F7    :strcpy(isim,"frx ");
                               strcat(isim,yazilan_isim);
                               system(isim);_setcursortype(0);
                                cerceve(1,1,79,25,RED,0);
                                menu();
                                baslik_yaz();satir_oku(1);

                                break;
          */
                   case 'u'   :
                   case 'U'   : if(strlen(dosya_ismi)!=0){strcpy(dosya_ismi,yazilan_isim);dosya_ac();}break;
                   case F10   : if(degisiklik){
                                if(CloseQuery()){
                                textbackground(BLACK);
                                textcolor(LIGHTGRAY);
                                clrscr();
                                ayar_kaydet();
                                return 0;}}
                                else{ayar_kaydet();
                                     textbackground(BLACK);
                                     textcolor(LIGHTGRAY);
                                     clrscr();x=2;}
                                break;
                   default    :if(secim==-5){x=2;};
            }
    }

return 0;
}

void replace_penceresi()
{
int i,j;
_setcursortype(2);
gettext(5, 10, 70, 20, buffer);
for(i=10;i<=20;i++){
  for(j=5;j<=70;j++){gotoxy(j,i);cprintf(" ");}}
cerceve(5,10,70,20,RED,0);
gotoxy(30,10);
textcolor(LIGHTGREEN);
textbackground(1);
cprintf("   REPLACE   ");
//cprintf(read_msg(380).out);
gotoxy(15,18);
textcolor(RED);
textbackground(LIGHTGRAY);
cprintf("  ENTER ");cprintf(read_msg(380).out);cprintf("  ");
gotoxy(40,18);
cprintf("    ESC ");cprintf(read_msg(395).out);cprintf("    ");
gotoxy(8,12);
textbackground(0);
textcolor(GREEN);
cprintf(read_msg(379).out);
cprintf("       : [.....................................] ");
if(strlen(historysec[0])>0){gotoxy(26,12);cprintf("%s",historysec[0]);}
gotoxy(8,14);
cprintf(read_msg(380).out);
cprintf(" : [.....................................] ");
if(strlen(historykon[0])>0){gotoxy(26,14);cprintf("%s",historykon[0]);}
gotoxy(8,16);
cprintf(read_msg(381).out);
if(sozcuk==0){cprintf(": [  ]");}else{cprintf(": [ X ]");}

textcolor(GREEN);
gotoxy(26,12);
strcpy(aranan,stringal(26,12,37,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789abcdefghijklmnopqrstuvwxyz.:_-=)(&%*^",1));
gotoxy(26,14);
strcpy(konulacak,stringal(26,14,37,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789abcdefghijklmnopqrstuvwxyz.:_-=)(&%*^",2));
gotoxy(27,16);
char szc[1];
strcpy(szc,stringal(27,16,1,"X",4));

for(i=10;i<=20;i++){
  for(j=5;j<=70;j++){gotoxy(j,i);cprintf(" ");}}
puttext(5, 10, 70, 20, buffer);
if(strlen(aranan)>0&&strlen(konulacak)>0)
{
for(i=5;i>0;i--){
strcpy(historysec[i],historysec[i-1]);
}
strcpy(historysec[0],aranan);
for(i=5;i>0;i--){
strcpy(historykon[i],historykon[i-1]);
}
strcpy(historykon[0],konulacak);
replace(1,aranan,konulacak);
ayar_kaydet();
}
_setcursortype(0);
}
void baslik_yaz(void)
{
if(toplamsatir!=0){
textbackground(YELLOW);
gotoxy(55,23);textcolor(LIGHTGREEN);
cprintf(read_msg(396).out);
cprintf(": %li ",toplamsatir);textbackground(0);}
     cerceve(1,1,79,25,RED,0);
 char c;int y;
textcolor(WHITE);
 for(y=2;y<=22;y++)
 {gotoxy(79,y);
  if(y==2){c=30;}else if(y==22){c=31;}
  else{c=176;}
  cprintf("%c",c);
 }
gotoxy(79,3);cprintf("%c",219);

     gotoxy(35,1);
     cprintf("%s",yazilan_isim);
}
int menu(){
cerceve(1,23,79,25,RED,0);
cerceve(1,1,79,25,RED,0);
     textcolor(15);
gotoxy(3,24);
cprintf(read_msg(399).out);//MENU
/*  cprintf("F1.");cprintf(read_msg(373).out);cprintf(" ");//FILE
  cprintf("F2.");cprintf(read_msg(378).out);cprintf(" ");//Replace   ");
  cprintf("F3.");cprintf(read_msg(383).out);cprintf(" ");//Operations   ");
  cprintf("F5.");cprintf(read_msg(388).out);cprintf(" ");//Settings   ");
  cprintf("F8.");cprintf(read_msg(393).out);cprintf(" ");//Convert    ");
  cprintf("F9.");cprintf(read_msg(397).out);cprintf(" ");//Convert    ");
  cprintf("F10.");cprintf(read_msg(4).out);//EXT");*/

textcolor(LIGHTGRAY);
return 0;
}

//----------------------------- SADELESTIRME -------------------------------//
void sadelestir(int convert_type)// 0 - Sadece Kod
{                                // 1 - Satir no sil
                                 // 2 - Bosluk birak
                                 // 3 - Convert to Ajan
long int satir2=1;
int i=0;
char chr;
start.x=0;start.y=0;start.z=0;gtip=0;
end.x=0;end.y=0;end.z=0;RADYUS=0;

FILE *temp;

temp  = fopen("temp002.cam","wt");
fptrx = fopen("temp.cam", "r+b");
fseek(fptrx, 0L, SEEK_SET);
      gotoxy(40,12);textcolor(RED);cprintf("FILE CONVERTING ! ! !");
      gotoxy(40,13);cprintf("PLEASE WAIT...");
while(!feof(fptrx)){
     chr=fgetc(fptrx);
      if (chr=='\n')
                   {
                     if(star_satir_aktif==1)
                     {
                     if(satir2>parameters.start_satir){
                          if(convert_type==0){kodlar();}
                     else if(convert_type==1){satirno();}
                     else if(convert_type==2){bosluk();}
                     else if(convert_type==3){analiz();}
                     if(strlen(yeniSatir)>1){
                     strcat(yeniSatir,"\n");
                     fwrite(&yeniSatir, strlen(yeniSatir), 1, temp);//fputc('\n', temp);
                     strset(yeniSatir,'\0');
                                             }//if(strlen(yeniSatir)>1)
                                                                         }//if(satir2>parameters.start_satir){
                     }
                     else
                     {
                     if(convert_type==0){kodlar();}
                     else if(convert_type==1){satirno();}
                     else if(convert_type==2){bosluk();}
                     else if(convert_type==3){analiz();}
                     if(strlen(yeniSatir)>1){
                     strcat(yeniSatir,"\n");
                     fwrite(&yeniSatir, strlen(yeniSatir), 1, temp);//fputc('\n', temp);
                     strset(yeniSatir,'\0');
                                          }//if(strlen(yeniSatir)>1)
                     }
                     strset(strSatir,'\0');i=0;satir2++;
                     if(satir2==parameters.start_satir)star_satir_aktif=0;
                 }
          else
                 {
                     strSatir[i]=chr;i++;
                 }
      }
fclose(temp);
fclose(fptrx);
degisiklik=1;
remove("temp.cam");
system("ren temp002.cam temp.cam");
strcpy(dosya_ismi,"temp.cam");
}

void analiz(void)
{
int i,j,sutun=0,sayi=0;
char ilkmi=1,kod[20][78]={""};
for(i=0;i<=20;i++){strcpy(kod[i],"");}
    for(j=0;j<=20;j++){
    for(i=sutun;i<strlen(strSatir);i++)
    {
     if(ilkmi==1){if(strSatir[i]!=' '){kod[j][sayi]=strSatir[i];ilkmi=0;sayi++;}}
          else{//ilkmi =0 ise
               if ((strSatir[i]>=48&&strSatir[i]<=57)//0..9 rakam ise
                   ||(strSatir[i-1]>=65&&strSatir[i-1]<=90)//Bir înceki Harf ise
                   ||(strSatir[i-1]>=97&&strSatir[i-1]<=122)//Bir înceki Harf ise
                   ||(strSatir[i]==46)//. ise
                   ||(strSatir[i]==45))//- ise
                      {kod[j][sayi]=strSatir[i];sayi++;}
                      else
                      {
                      ilkmi=1;sayi=0;break;
                      }
                }
      sutun++;  }
      }
ilkmi=1;
int sig=17;
char end_var=0;
  start.x=end.x;start.y=end.y;start.z=end.z;
  for(i=0;i<=20;i++)
  {
     if(strlen(kod[i])>1&&((kod[i][0]=='F'||kod[i][0]=='G'||kod[i][0]=='N'||kod[i][0]=='K'||kod[i][0]=='Q'||//14_apr_05 K,Q ve D eklendi
            kod[i][0]=='X'||kod[i][0]=='I'||kod[i][0]=='J'||kod[i][0]=='Y'||kod[i][0]=='W'||kod[i][0]=='D'||
            kod[i][0]=='Z'||kod[i][0]=='U'||kod[i][0]=='H'||kod[i][0]=='M'||
            kod[i][0]=='O'||kod[i][0]=='T'||kod[i][0]=='S'||kod[i][0]=='L'||
            kod[i][0]=='P'||kod[i][0]=='R')&&((kod[i][1]>=48&&kod[i][1]<=57)||(kod[i][1]==45||kod[i][1]=='.'))/*||(kod[i][1]==45||kod[i][1]=='.'))*/)
        ||((kod[i][0]=='I'||kod[i][0]=='J'||kod[i][0]=='X'||kod[i][0]=='W'||kod[i][0]=='Y'||kod[i][0]=='U'||kod[i][0]=='Z')
             &&kod[i][1]==45&&(kod[i][2]>=48&&kod[i][2]<=57))
        ||(strstr(kod[i],"MSG")!=NULL))
      {
          if((parameters.satirno_yaz==1&&kod[i][0]!='N')||(parameters.satirno_yaz==0))
          {
                      if(strcmp(kod[i],"G01")==0||strcmp(kod[i],"G1")==0){gtip=0;}
                      if(strcmp(kod[i],"G02")==0||strcmp(kod[i],"G2")==0){gtip=2;}
                      else if(strcmp(kod[i],"G03")==0||strcmp(kod[i],"G3")==0){gtip=3;}

                      if(kod[i][0]=='X'||kod[i][0]=='Y'||kod[i][0]=='Z'||kod[i][0]=='R'||kod[i][0]=='I'||kod[i][0]=='J')
                      {
                              if(kod[i][0]=='I'&&parameters.arc_tip==1)
                              {
                              I=atof(&kod[i][1]);
                              I=I*-1.;
                              gcvt(I, sig, &kod[i][1]);
                              }
                              if(kod[i][0]=='J'&&parameters.arc_tip==1)
                              {
                              J=atof(&kod[i][1]);
                              J=J*-1.;gcvt(J, sig, &kod[i][1]);
                              }
                                   if(kod[i][0]=='X'){if(gtip!=0){end_var=1;}end.x=atof(&kod[i][1]);}
                              else if(kod[i][0]=='Y'){if(gtip!=0){end_var=1;}end.y=atof(&kod[i][1]);}
                              else if(kod[i][0]=='Z'){if(gtip!=0){end_var=1;}end.z=atof(&kod[i][1]);}
                              if(kod[i][0]=='R'&&RADYUS==0){RADYUS=atof(&kod[i][1]);}
                      }
              if (ilkmi==1)
                        {
                        strcat(yeniSatir,kod[i]);ilkmi=0;
                        }
                        else
                        {
                        if(parameters.bosluk_koy==1){strcat(yeniSatir," ");}
                        strcat(yeniSatir,kod[i]);
                        }
            }//if(kod[i][0]!='N')
        }//if(strlen(kod[i])>1&&((kod[i][0]=='G'||kod[i][0]=='X'||kod[i][0]=='I'||kod[i][0]=='J'||kod[i][0]=='Y'||kod[i][0]=='Z'||kod[i][0]=='U'||kod[i][0]=='H'||kod[i][0]=='M'||kod[i][0]=='O'||kod[i][0]=='T'||kod[i][0]=='S'||kod[i][0]=='L'||kod[i][0]=='P'||kod[i][0]=='R')
  }

    if(RADYUS!=0&&gtip!=0){
                  convert_ijk();RADYUS=0;
                    if(gtip==2){strcpy(yeniSatir,"G02");}
                    else if(gtip==3){strcpy(yeniSatir,"G03");}

                    if(end_var==1){
                  	sprintf(kod[0],"%.3lf",end.x);
                    strcat(yeniSatir," X");strcat(yeniSatir,kod[0]);
                  	sprintf(kod[0],"%.3lf",end.y);
                    strcat(yeniSatir," Y");strcat(yeniSatir,kod[0]);
                                  }

                    if(I!=0){
                  	sprintf(kod[0],"%.3lf",I);
                    strcat(yeniSatir," I");strcat(yeniSatir,kod[0]);
                          }
                    if(J!=0){
                  	sprintf(kod[0],"%.3lf",J);
                    strcat(yeniSatir," J");strcat(yeniSatir,kod[0]);
                             }

                    for(i=0;i<20;i++){
                                      if(kod[i][0]=='F'||kod[i][0]=='S')
                                        { strcat(yeniSatir," ");
                                          strcat(yeniSatir,kod[i]);}
                                     }

//gtip=0;
//                   end.x=0;end.y=0;end.z=0;
end_var=0;
                 }

}//end of analiz()

//------------------------REPLACE ---------------------------------------//
void degistir3(char *aranan,char *konulacak)
{
char *str1;
int i,j,sutun=0,sayi=0;
char ilkmi=1,kod[20][78]={""};
char *illegal="ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz:_;'=)(&%^\"";
char kodmu=0;
str1=strstr(strSatir,aranan);
if(str1!=NULL&&konulacak[0]=='*')
{
strcpy(yeniSatir,"");
}

else if(str1!=NULL)
  {
   for(j=0;j<=20;j++){
    for(i=sutun;i<strlen(strSatir);i++)
    {
     if(ilkmi==1){if(strSatir[i]!=' '){kod[j][sayi]=strSatir[i];ilkmi=0;sayi++;
                      if ((strSatir[i+1]>=48&&strSatir[i+1]<=57)||strSatir[i+1]==45||strSatir[i+1]==46){kodmu=1;}
                      else{kodmu=0;}
                      }}
          else{  if(kodmu==1){
                            if(strchr(illegal,strSatir[i])==0)
                            {kod[j][sayi]=strSatir[i];sayi++;}
                            else{ilkmi=1;sayi=0;break;}
                      }
                      if(kodmu==0){
                            if(strSatir[i]!=';'&&strSatir[i-1]!=';')
                            {kod[j][sayi]=strSatir[i];sayi++;}
                            else{ilkmi=1;sayi=0;break;}
                      }
                }
      sutun++;  }
      }
ilkmi=1;
char *str1;
char yedek_kod[78]="";
 for(j=0;j<20;j++)
  {
 str1=strstr(kod[j],aranan);
 if(str1!=NULL)
         {
          for(i=0;i<=strlen(kod[j])-strlen(str1);i++)
          strcat(yedek_kod,konulacak);
          int sutun;
          sutun=strlen(yedek_kod);
          for(i=(strlen(kod[j])-strlen(str1))+strlen(aranan);i<strlen(kod[j]);i++)
         {yedek_kod[sutun]=kod[j][i];sutun++;}
         strcpy(kod[j],yedek_kod);
         }
   }
  for(i=0;i<20;i++)
  {
          if(strlen(kod[i])>0){
              if (ilkmi==1)
                        {
                        strcat(yeniSatir,kod[i]);ilkmi=0;
                        }
                        else
                        {
                        strcat(yeniSatir,kod[i]);
                        }
                    }
   }
}
else
{
strcpy(yeniSatir,strSatir);
}
}

void degistir2(char *aranan,char *konulacak)
{
char *str1;
int i,j,sutun=0,sayi=0;
char ilkmi=1,kod[20][78]={""};
char *illegal="ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz:_;'=)(&%^\"";
char kodmu=0;

str1=strstr(strSatir,aranan);
//   if(aranan[strlen(aranan)]=="*"){strcat(yeniSatir,"\n");strset(yeniSatir,'\0');}
if(str1!=NULL&&konulacak[0]=='*')//rev 0
{
strcpy(yeniSatir,"");
}
else if(str1!=NULL)
  {
    for(j=0;j<=20;j++){
    for(i=sutun;i<strlen(strSatir);i++)
    {
     if(ilkmi==1){if(strSatir[i]!=' '){kod[j][sayi]=strSatir[i];ilkmi=0;sayi++;
                      if ((strSatir[i+1]>=48&&strSatir[i+1]<=57)||strSatir[i+1]==45||strSatir[i+1]==46){kodmu=1;}
                      else{kodmu=0;}
                      }}
          else{  if(kodmu==1){
                            if(strchr(illegal,strSatir[i])==0)
                            {kod[j][sayi]=strSatir[i];sayi++;}
                            else{ilkmi=1;sayi=0;break;}
                      }
                      if(kodmu==0){
                            if(strSatir[i]!=';'&&strSatir[i-1]!=';')
                            {kod[j][sayi]=strSatir[i];sayi++;}
                            else{ilkmi=1;sayi=0;break;}
                      }
                }
      sutun++;  }
      }
char *ptr;int d=0,uz1=0,uz2=0,uz3=0,uz4=0;
char kod_sonu[20]="\0";
char kod_basi[20]="\0";
ilkmi=1;
 for(i=0;i<20;i++)
  {
   if((ptr=strstr(kod[i], aranan))!=NULL)
         {uz1=strlen(kod[i]);uz2=strlen(ptr);uz3=strlen(kod_basi);
         for(int k=0;k<(uz1-uz2);k++){kod_basi[k]=kod[i][k];}
         d=0;
         uz3=strlen(kod_basi);uz4=strlen(aranan);
         for( k=(uz3+uz4);k<uz1;k++){kod_sonu[d]=kod[i][k];d++;}
           if(uz3!=0)strcpy(kod[i],kod_basi);
           if(uz3!=0)strcat(kod[i],konulacak);else strcpy(kod[i],konulacak);
           strcat(kod[i],kod_sonu);

         }
   }
  for(i=0;i<20;i++)
  {
         if(strlen(kod[i])>0){
              if (ilkmi==1)
                        {
                        strcat(yeniSatir,kod[i]);ilkmi=0;
                        }
                        else
                        {
                        strcat(yeniSatir," ");
                        strcat(yeniSatir,kod[i]);
                        }
                    }
   }
}
else
{
strcpy(yeniSatir,strSatir);
}

}//degistir2



void replace(int baslangic,char *aranan,char *konulacak)
{
long int satir2=1,satir=1;
int i=0;
char chr;
FILE *temp;
temp=fopen ("temp002.cam","w+b");
fptrx = fopen("temp.cam", "r+b");
fseek(fptrx, 0L, SEEK_SET);
while(!feof(fptrx)){
     chr=fgetc(fptrx);
      if (chr=='\n')
                   {
                     if(satir2>=baslangic)
                     {
                     fgetpos(fptrx, &pos[satir]);

                     if(sozcuk==1){degistir2(aranan,konulacak);}
                     else{degistir3(aranan,konulacak);}
                     strcat(yeniSatir,"\n");
                     fwrite(&yeniSatir, strlen(yeniSatir), 1, temp);strset(yeniSatir,'\0');}
                     strset(strSatir,'\0');i=0;satir2++;
                 }
            else
                 {
                     strSatir[i]=chr;i++;
                 }
      }//while
fclose(fptrx);
fclose(temp);
degisiklik=1;
system("del temp.cam");
system("ren temp002.cam temp.cam");
}

int history(int x1,int y1,int x2,int y2,int gelen)
{
gettext(x1,y1,x2,y2,buffer);
incecerceve(x1,y1,x2,y2, GREEN,0);
ayar_oku();
gotoxy(x1+1,y1);
int i=0;
int charcolor=GREEN,reversecolor=BLACK;
int x=x1+1;
int key1, key2;
int nsec=0;
oldc=getfirstcolor(&c);
textcolor(charcolor);
textbackground(reversecolor);
 for(i=0;i<=5;++i)
 {if(gelen==1){
  if(strlen(historysec[i])>0)
  {  gotoxy(x1+1,y1+i);
  cprintf("%s",historysec[i]);
  nsec++;}}
  else if(gelen==2){
  if(strlen(historykon[i])>0)
  {  gotoxy(x1+1,y1+i);
  cprintf("%s",historykon[i]);
  nsec++;}}
 }
 highvideo();i=0;--nsec;
 do{
      gotoxy(x,i+y1);
      textcolor(reversecolor);
      textbackground(charcolor);
      if(gelen==1){cprintf("%s",historysec[i]);}else{cprintf("%s",historykon[i]);}
      textcolor(charcolor);
      textbackground(reversecolor);
      gotoxy(x,i+y1);
      key1=getch();
      if((key1!=13)&&(key1==0))
      {
      key2=getch();
         if((key2==80)&&(i<nsec)){//asagi
            if(gelen==1){cprintf("%s",historysec[i]);}else{cprintf("%s",historykon[i]);}
            ++i;
        }
      else if((key2==80)&&(i==nsec)){//asagi
            if(gelen==1){cprintf("%s",historysec[i]);}else{cprintf("%s",historykon[i]);}
          i=0;
      }
      else if((key2==72)&&(i>0)){  //yukari
            if(gelen==1){cprintf("%s",historysec[i]);}else{cprintf("%s",historykon[i]);}
          --i;
      }
      else if((key2==72)&&(i==0)){  //yukari
            if(gelen==1){cprintf("%s",historysec[i]);}else{cprintf("%s",historykon[i]);}
          i=nsec;
      }
      }
 }while (key1!=13&&key1!=27);
 putcolor(oldc);
 ++i;
puttext(x1,y1,x2,y2,buffer);
textbackground(0);
return i;
}
void incecerceve(int x1,int y1,int x2,int y2, int w_fcolor,int bcolor)
{
int i,j;
textcolor(w_fcolor);
   textbackground(bcolor);
   for(i=x1+1;i<=(x2-1);++i){
   for(j=y1+1;j<=(y2-1);++j){
    gotoxy(i,j);cprintf(" ");
   }}
//            }
if ((x2>x1)&&(y2>y1)){
   gotoxy(x1,y1);cprintf("%c",179);gotoxy(x2,y1);cprintf("%c",179);
   gotoxy(x1,y2);cprintf("%c",192);gotoxy(x2,y2);cprintf("%c",217);


   for(i=x1+1;i<=(x2-1);++i){
                             gotoxy(i,y2);cprintf("%c",196);
                             }
   for(i=y1+1;i<=(y2-1);++i){
                             gotoxy(x1,i);cprintf("%c",179);
                             gotoxy(x2,i);cprintf("%c",179);
                             }
}
}

void cerceve(int x1,int y1,int x2,int y2, int w_fcolor,int bcolor)
{
int i;
textcolor(w_fcolor);
   if(bcolor!=0){textbackground(bcolor);
   for(i=x1+1;i<=(x2-1);++i){
   for(int j=y1+1;j<=(y2-1);++j){
    gotoxy(i,j);cprintf(" ");
   }}            }
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

char *stringal(int x1,int y1,int uzunluk,char *legal,int gelen)
{
	int k,secim;char geri=1;
	char symtab[256]="";
	char al=0,xcursor[]=".";//€
       if(gelen==1){strcpy(symtab,historysec[0]);
                    al=strlen(historysec[0]);gotoxy(x1+al,y1);
                    }
       else if(gelen==2){strcpy(symtab,konulacak);al=strlen(konulacak);gotoxy(x1+al,y1);}
       else if(gelen==3){
                         strcpy(symtab,file_name);if(strlen(file_name)<8){al=strlen(file_name);}else{al=strlen(file_name)-1;}gotoxy(x1+al,y1);
                         }
       else if(gelen==9){
                         itoa(parameters.start_satir,symtab,10);if(strlen(symtab)<8){al=strlen(symtab);}else{al=strlen(symtab)-1;}gotoxy(x1+al,y1);
                         }

       else if(gelen==5){strcpy(xcursor," ");}
do{
		k=kbhits();
		if(k){
    if(k==DOWN){if(gelen==1){secim=history(25,13,63,19,gelen);
                        		 gotoxy(8,12);cprintf("         FIND  : [.....................................] %c",31);
                             gotoxy(26,12);strcpy(symtab,historysec[secim-1]);al=strlen(historysec[secim-1]);cprintf("%s",symtab);gotoxy(x1+al,y1);
                             gotoxy(8,14);cprintf("      REPLACE  : [.....................................] ");
                             gotoxy(26,14);cprintf("%s",historykon[secim-1]);strcpy(konulacak,historykon[secim-1]);gotoxy(x1+al,y1);
                             }
                if(gelen==2){secim=history(25,15,63,21,gelen);
                gotoxy(8,14);cprintf("      REPLACE  : [.....................................] ");

                             gotoxy(26,14);strcpy(symtab,historykon[secim-1]);al=strlen(historykon[secim-1]);cprintf("%s",symtab);gotoxy(x1+al,y1);
                             }
               }
			if(k>256){
				continue;
				}
			if(k==27){ symtab[0]='\0';key=27;break;}
			if(k==13) {key=13;break;}
      if(k==32){
                            if(gelen==4)
                            {if(sozcuk==0){strcpy(symtab,"X");sozcuk=1;}
                            else{strcpy(symtab," ");sozcuk=0;}
                            gotoxy(27,16);
                            }
                }
      if(k==9) {if(gelen==3){break;}}
      if(k==8)
				if(al>0){
        if(gelen==3&&al+1==uzunluk&&geri==1){
//          cprintf(xcursor);//}
//					al--;
          *(symtab+al)='\0';geri=0;

          }

        else{
         // cprintf(xcursor);//}
					al--;
          *(symtab+al)='\0';}
          }
				else{
   	 			continue;
					}
          cprintf(xcursor);
			if(k!=8){
        if(strlen(legal)){
					if(strchr(legal,k)!=0){*(symtab+al++)=k;}
					}
        else{ *(symtab+al++)=k;}
        }
      gotoxy(x1,y1);
      cprintf("%s",symtab);
  if(gelen!=4){if(al!=uzunluk){cprintf(xcursor);}}
        gotoxy(x1+al,y1);
  if(gelen==3&&al==uzunluk){al--;gotoxy(x1+al,y1);geri=1;}
//        gotoxy(x1+al,y1);//}
			}//if(k)
		}while(al<uzunluk);
	k=strlen(symtab);if(symtab[k]==' ') while(symtab[k]!=' ') --k;
	symtab[k]='\0';
	return symtab;
}

int dosya_penceresi(char kayit)
{
 struct ffblk ffblk[1],FileList[1];
 int FileNumber = 0,DirNumber = 0,i=0,j=0,k=0,chr=0,VisCurPos=0,RealCurPos=0,OldCursor=0,LineStartPos=1;
 unsigned int QuitFromFileWindow = 0;
 char FileType = 3,krk=0;
 char ChoseeFileType=1,UnRepeat=0,SortType=0,done,refresh=1,ch;
char FileNameList[20][13]={""},gecici[13]="",FileExtension[3],isim[7],FileExtensionCnc[3];
int uzunluk=0,l=0,toplam=0,toplamdizin=0,bayrak=0,sayi=0;
char bspc=0,tab=0;
unsigned int xhandle=0;
gettext(20, 2, 65, 21, buffer);
strcpy(file_name,"");
for(i=2;i<=21;i++){
  for(j=20;j<=65;j++){gotoxy(j,i);cprintf(" ");}}
incecerceve(20,3,33,21,RED,0);
for(j=20;j<=65;j++){textbackground(YELLOW);gotoxy(j,3);cprintf(" ");textbackground(BLACK);}
cerceve(20,2,65,21,RED,0);
  for(j=21;j<=32;j++){textbackground(WHITE);gotoxy(j,4);cprintf(" ");textbackground(BLACK);}
gotoxy(37,2);
if(kayit==0){
cprintf(read_msg(373).out);cprintf(" ");cprintf(read_msg(375).out);}
else{
cprintf(read_msg(377).out);gotoxy(34,4);

cprintf(read_msg(294).out);
textcolor(WHITE);
gotoxy(34,5);cprintf("[........]");
}
     while(1){
if(tab==1){_setcursortype(1);
//strcpy(file_name,"");
strcpy(file_name,stringal(35,5,8,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789abcdefghijklmnopqrstuvwxyz._-=)(&%*^",3));
tab=0;
_setcursortype(0);
if(key==27){QuitFromFileWindow = 1;
												 FileType = 1;ch=1;key=0;}
else if(key==13)
     {
      QuitFromFileWindow = 1;key=0;
                        break;
     }
}

if(ChoseeFileType==1){
                      strcpy(FileExtension ,"CAM");
                      strcpy(FileExtensionCnc ,"CNC");
if(xhandle)  xmfree(xhandle);
  if (!xmsinstalled)
  {
    puts("\nCan't use memory: No XMS Driver Installed!"); return (0);
  }
  if (!(xhandle = xmalloc(512)))//12192 dosya kapasitesi simdilik yeterli
  {
    pxmserror("\nCan't use memory:");
    return (0);
  }
else{
             chdir(yol);
             if(strcmp(yol,"C:\\"))strcat(yol,"\\");
             strcat(yol,"*.");

     FileNumber=0;

             done=findfirst(yol,&ffblk[0],FA_DIREC);
          while(!done){
           if(ffblk[0].ff_attrib==FA_DIREC&&strcmp(ffblk[0].ff_name, ".")!=0 ){
           strcat(ffblk[0].ff_name,"\\");
           ctoxm(xhandle,1.*sizeof(ffblk)*FileNumber,&ffblk,sizeof(ffblk)-1);
           FileNumber++;}
           done =findnext(&ffblk[0]);}//while(!done)
           DirNumber=FileNumber;

      for(i=33;i<=90;i++){
         if(i!=42&&i!=47&&i!=63) sprintf(isim,"%c*.%s",i,FileExtension);
          done =findfirst(isim,&ffblk[0],0);
          while(!done){
               ctoxm(xhandle,1.*sizeof(ffblk)*FileNumber,&ffblk,sizeof(ffblk)-1);
               done =findnext(&ffblk[0]);
               FileNumber++;}//while(!done)
           }//for//
      for(i=33;i<=90;i++){
         if(i!=42&&i!=47&&i!=63) sprintf(isim,"%c*.%s",i,FileExtensionCnc);
          done =findfirst(isim,&ffblk[0],0);
          while(!done){
               ctoxm(xhandle,1.*sizeof(ffblk)*FileNumber,&ffblk,sizeof(ffblk)-1);
               done =findnext(&ffblk[0]);
               FileNumber++;}//while(!done)
           }//for//

getcwd(yol,100);
//********    SIRALAMALAR     ********
       if(FileNumber>1){
//*********** NAME,DATE,SIZE GORE SIRALAMA
                 if(SortType!=3){
                     if(strcmp(yol,"C:\\")==0){l=0;}else{l=1;}
                        for(j=l;j<DirNumber;j++)
                        {
                            xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                            for(k=j+1;k<DirNumber;k++)
                            {
                            xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                                if((SortType==0)&&strcmp(FileList[0].ff_name,ffblk[0].ff_name)>=0
                                ||(SortType==1)&&(FileList[0].ff_fdate<ffblk[0].ff_fdate||(FileList[0].ff_fdate==ffblk[0].ff_fdate)&&(FileList[0].ff_ftime<ffblk[0].ff_ftime))
                                ||(SortType==2)&&(FileList[0].ff_fsize<ffblk[0].ff_fsize))
                                {
                                ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                FileList[0]=ffblk[0];
                                ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                }//if((SortType==0)&&(FileList.ff_name>ffblk.ff_name)||
                            }//for(k=j+1;k<FileNumber;k++){
                        }//for(j=0;j<FileNumber;j++)

                        for(j=DirNumber;j<FileNumber;j++)
                        {
                             xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                             for(k=j+1;k<FileNumber;k++)
                             {
                             xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                                 if((SortType==0)&&strcmp(FileList[0].ff_name,ffblk[0].ff_name)>=0
                                 ||(SortType==1)&&(FileList[0].ff_fdate<ffblk[0].ff_fdate||(FileList[0].ff_fdate==ffblk[0].ff_fdate)&&(FileList[0].ff_ftime<ffblk[0].ff_ftime))
                                 ||(SortType==2)&&(FileList[0].ff_fsize<ffblk[0].ff_fsize)){
                                 ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                 FileList[0]=ffblk[0];
                                 ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                 }//if((SortType==0)&&(FileList.ff_name>ffblk.ff_name)||
                              }//for(k=j+1;k<FileNumber;k++){
                        }//for(j=0;j<FileNumber;j++)
                 }//if SortType!=3
                 else
                 {
//************ KARAKTERE GORE SIRALAMA  //09//Dec//04 fahreddin
                if(strcmp(yol,"C:\\")==0){l=0;}else{l=1;}
                toplam=0;toplamdizin=0;
//****** Girilen karaktere uygun kelimeler yukarç alçnçyor.
                   for(j=l;j<FileNumber;j++)
                   {
                   xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                       if(j==1){if(FileList[0].ff_name[0]==gecici[0]){toplam+=1;}}
                       for(k=j+1;k<FileNumber;k++)
                       {
                       xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                             for(i=0;i<strlen(gecici);i++){if(ffblk[0].ff_name[i]==gecici[i]){bayrak+=1;}}
                                   if(bayrak==strlen(gecici))
                                         {
                                         ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                         FileList[0]=ffblk[0];
                                         ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                         if(j==1){if(ffblk[0].ff_name[0]==gecici[0]){toplam+=1;}}
                                         }
                              bayrak=0;
                         }
                   }


//*************Bulunan stringlerin dizin ismi olanlarç yukarç alçniyor.

                   for(j=l;j<toplam;j++)
                   {xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                     if(j==1){if(FileList[0].ff_name[0]==gecici[0]){toplamdizin+=1;}}
                     for(k=j+1;k<=toplam;k++)
                       {xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
//                        for(i=0;i<strlen(gecici);i++){if(ffblk[0].ff_name[i]==gecici[i]){bayrak+=1;}}
                             if(ffblk[0].ff_attrib==FA_DIREC)//ffblk[0].ff_name[strlen(ffblk[0].ff_name)-1]=='\\')
                                         {ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                          FileList[0]=ffblk[0];
                                          ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                          if(j==1){if(ffblk[0].ff_name[0]==gecici[0]){toplamdizin+=1;}}
                                         }//bayrak=0;
                        }}

//Dizinler harf sçrasçna diziliyor
                   if(toplamdizin>1){
                   for(j=l;j<toplamdizin;j++)
                   {xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                     for(k=j+1;k<toplamdizin;k++)
                       {
                       xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                       if(strcmp(FileList[0].ff_name,ffblk[0].ff_name)>=0)
                                 {ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                  FileList[0]=ffblk[0];
                                  ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                  }
                        }
                     }}
//Isimler harf sirasina diziliyor.
               for(j=toplamdizin+1;j<toplam;j++)
                 {xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                  for(k=j+1;k<toplam;k++)
                   {xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
//                     for(i=0;i<strlen(gecici);i++){if(ffblk[0].ff_name[i]==gecici[i]){bayrak+=1;}}
                        if(strcmp(FileList[0].ff_name,ffblk[0].ff_name)>=0)
                                       {ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                          FileList[0]=ffblk[0];
                                          ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                          //if(j==1){if(ffblk[0].ff_name[0]==gecici[0]){toplamdizin+=1;}}
                                         }//bayrak=0;
                        }
                     }

             //DIGERLERI
//Geri kalan isimlerde dizin olanlar yukarç alçnçyor
                   for(j=toplam+1;j<FileNumber;j++)
                   {
                   xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                       for(k=j+1;k<FileNumber;k++)
                       {
                       xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                       if(ffblk[0].ff_attrib==FA_DIREC)
                                         {
                                         ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                         FileList[0]=ffblk[0];
                                         ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                          }
                        }
                     }
//Geri kalan isimlerde dizin harf sirasina diziliyor
                  sayi=DirNumber-toplamdizin;
                   for(j=toplam+1;j<toplam+sayi;j++)
                   {xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                     for(k=j+1;k<toplam+sayi;k++)
                       {xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                             if(strcmp(FileList[0].ff_name,ffblk[0].ff_name)>=0)
                                         {ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                          FileList[0]=ffblk[0];
                                          ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                         }
                        }
                     }

//Geri kalan isimler harf sirasina diziliyor
                   for(j=toplam+sayi+1;j<FileNumber;j++)
                   {xmtoc(FileList,xhandle,1.*sizeof(FileList)*j,sizeof(FileList)-1);
                     for(k=j+1;k<FileNumber;k++)
                       {xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*k,sizeof(ffblk)-1);
                             if(strcmp(FileList[0].ff_name,ffblk[0].ff_name)>=0)
                                         {ctoxm(xhandle,1.*sizeof(FileList)*k,FileList,sizeof(FileList)-1);
                                          FileList[0]=ffblk[0];
                                          ctoxm(xhandle,1.*sizeof(FileList)*j,FileList,sizeof(FileList)-1);
                                         }
                        }
                    }



                   }//if SortType!=3 else
       }//if(FileNumber>FirstCharNo+1)
  }//else
  ChoseeFileType=0;
 }//ChoseeFileType==1

if(refresh==1||(RealCurPos-VisCurPos)!=LineStartPos){
LineStartPos=RealCurPos-VisCurPos;
if(LineStartPos<0){LineStartPos=0;RealCurPos=VisCurPos;}
{
for(i=5;i<=20;i++){
  for(j=21;j<=32;j++){gotoxy(j,i);cprintf(" ");}}
}
int satir=0;

for(i=LineStartPos;i<LineStartPos+16;i++){
 xmtoc(ffblk,xhandle,1.*sizeof(ffblk)*i,sizeof(ffblk)-1);
if(i<FileNumber){
strcpy(FileNameList[i-LineStartPos],ffblk[0].ff_name);
FileNameList[i-LineStartPos][12]='\x0';
for(j=21;j<=32;j++){gotoxy(j,satir+5);cprintf(" ");}
gotoxy(21, satir+5);satir++;
textcolor(WHITE);
cprintf(FileNameList[i-LineStartPos]);
                  }
}//for
}//if((RealCurPos-VisCurPos)!=LineStartPos)
        if(refresh == 1||OldCursor!=VisCurPos){
		     if(UnRepeat==0){
              for(j=21;j<=32;j++){gotoxy(j,OldCursor+5);cprintf(" ");}
              gotoxy(21,OldCursor+5);
              cprintf(FileNameList[OldCursor]);
              textbackground(BLACK);
                        }
             OldCursor=VisCurPos;
             for(j=21;j<=32;j++){gotoxy(j,OldCursor+5);cprintf(" ");}
              gotoxy(21,OldCursor+5);
              textbackground(GREEN);
              cprintf(FileNameList[OldCursor]);
              textbackground(BLACK);
	  	        refresh = 0; UnRepeat=0;
               for(j=21;j<=64;j++){textbackground(YELLOW);gotoxy(j,3);cprintf(" ");textbackground(BLACK);}
               int uz=strlen(yol);gotoxy(21,3);textbackground(YELLOW);
               if(uz>44){for(i=uz-44;i<strlen(yol);i++){cprintf("%c",yol[i]);}}else{cprintf("%s",yol);}
               textbackground(0);
                                    }


chdir(kokdizin);


        switch(chr=kbhits())  {
               case F1 :SortType = 0;RealCurPos=0;ChoseeFileType=1;break;//ByName
               case F2 :SortType = 1;RealCurPos=0;ChoseeFileType=1;break;//ByDate
               case F3 :SortType = 2;RealCurPos=0;ChoseeFileType=1;break;//BySize
               case ENTER :
                         bspc=0;
                         strcpy(dosya_ismi, FileNameList[VisCurPos]);
                         uzunluk=(strlen(dosya_ismi)-1);
                         if(dosya_ismi[uzunluk]=='\\')
                               {
                                ChoseeFileType=1;
                                }
                                else{QuitFromFileWindow = 1;}
                        break;
               case 27: QuitFromFileWindow = 1;
												 FileType = 1;ch=1;
												 break;

               case UP:  VisCurPos--;RealCurPos--;			//Yukari
															if(VisCurPos < 0){ VisCurPos = 0;refresh=1;}
                              if(RealCurPos<0)RealCurPos=0;
																break;
		           case DOWN:  VisCurPos++;RealCurPos++;      //Asagi
                               if(RealCurPos>=FileNumber){
                               RealCurPos=FileNumber-1;VisCurPos--;}
                               if(VisCurPos > 15) {
                               VisCurPos = 15;refresh=1;
                               }findnext(&ffblk[0]);
																break;
               case LEFT:
		           case PG_UP:if((RealCurPos-16)>=0){          	//PgUp
                             RealCurPos-=16;refresh=1;
                                                }
																break;
               case RIGHT:
			         case PG_DN:if((RealCurPos+16)<FileNumber){  //PgDn
                                RealCurPos+=16;refresh=1;
                                                        }
                                else if((RealCurPos-VisCurPos+16)<(FileNumber-1))
                                {
                                VisCurPos=FileNumber-(RealCurPos-VisCurPos+16)-1;
                                RealCurPos=FileNumber-1;
                                UnRepeat=1;
                                }
																break;

               case 9:      if(kayit==1)
                            {
                                if(tab==1)
                                {gotoxy(35,5);_setcursortype(2);getch();tab=0;}
                                else
                                {tab=1;}
                            }
                             break;//TAB
               case 327:  			 													  	//HOME
                              RealCurPos=0;
                              VisCurPos=0;
																break;
			         case 335:                       							//END
                              RealCurPos=FileNumber-1;
                              VisCurPos=15;
															break;
               default:
                       bspc=1;
                        if(chr==8){
                                      for(j=0;j<strlen(gecici);j++)
                                      {
                                      if(j==strlen(gecici)-1){textbackground(WHITE);textcolor(LIGHTGRAY);
                                      gotoxy(21,4);cprintf("%s",gecici);
                                      gecici[j]='\0';textcolor(0);
                                      gotoxy(21,4);cprintf("%s",gecici);
                                      krk--;textcolor(15);}
                                      SortType = 3;RealCurPos=0;ChoseeFileType=1;//chdir(yol);
                                      }
                                      if(strlen(gecici)==0){bspc=0;ChoseeFileType=1;SortType=0;chdir(yol);}
                                   }
                           else
                                      if((chr>32)&&(chr<126)&&(krk+1)<13)
                                                                {
                                                                gecici[krk]=toupper(chr);
                                                                textbackground(15);textcolor(0);
                                                                gotoxy(21,4);cprintf("%s",gecici);
                                                                krk++;textcolor(11);SortType = 3;
                                                                RealCurPos=0;
                                                                if(strcmp(yol,"C:\\")==0){VisCurPos=0;}else{VisCurPos=1;}ChoseeFileType=1;
                                                                RealCurPos=0;ChoseeFileType=1;chdir(yol);
                                                                }
                  textbackground(BLACK);
               break;
            }

if(ChoseeFileType==1)
    {
         for(i=0;i<20;i++)strcpy(FileNameList[i],"\0");
            if(bspc==0)
                {
                      if(uzunluk!=0)
                      {
                             dosya_ismi[uzunluk]='\0';
                             if(strcmp(yol,"C:\\"))strcat(yol,"\\");
                             else{RealCurPos=0;VisCurPos=1;}
                             strcat(yol,dosya_ismi);
                             chdir(yol);
                             strcpy(dosya_ismi, "");
                             RealCurPos=VisCurPos=0;bspc=0;
                       }
                   else
                       {
                       RealCurPos=VisCurPos=0;bspc=1;
                       }
                  }
     xmfree(xhandle);xhandle=0;
     refresh=1;
     }

    if(QuitFromFileWindow == 1){  xmfree(xhandle);xhandle=0;
break;}
//if(ilk==1&&tab==0){ilk=0;}
 }//while
puttext(20, 2, 65, 21, buffer);
if(ch){
}
if(FileType != 3){/*menu1();*/return 0;}
textbackground(BLACK);
 return (QuitFromFileWindow);
}

void kodlar(void)
{
int i,j,sutun=0,sayi=0;
char ilkmi=1,kod[20][78]={""};
char parantezacildi=0;
    for(j=0;j<=20;j++){
    for(i=sutun;i<strlen(strSatir);i++)
    {
     if(ilkmi==1){if(strSatir[i]!=' '){kod[j][sayi]=strSatir[i];ilkmi=0;sayi++;}if(strSatir[i]=='(')parantezacildi=1;}
          else{//ilkmi = 0 ise
               if(strstr(kod[j],"MSG")!=NULL||strstr(kod[j],"TC")!=NULL||strstr(kod[j],"'")!=NULL)
               {
                   kod[j][sayi]=strSatir[i];sayi++;
                 }
                 else
               {
               if(strSatir[i]=='(')parantezacildi=1;else if(strSatir[i-1]==')') parantezacildi=0;
               if(parantezacildi==0){
               if ((strSatir[i]>=48&&strSatir[i]<=57)//0..9 rakam ise
                   ||(strSatir[i-1]>=65&&strSatir[i-1]<=90)//Bir înceki Harf ise
                   ||(strSatir[i-1]>=97&&strSatir[i-1]<=122)//Bir înceki Harf ise
                   ||(strSatir[i]==46)//. ise
                   ||(strSatir[i]==45))//- ise
                      {kod[j][sayi]=strSatir[i];sayi++;}
                      else{ilkmi=1;sayi=0;break;}
                      }
                 }
                }
      sutun++;  }
       if(strstr(kod[j],"TC")!=NULL)
       {
                if(strstr(kod[j],"TC_LASER_ON")!=NULL){strcpy(kod[j],"TC_LASER_ON");}
                else
                if(strstr(kod[j],"TC_LASER_OFF")!=NULL){strcpy(kod[j],"TC_LASER_OFF");}
                else{strcpy(kod[j],"");}

       }else
       if(strstr(kod[j],"MSG")!=NULL){strcpy(kod[j],"");}
       else if(strstr(kod[j]," ' ")!=NULL){strcpy(kod[j],"");}

      }
ilkmi=1;
  for(i=0;i<=20;i++)
  {
      if(strlen(kod[i])>1&&((kod[i][0]=='G'||kod[i][0]=='X'||kod[i][0]=='I'||kod[i][0]=='J'||kod[i][0]=='Y'||kod[i][0]=='Z'||kod[i][0]=='U'||kod[i][0]=='H'||kod[i][0]=='M'||kod[i][0]=='O'||kod[i][0]=='T'||kod[i][0]=='S'||kod[i][0]=='L'||kod[i][0]=='P'||kod[i][0]=='W'||kod[i][0]=='F')
         &&(kod[i][1]>=48&&kod[i][1]<=57))
         ||((kod[i][0]=='I'||kod[i][0]=='J'||kod[i][0]=='X'||kod[i][0]=='Y'||kod[i][0]=='W'||kod[i][0]=='U'||kod[i][0]=='Z')&&kod[i][1]==45&&(kod[i][2]>=48&&kod[i][2]<=57))
         ||(strstr(kod[i],"MSG")!=NULL||strstr(kod[i],"TC")!=NULL))
         {
           if (ilkmi==1)
                        {
                        strcpy(yeniSatir,strSatir);ilkmi=0;break;
                        }
                        else
                        {
                        strcpy(yeniSatir,strSatir);break;
                        }
      }
   }
}

void bosluk(void)
{
int i,j,sutun=0,sayi=0;
char ilkmi=1,kod[20][78]={""};
char *illegal="ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz:_;'=)(&%^\"";
char kodmu=0;
    for(j=0;j<=20;j++){
    for(i=sutun;i<strlen(strSatir);i++)
    {
     if(ilkmi==1){if(strSatir[i]!=' '){kod[j][sayi]=strSatir[i];ilkmi=0;sayi++;
                      if ((strSatir[i+1]>=48&&strSatir[i+1]<=57)||strSatir[i+1]==45||strSatir[i+1]==46){kodmu=1;}
                      else{kodmu=0;}
                      }}
          else{  if(kodmu==1){
                            if(strchr(illegal,strSatir[i])==0)
                            {kod[j][sayi]=strSatir[i];sayi++;}
                            else{ilkmi=1;sayi=0;break;}
                      }
                      if(kodmu==0){
                            if(strSatir[i]!=';'&&strSatir[i-1]!=';')
                            {kod[j][sayi]=strSatir[i];sayi++;}
                            else{ilkmi=1;sayi=0;break;}
                      }
                }
      sutun++;  }
      }
ilkmi=1;
  for(i=0;i<20;i++)
  {
          if(strlen(kod[i])>0){
              if (ilkmi==1)
                        {
                        strcat(yeniSatir,kod[i]);ilkmi=0;
                        }
                        else
                        {
                        strcat(yeniSatir," ");strcat(yeniSatir,kod[i]);
                        }
                    }
   }
}


void satirno(void)
{
int i,j,sutun=0,sayi=0;
char ilkmi=1,kod[20][78]={""};
    for(j=0;j<=20;j++){
    for(i=sutun;i<strlen(strSatir);i++)
    {
     if(ilkmi==1){if(strSatir[i]!=' '){kod[j][sayi]=strSatir[i];ilkmi=0;sayi++;}}
          else{//ilkmi =0 ise
               if(strstr(kod[j],"MSG")!=NULL||strstr(kod[j],"TC")!=NULL)
               {
                   kod[j][sayi]=strSatir[i];sayi++;
                   if(strSatir[i]==41){sutun++;break;}
                 }
                 else
               {
               if ((strSatir[i]>=48&&strSatir[i]<=57)//0..9 rakam ise
                   ||(strSatir[i-1]>=65&&strSatir[i-1]<=90)//Bir înceki Harf ise
                   ||(strSatir[i-1]>=97&&strSatir[i-1]<=122)//Bir înceki Harf ise
                   ||(strSatir[i]==46)//. ise
                   ||(strSatir[i]==45))//- ise
                      {kod[j][sayi]=strSatir[i];sayi++;}
                      else{ilkmi=1;sayi=0;break;}
                 }
                }
      sutun++;  }
      }
ilkmi=1;
  for(i=0;i<20;i++)
  {
          if(strlen(kod[i])>0){
              if (ilkmi==1)
                        { if(kod[i][0]!='N'){
                        strcat(yeniSatir,kod[i]);ilkmi=0;}
                        }
                        else
                        {
                        strcat(yeniSatir,kod[i]);
                        }
                    }
   }
}
