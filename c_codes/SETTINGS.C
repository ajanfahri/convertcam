//-------------------------------  SETTINGS.C  ---------------------------------
#include "global.h"

extern void cerceve(int x1,int y1,int x2,int y2, int w_fcolor,int bcolor);
extern void incecerceve(int x1,int y1,int x2,int y2, int w_fcolor,int bcolor);
extern unsigned getfirstcolor(struct text_info *cl);
extern void putcolor(unsigned oldcolor);
extern int kbhits(void);
extern char *stringal(int x1,int y1,int uzunluk,char *legal,int gelen);
extern void hata_mesaji(char *mesaj);
void dosya_oku(char *file_name,int baslangic);
void items_ekle(char ek_string[30],char ek_string2[30],int itemindex,int realcurpos,int gelen);
void dosyaismial(void);
void listbox_itemsdelete(int itemindex);
void zemin(void);
struct message read_msg(int msg_number);
int tab=0;
int yazi_yaz(int secim);
void listbox_edit(void);


void listbox_ciz(int listno)
{
for(int i=parameters.listbox[listno].y1;i<=parameters.listbox[listno].y2;++i){
     for(int j=parameters.listbox[listno].x1;j<=parameters.listbox[listno].x2;++j){gotoxy(j,i);textbackground(BLUE);cprintf(" ");}}
}

void listbox_doldur(int listno)
{
textbackground(BLUE);textcolor(15);
int itemindex=0,i=0;
int satir=parameters.listbox[listno].y1;
 while(1)
 {
   if(strlen(parameters.listbox[listno].item[itemindex])>0&&itemindex<9)
   {
   for(int j=parameters.listbox[listno].x1;j<=parameters.listbox[listno].x2;++j)
     {
     gotoxy(j,parameters.listbox[listno].y1+itemindex);
     textbackground(BLUE);cprintf(" ");//”nce yazilacak satirin backgroundu mavi yapliyor.
   }
   gotoxy(parameters.listbox[listno].x1,satir);


    for(i=0;i<strlen(parameters.listbox[listno].item[itemindex]);++i){
                      cprintf("%c",parameters.listbox[listno].item[itemindex][i]);
                      }
    satir+=1;itemindex++;
   }else{break;}
  }
  if(itemindex>=9){itemindex=8;}
// parameters.listbox[listno].itemindex=itemindex;
}

void listbox_itemsdelete(int itemindex,int realcurpos)
{
items_ekle("","",itemindex,realcurpos,1);
}



void items_ekle(char ek_string[30],char ek_string2[30],int itemindex,int realcurpos,int gelen)
{
FILE *fptrx;
if((fptrx=fopen(parameters.filename,"rt"))!=NULL){

if(gelen){
for(int i=itemindex;i<9;i++)
{strcpy(parameters.listbox[0].item[i],parameters.listbox[0].item[i+1]);
 strcpy(parameters.listbox[1].item[i],parameters.listbox[1].item[i+1]);
parameters.listbox[0].itemindex--;
parameters.listbox[1].itemindex--;
if(parameters.listbox[0].itemindex<0)parameters.listbox[0].itemindex=0;
if(parameters.listbox[1].itemindex<0)parameters.listbox[1].itemindex=0;
}
}else {
parameters.listbox[0].itemindex++;
parameters.listbox[1].itemindex++;
       }
fseek(fptrx, 0L, SEEK_SET);
fwrite(&parameters,sizeof(parameters), 1, fptrx);
fclose(fptrx);

                 }

}

void kaydet2()
{
FILE *fptrx;
if((fptrx=fopen(parameters.filename,"rt"))!=NULL){

fseek(fptrx, 0L, SEEK_SET);
fwrite(&parameters,sizeof(parameters), 1, fptrx);
fclose(fptrx);
                                                 }
}



