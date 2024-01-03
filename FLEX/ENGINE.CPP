int exit_code_1 = 0 , main_exit_code = 0;

void cls(int bkcol)
{
  setbkcolor(bkcol);
  cleardevice();

  rectangle(1,1,638,13);

  settextstyle(0,0,1);

  outtextxy(16,3,"File");
  outtextxy(65,3,"Edit");
  outtextxy(111,3,"Color");
  outtextxy(167,3,"Shape");
  outtextxy(224,3,"Help");

  line ( 10,10,263,53);
  line ( 20,49,256,22);
}
void gra_m_loc(int x, int y, int col)
{
  char strx[3],stry[3],location[12];
  strcpy(location,"");
      gcvt( m_x() , 3 ,strx);
      gcvt( m_y() , 3 ,stry);

      strcpy(location,strx);
      strcat(location," / ");
      strcat(location,stry);

      setcolor(15);
      outtextxy(x,y,location);
      delay(50);
      setcolor(0);
      outtextxy(x,y,location);
  setcolor(col);
}





void hilight_file(int col)
{
 settextstyle(0,0,1);
  setcolor(14);
  outtextxy(16,3,"File");
  setcolor(15);
  outtextxy(65,3,"Edit");
  outtextxy(111,3,"Color");
  outtextxy(167,3,"Shape");
  outtextxy(224,3,"Help");
  setcolor(col);
}
void hilight_edit(int col)
{
 settextstyle(0,0,1);
  setcolor(14);
  outtextxy(65,3,"Edit");
  setcolor(15);

  outtextxy(16,3,"File");
  outtextxy(111,3,"Color");
  outtextxy(167,3,"Shape");
  outtextxy(224,3,"Help");
  setcolor(col);
}
void hilight_color(int col)
{
 settextstyle(0,0,1);
  setcolor(14);
  outtextxy(111,3,"Color");

  setcolor(15);
  outtextxy(65,3,"Edit");
  outtextxy(16,3,"File");

  outtextxy(167,3,"Shape");
  outtextxy(224,3,"Help");
  setcolor(col);
}
void hilight_shape(int col)
{
 settextstyle(0,0,1);
  setcolor(14);
  outtextxy(167,3,"Shape");

  setcolor(15);
  outtextxy(65,3,"Edit");
  outtextxy(16,3,"File");
  outtextxy(111,3,"Color");

  outtextxy(224,3,"Help");
  setcolor(col);
}
void hilight_help(int col)
{
 settextstyle(0,0,1);
  setcolor(14);
  outtextxy(224,3,"Help");

  setcolor(15);
  outtextxy(65,3,"Edit");
  outtextxy(16,3,"File");
  outtextxy(111,3,"Color");
  outtextxy(167,3,"Shape");

  setcolor(col);
}
void normalise_menu(int col)
{
 settextstyle(0,0,1);
   setcolor(15);
  outtextxy(224,3,"Help");
  outtextxy(65,3,"Edit");
  outtextxy(16,3,"File");
  outtextxy(111,3,"Color");
  outtextxy(167,3,"Shape");

  setcolor(col);
}


void check_n_hilight_mainmenu(int fx_col)
{
  if  (m_y() >= 12) normalise_menu(fx_col);

  if ( (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 10) && (m_x() <= 57)) hilight_file(fx_col);
  if ( (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 57) && (m_x() <= 100)) hilight_edit(fx_col);
  if ( (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 106) && (m_x() <= 154)) hilight_color(fx_col);
  if ( (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 160) && (m_x() <= 208)) hilight_shape(fx_col);
  if ( (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 219) && (m_x() <= 260)) hilight_help(fx_col);
}
void hilight_create_new(int col)
{
  settextstyle(0,0,1);
  setcolor(14);

  int yval = 160 , space = 20;
  setcolor(12);
  outtextxy(165,yval,"Create A New Image File");
  yval = yval + space;
  setcolor(14);
  outtextxy(165,yval,"Open An existing Image File   F3");

  yval = yval + space;
  outtextxy(165,yval,"Save current Creation   F2");

  yval = yval + space;
  outtextxy(165,yval,"Save drawing as..");

  yval = yval + space;
  outtextxy(165,yval,"Exit, ta-ta, Bye-Bye   Alt+X");



  setcolor(col);


}
void hilight_open_file(int col)
{
  settextstyle(0,0,1);
  setcolor(14);

  int yval = 160 , space = 20;
  setcolor(14);
  outtextxy(165,yval,"Create A New Image File");
  yval = yval + space;
  setcolor(12);
  outtextxy(165,yval,"Open An existing Image File   F3");
  setcolor(14);
  yval = yval + space;
  outtextxy(165,yval,"Save current Creation   F2");

  yval = yval + space;
  outtextxy(165,yval,"Save drawing as..");

  yval = yval + space;
  outtextxy(165,yval,"Exit, ta-ta, Bye-Bye   Alt+X");



  setcolor(col);


}

