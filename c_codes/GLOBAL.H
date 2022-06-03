//------------------------------  $GLOBALS.C  ----------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <ctype.h>
#include <dir.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>


int xmfree(unsigned int hxmem);
extern unsigned char xmsinstalled;
unsigned int xmalloc(unsigned int size);
void pxmserror(const char *s);
int _xmemcpy(unsigned long n, unsigned int srchandle, unsigned long srcoff,
	     unsigned int desthandle, unsigned long destoff);
int inline ctoxm(unsigned int desthandle, unsigned long destoff, void far *src, unsigned long n)
  { return (_xmemcpy(n, 0, (unsigned long)src, desthandle, destoff)); }
int inline xmtoc(void far *dest, unsigned int srchandle, unsigned long srcoff, unsigned long n)
  { return (_xmemcpy(n, srchandle, srcoff, 0, (unsigned long)dest)); }

enum{ENTER=13,F1=59+256,F2,F3,F4,F5,F6,F7,F8,F9,F10,UP=72+256,PG_UP,LEFT=75+256,RIGHT=LEFT+2,DOWN=80+256,PG_DN};

struct message{char out[80];};
#if defined(MAIN)

char buffer[4096];
int itemindex;
double RADYUS=0;
	struct CRTC{
		char tanim,kesim,mutlak;
		long xson,yson,zson,uson,ic,jc;
		}CRC={0,0,0,0,0,0,0,0,0};

  struct LISTBOX
       {
       int x1,y1,x2,y2;
       char item[9][30];
       int itemindex;
       };//listbox[2]={{10,10,38,18},{40,10,68,18}};

struct PARAMETRELER
       {unsigned  satirno_yaz:1, bosluk_koy:1, arc_tip:1,dil:1;
       char filename[12];
       int start_satir;
       LISTBOX listbox[2];
       }parameters={1,1,0,0,"\0",0,{{10,10,38,18},{40,10,68,18}}};

struct START
       {
       double x,y,z;
       }start={0,0,0};

struct END
       {
       double x,y,z;
       }end={0,0,0};


char star_satir_aktif=0;
       int strt_satir=1;
#else
extern char star_satir_aktif;
extern int start_satir;


extern int itemindex;
struct LISTBOX
       {
       int x1,y1,x2,y2;
       char item[9][30];
       int itemindex;
       };
//         */
       extern struct PARAMETRELER
       {unsigned
       satirno_yaz:1,
       bosluk_koy:1,
       arc_tip:1,
				dil:1;
       char filename[12];
       int start_satir;
        LISTBOX listbox[2];
       }parameters;


extern char buffer[4096];
#endif