void listbox_itemsadd(int itemindex,int realcurpos)
{
textbackground(BLUE);textcolor(15);
char yedek[2][37]={"\0","\0"};
int i=0,listno=0;
for(listno=0;listno<=1;++listno){
   for(int j=parameters.listbox[listno].x1;j<=parameters.listbox[listno].x2;++j)
     {
     gotoxy(j,parameters.listbox[listno].y1+itemindex);
     textbackground(RED);
     cprintf(" ");//yazilacak satirin backgroundu mavi yapiliyor.
     }
   gotoxy(parameters.listbox[listno].x1,parameters.listbox[listno].y1+itemindex);//burasi
   _setcursortype(1);
   strcpy(yedek[listno],stringal(parameters.listbox[listno].x1,(parameters.listbox[listno].y1+itemindex),37,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789abcdefghijklmnopqrstuvwxyz.:_-=)(&%*^",5));
   if(strlen(yedek[listno])>0){strset(parameters.listbox[listno].item[itemindex],'\0');strcpy(parameters.listbox[listno].item[itemindex],yedek[listno]);}
   _setcursortype(0);
      for(j=parameters.listbox[listno].x1;j<=parameters.listbox[listno].x2;++j)
     {
     gotoxy(j,parameters.listbox[listno].y1+itemindex);
     textbackground(GREEN);cprintf(" ");
     }
   gotoxy(parameters.listbox[listno].x1,parameters.listbox[listno].y1+itemindex);
   if(strlen(parameters.listbox[listno].item[itemindex])>0)
   {
    for(i=0;i<strlen(parameters.listbox[listno].item[itemindex]);++i){cprintf("%c",parameters.listbox[listno].item[itemindex][i]);}
   }else{break;}
}
if(strlen(yedek[0])>0&&strlen(yedek[1])>0)
{
items_ekle(yedek[0],yedek[1],itemindex,realcurpos,0);
}
//parameters.listbox[listno].itemindex=itemindex;
}

void dosyaismial(void)
{
FILE *dosya;
char name[12];
  gotoxy(22,8);
  textbackground(BLUE);textcolor(WHITE);cprintf("        ");
  gotoxy(22,8);_setcursortype(1);
 strcpy(name,stringal(22,8,8,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789abcdefghijklmnopqrstuvwxyz.:_-=)(&%*^",5));
 _setcursortype(0);
if(strlen(name)>0){strcat(name,".CNV");
 if(strlen(name)>0&&(dosya=fopen(name,"rt"))==NULL)
 {
  dosya=fopen(name,"w+");
  fclose(dosya);
  }
strcpy(parameters.filename,name);
itemindex=0;
}
}

int tab_control()
{
char starttext[12];
char st_satir[25];
  if(tab<0){tab=4;}
  if(tab>4){tab=0;}
  switch(tab)
             {
             case 0 :gotoxy(37,5);break;
             case 1 :gotoxy(37,6);break;
             case 2 :gotoxy(66,5);break;
             case 3 :gotoxy(60,6);
                     strcpy(starttext,stringal(60,6,8,"0123456789",9));
                     if(starttext!="") {
                     parameters.start_satir=atoi(starttext);
                     kaydet2();
                     }
											//tab++;
                     break;
             case 4 :
						 gotoxy(11,10);listbox_edit();
						 tab_control();break;
             }
return 0;
}

void zemin()
{
char st_satir[25];

textbackground(BLACK);
_setcursortype(2);
cerceve(8,3,70,22,RED,LIGHTGRAY);
incecerceve(9,4,69,7,BLACK,LIGHTGRAY);
gotoxy(11,5);cprintf(read_msg(386).out);cprintf("           : [ ] ");
gotoxy(41,5);cprintf(read_msg(389).out);cprintf(" : [ ] ");

if(parameters.bosluk_koy==1){gotoxy(37,5);cprintf("X");}
if(parameters.arc_tip==1){gotoxy(66,5);cprintf("X");}
gotoxy(11,6);cprintf(read_msg(385).out);cprintf(" : [ ]");
//cprintf(" DELETE LINE NUMBERS    : [ ] ");
if(parameters.satirno_yaz==1){gotoxy(37,6);cprintf("X");}
gotoxy(41,6);cprintf(read_msg(390).out);cprintf(":");
//cprintf(" START LINE NUMBER :[   ] ");
itoa(parameters.start_satir,st_satir,10);
gotoxy(60,6);cprintf(" %s ",st_satir);


incecerceve(9,8,69,19,BLACK,LIGHTGRAY);
char dosya_ismi[13];strcpy(dosya_ismi,parameters.filename);
strxfrm(dosya_ismi, dosya_ismi, strlen(dosya_ismi)-3);
gotoxy(10,8);cprintf(read_msg(13).out);
textbackground(BLUE);textcolor(WHITE);
cprintf("        ");gotoxy(22,8);cprintf("%s",dosya_ismi);
textbackground(LIGHTGRAY);textcolor(0);
gotoxy(15,9);cprintf(" X MACHINE ");
gotoxy(34,9);textcolor(RED);cprintf(read_msg(393).out);textcolor(0);
gotoxy(55,9);cprintf(" AJAN ");
listbox_ciz(0);
listbox_ciz(1);
textbackground(GREEN);textcolor(RED);
//gotoxy(9,21); cprintf("  F1 YENI  ");
gotoxy(21,21);cprintf("   F2 ");cprintf(read_msg(375).out);cprintf("  ");
//gotoxy(33,21);cprintf(" F3 KAYDET ");
gotoxy(45,21);cprintf("  F4 ");cprintf(read_msg(392).out);cprintf("  ");
}

int settings(void)
{
int secim,x=0;
tab=0;
gettext(8,3,70,22,buffer);
zemin();
dosya_oku(parameters.filename,0);
listbox_doldur(0);
listbox_doldur(1);
gotoxy(37,5);
while(x!=2){
        switch(secim=kbhits())
         {
                   case F2   : dosyaismial();listbox_edit();break;
                   case 9    : tab++;tab_control();break;
                   case ENTER: tab++;tab_control();break;
                   case 27   : textbackground(BLACK);
                               puttext(8,3,70,22,buffer);_setcursortype(0);
                               x=2;break;
                   default   : if(secim==13||secim==32){
									 textbackground(LIGHTGRAY);textcolor(0);
                             yazi_yaz(secim);
                            }
//														listbox_doldur(0);listbox_doldur(1);break;
           }
    }
kaydet2();
return 0;
}

int yazi_yaz(int secim)
{
  if(tab<3){if(secim==32)
                 {if(tab==0){if(parameters.bosluk_koy==0){parameters.bosluk_koy=1;cprintf("X");gotoxy(wherex()-1,wherey());}
                  else if(parameters.bosluk_koy==1){parameters.bosluk_koy=0;cprintf(" ");gotoxy(wherex()-1,wherey());}}
                  if(tab==1){if(parameters.satirno_yaz==0){parameters.satirno_yaz=1;cprintf("X");gotoxy(wherex()-1,wherey());}
                  else if(parameters.satirno_yaz==1){parameters.satirno_yaz=0;cprintf(" ");gotoxy(wherex()-1,wherey());}}
                  if(tab==2){if(parameters.arc_tip==0){parameters.arc_tip=1;cprintf("X");gotoxy(wherex()-1,wherey());}
                  else if(parameters.arc_tip==1){parameters.arc_tip=0;cprintf(" ");gotoxy(wherex()-1,wherey());}}
                 }}
return 0;

}

void dosya_oku(char *file_name,int baslangic)
{
FILE *fptrx;
if((fptrx=fopen(file_name,"r+t"))!=NULL)
{
listbox_ciz(0);
listbox_ciz(1);
fseek(fptrx, 0L, SEEK_SET);
fread(&parameters,sizeof(parameters),1,fptrx);
fclose(fptrx);
}
else
    {
    char hata[40];strcpy(hata,read_msg(398).out);
    fptrx=fopen(parameters.filename,"r+");
    hata_mesaji(&hata[0]);_setcursortype(2);
    fclose(fptrx);
    }
}


void listbox_edit(void)
{
char st_satir[12];
_setcursortype(0);
int kontrol=1,realcurpos=0;
int quit=0;
while(1){
if(kontrol==1){
dosya_oku(parameters.filename,realcurpos);

//itoa(parameters.start_satir,st_satir,10);
//gotoxy(61,6);cprintf(" %s ",st_satir);
zemin();
listbox_doldur(0);
listbox_doldur(1);
for(int listno=0;listno<=1;++listno){
 for(int j=parameters.listbox[listno].x1;j<=parameters.listbox[listno].x2;++j)
     {
     gotoxy(j,parameters.listbox[listno].y1+itemindex);
     textbackground(GREEN);cprintf(" ");
     }
     gotoxy(parameters.listbox[listno].x1,parameters.listbox[listno].y1+itemindex);
     textbackground(GREEN);textcolor(15);cprintf(parameters.listbox[listno].item[itemindex]);
}
kontrol=0;
}else{
         switch(kbhits())  {
               case F2   : dosyaismial();kontrol=1;break;
               case F4    :listbox_itemsdelete(itemindex,realcurpos);kontrol=1;break;
               case UP    :if(realcurpos>0&&itemindex==0){realcurpos--;kontrol=1;dosya_oku(parameters.filename,realcurpos);}
                           if(itemindex!=0){itemindex--;kontrol=1;}break;
		           case DOWN  :if(itemindex==8&&realcurpos+itemindex<parameters.listbox[0].itemindex)
                           {
                           realcurpos++;kontrol=1;
                           dosya_oku(parameters.filename,realcurpos);
                           }
                           else if(realcurpos+itemindex<parameters.listbox[0].itemindex){itemindex++;kontrol=1;}
													 break;
		           case 9     :quit=1;break;
		           case 27    :quit=1;break;
               case ENTER :listbox_itemsadd(itemindex,realcurpos);
                           if(itemindex==8&&realcurpos+itemindex<=parameters.listbox[0].itemindex){realcurpos++;kontrol=1;dosya_oku(parameters.filename,realcurpos);}
                           else if(itemindex<parameters.listbox[0].itemindex){itemindex++;kontrol=1;}
                           //itemindex++;
                           kontrol=1;break;
               default    :break;
            }
           }
if(quit==1){break;}
    }//while
_setcursortype(2);
tab++;
}//listbox_edit