void hilight_save_file(int col)
{
  settextstyle(0,0,1);
  setcolor(14);

  int yval = 160 , space = 20;
  setcolor(12);
  outtextxy(165,yval,"Create A New Image File");
  yval = yval + space;
  setcolor(14);
  outtextxy(165,yval,"Open An existing Image File   F3");

  yval = yval + space;
  outtextxy(165,yval,"Save current Creation   F2");

  yval = yval + space;
  outtextxy(165,yval,"Save drawing as..");

  yval = yval + space;
  outtextxy(165,yval,"Exit, ta-ta, Bye-Bye   Alt+X");



  setcolor(col);


}

void hilight_save_as(int col)
{
  settextstyle(0,0,1);
  setcolor(14);

  int yval = 160 , space = 20;
  setcolor(12);
  outtextxy(165,yval,"Create A New Image File");
  yval = yval + space;
  setcolor(14);
  outtextxy(165,yval,"Open An existing Image File   F3");

  yval = yval + space;
  outtextxy(165,yval,"Save current Creation   F2");

  yval = yval + space;
  outtextxy(165,yval,"Save drawing as..");

  yval = yval + space;
  outtextxy(165,yval,"Exit, ta-ta, Bye-Bye   Alt+X");



  setcolor(col);


}

void hilight_exit(int col)
{
  settextstyle(0,0,1);
  setcolor(14);

  int yval = 160 , space = 20;
  setcolor(12);
  outtextxy(165,yval,"Create A New Image File");
  yval = yval + space;
  setcolor(14);
  outtextxy(165,yval,"Open An existing Image File   F3");

  yval = yval + space;
  outtextxy(165,yval,"Save current Creation   F2");

  yval = yval + space;
  outtextxy(165,yval,"Save drawing as..");

  yval = yval + space;
  outtextxy(165,yval,"Exit, ta-ta, Bye-Bye   Alt+X");



  setcolor(col);


}

