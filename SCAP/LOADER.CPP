// all the drivers needed to load the game are present in this module

union REGS ii,oo; //input and output cpu registers
union SREGS ss;

void initilize_graphics()
{
  int gd,gm;
  /* request auto detection */
  int gdriver = DETECT, gmode, errorcode;

  /* initialize graphics mode */
  initgraph(&gdriver, &gmode, "c:\\tc");

  /* read result of initialization */
  errorcode = graphresult();

  if (errorcode != grOk)  /* an error occurred */
     {
	cout<<"Graphics error: "<< grapherrormsg(errorcode)<<"\n";
	cout<<"Press any key to halt:";
	getch();
	exit(1);             /* return with error code */
     }


}

void close_graphics()
{
  closegraph();
  restorecrtmode();
}

void amit_needs_mouse()
{


  ii.x.ax = 0;
  int86(0x33, &ii, &oo);

  ii.x.ax = 1;
  int86(0x33, &ii, &oo);

}

int m_button()
{
  int res;
  ii.x.ax = 3;
  int86(0x33, &ii, &oo);
  res = oo.x.bx;
  return res;
}

int m_x()
{
   int res;
  ii.x.ax = 3;
  int86(0x33, &ii, &oo);
  res = oo.x.cx;
  return res;
}
int m_y()
{
   int res;
  ii.x.ax = 3;
  int86(0x33, &ii, &oo);
  res = oo.x.dx;
  return res;
}
void m_showptr()
{
  ii.x.ax = 1;
  int86(0x33, &ii, &oo);
}

void m_setxmax(int min, int max)
{
  ii.x.ax = 7;
  ii.x.cx = min;
  ii.x.dx = max;
  int86(0x33, &ii, &oo);
}

void m_setymax(int min, int max)
{
  ii.x.ax = 8;
  ii.x.cx = min;
  ii.x.dx = max;
  int86(0x33, &ii, &oo);
}

void m_setposn(int x, int y)
{
  ii.x.ax = 4;
  ii.x.cx = x;
  ii.x.dx = y;
  int86(0x33, &ii, &oo);
}

void m_speed(int x, int y, int speed)
{
  ii.x.ax = 0x001a;
  ii.x.bx = x;
  ii.x.cx = y;
  ii.x.dx = speed;
  int86(0x33, &ii, &oo);
}
int getpixcolor(int x, int y)
{
  int res;
  ii.h.ah = 13;
  ii.x.cx = x;
  ii.x.dx = y;
  int86(0x10,&ii,&oo);
  res = oo.x.dx;
  return res;
}


int c[][32] = {
    //hand screen mask + bitmap
    0xe1ff,0xe1ff,0xe1ff,0xe1ff,0xe1ff,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x1e00,0x1200,
    0x1200,0x1200,0x13ff,0x1249,0x1249,0xf249,
    0x9001,0x9001,0x9001,0x8001,0x8001,0x8001,
    0xffff,0x0000,

    //dot screen mask
    0xffff,0x5fff,0x1fff,0xffff,
    0xffff,0xffff,0xffff,0xffff,
    0xffff,0xffff,0xffff,0xffff,
    0xffff,0xffff,0xffff,0xffff,
    //dot bitmap
    0x6000,0xa000,0xa000,0xe000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,


    };
void changecursor(int *shape)
{
  ii.x.ax = 9;
  ii.x.bx = 0;
  ii.x.cx = 0;
  ii.x.dx = (unsigned)shape;
  segread (&ss);
  ss.es = ss.ds;
  int86x(0x33,&ii,&oo,&ss);
}


void image_retrive(char *filename)
{
  struct fig{
     int col,x,y;
     };
  fig paint;
  int xxx,yyy,count,coolour;
  char colour;
  ifstream imagefile(filename,ios::in | ios::binary);
  if (!imagefile){
     setcolor(12);

     outtextxy(5,460,"This path filename was not found");
     setcolor(7);
     }
  while (!imagefile.eof()){
      imagefile.read((unsigned char *)&paint ,sizeof(struct fig));
      putpixel(paint.x,paint.y,paint.col);
  }

}
void *screenbuffer1;
void save_screen_1(int tx, int ty, int bx, int by)
{
  int scr_area = imagesize(tx, ty, bx, by);
  screenbuffer1 = malloc(scr_area);
  getimage(tx,ty,bx,by,screenbuffer1);
}
void restore_screen_1(int tx, int ty)
{
 m_setposn(2,2);
 putimage(tx,ty,screenbuffer1,COPY_PUT);
 free(screenbuffer1);
}
void setmode(int m)
{
  ii.h.ah = 0; //service number
  ii.h.al = m; // mode no
  int86(16,&ii,&oo);
}
void setpaletteregs()
{
  char arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  ii.h.ah = 0x10; //service number
  ii.h.al = 0x02; //subfunction - setmultiple registers
  ss.es = FP_SEG(arr);
  ii.x.dx = FP_OFF(arr);

  int86x(16,&ii,&oo,&ss);
}
void setdacregs()
{
  int j;
  for (j = 1 ; j <= 15 ; j++)
    {
      ii.h.ah = 0x10; //service number
      ii.h.al = 0x10; //sub function - set DAC registers
      ii.x.bx = j; // register no to set (0-63)
      ii.h.ch = 10;//green value(0-63)
      ii.h.cl = 20; //blue value(0-63)
      ii.h.dh = 0; //red value(0-63)
      int86(16,&ii,&oo);
    }

}