void menupop_file(int fx_col)
{
  save_screen_1(150,122,496,317);
  putimage(150,122,screenbuffer1,XOR_PUT);
  setcolor(15);
  rectangle(150,122,496,317);
  setcolor(11);
  rectangle(151,123,495,316);
  setcolor(2);
  rectangle(152,124,494,315);

  settextstyle(0,0,1);
  setcolor(14);
  outtextxy(155,130," File Menu.");
  outtextxy(150,134,"____________");
  settextstyle(0,0,1);
  int yval = 160 , space = 20;

  outtextxy(165,yval,"Create A New Image File");
  yval = yval + space;
  outtextxy(165,yval,"Open An existing Image File   F3");

  yval = yval + space;
  outtextxy(165,yval,"Save current Creation   F2");

  yval = yval + space;
  outtextxy(165,yval,"Save drawing as..");

  yval = yval + space;
  outtextxy(165,yval,"Exit, ta-ta, Bye-Bye   Alt+X");
  exit_code_1 = 0;
  do{
      if ( (m_y() >= 157) && (m_y() <= 168) && (m_x() >= 164) && (m_x() <= 350)) hilight_create_new(fx_col);
      if ( (m_y() >= 177) && (m_y() <= 188) && (m_x() >= 164) && (m_x() <= 420)) hilight_open_file(fx_col);
      if ( (m_y() >= 197) && (m_y() <= 208) && (m_x() >= 164) && (m_x() <= 373)) hilight_create_new(fx_col);
      if ( (m_y() >= 217) && (m_y() <= 227) && (m_x() >= 164) && (m_x() <= 299)) hilight_create_new(fx_col);
      if ( (m_y() >= 236) && (m_y() <= 249) && (m_x() >= 164) && (m_x() <= 389)) hilight_create_new(fx_col);
    }while(exit_code_1 != 1);
  restore_screen_1(150,122);
}
void menupop_edit()
{
  save_screen_1(150,122,496,317);
  putimage(150,122,screenbuffer1,XOR_PUT);

  setcolor(15);
  rectangle(150,122,496,317);
  setcolor(11);
  rectangle(151,123,495,316);
  setcolor(2);
  rectangle(152,124,494,315);

  settextstyle(1,0,3);
  setcolor(14);
  outtextxy(155,130," Edit Menu.");
  outtextxy(150,134,"____________");
  int yval = 160 , space = 20;
  settextstyle(7,0,1);
  outtextxy(165,yval,"Copy object  Ctrl+C");
  yval = yval + space;
  outtextxy(165,yval,"Paste object  Ctrl+P");

  yval = yval + space;
  outtextxy(165,yval,"Clear The Screen");
  do{
    gra_m_loc(563,5,15); // print current location of pionter
    }while(!kbhit());
  restore_screen_1(150,122);
}
void menupop_color()
{
  save_screen_1(150,122,496,317);
  putimage(150,122,screenbuffer1,XOR_PUT);
  setcolor(15);
  rectangle(150,122,496,317);
  setcolor(11);
  rectangle(151,123,495,316);
  setcolor(2);
  rectangle(152,124,494,315);

  settextstyle(1,0,3);
  setcolor(14);
  outtextxy(155,130," Color Menu.");
  outtextxy(150,134,"____________");
  int yval = 160 , space = 20;
  settextstyle(7,0,1);
  outtextxy(165,yval,"Select Foreground Color");
  yval = yval + space;
  outtextxy(165,yval,"Select Background Color");

  yval = yval + space;
  outtextxy(165,yval,"Select Fill Pattern");

  yval = yval + space;
  outtextxy(165,yval,"Select line Style");

  do{
    gra_m_loc(563,5,15); // print current location of pionter
    }while(!kbhit());
  restore_screen_1(150,122);
}

void menupop_shape()
{
  save_screen_1(150,122,496,317);
  putimage(150,122,screenbuffer1,XOR_PUT);
  setcolor(15);
  rectangle(150,122,496,317);
  setcolor(11);
  rectangle(151,123,495,316);
  setcolor(2);
  rectangle(152,124,494,315);

  settextstyle(1,0,3);
  setcolor(14);
  outtextxy(155,130," Shape Menu.");
  outtextxy(150,134,"____________");
  int yval = 160 , space = 20;
  settextstyle(7,0,1);
  outtextxy(165,yval,"Write Graphical Text");
  yval = yval + space;
  outtextxy(165,yval,"Draw A Rectangle");

  yval = yval + space;
  outtextxy(165,yval,"Draw Circle");

  yval = yval + space;
  outtextxy(165,yval,"Draw Ellipse");

  yval = yval + space;
  outtextxy(165,yval,"Draw Arc");
  yval = yval + space;
  outtextxy(165,yval,"Draw A Line");
  yval = yval + space;
  outtextxy(165,yval,"Free hand drawing mode");
  do{
    gra_m_loc(563,5,15); // print current location of pionter
    }while(!kbhit());
  restore_screen_1(150,122);
}

void menupop_help()
{
  save_screen_1(150,122,496,317);
  putimage(150,122,screenbuffer1,XOR_PUT);
  setcolor(15);
  rectangle(150,122,496,317);
  setcolor(11);
  rectangle(151,123,495,316);
  setcolor(2);
  rectangle(152,124,494,315);

  settextstyle(1,0,3);
  setcolor(14);
  outtextxy(155,130," Help Menu.");
  outtextxy(150,134,"____________");
  int yval = 160 , space = 20;
  settextstyle(7,0,1);
  outtextxy(165,yval,"Help Index");
  yval = yval + space;
  outtextxy(165,yval,"Topic Serch");

  yval = yval + space;
  outtextxy(165,yval,"About..");

  yval = yval + space;
  outtextxy(165,yval,"The Brain Behind.");

  do{
    gra_m_loc(563,5,15); // print current location of pionter
    }while(!kbhit());
  restore_screen_1(150,122);
}

