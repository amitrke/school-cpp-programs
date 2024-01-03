#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#define X0 4
#define Xn 76
#define Y0 4
#define Yn 23

union REGS i,o;
int ascii,scan;
int level,change;
int n = 200;
void get_key()
{
  i.h.ah=0;
  int86(0x16,&i,&o);
  ascii=o.h.al;
  scan=o.h.ah;
}
class element
{
public:
	char s;
	int x,y;
       element() : s('þ') {}
};

class snake{
       element sn[150];
       int length;
       int h,k;
       time_t t;
      public:
       snake();
       void Draw_boundary();
       void print_snake();
       void check();
       void Move(int a[],int n);
       void Random();
};


void snake :: Random()
{
 randomize();
 h=X0+rand()%(Xn-X0);
 k=Y0+rand()%(Yn-Y0);
 gotoxy(h,k);
 textcolor(RED);
 cprintf("");
 textcolor(WHITE);
}

snake :: snake()
{
    length=3;
    for(int k=0;k<length;k++)
    {
       sn[k].x=length-k+X0;
       sn[k].y=Y0+1;
    }
    Random();
}

void snake :: print_snake()
{
  textcolor(YELLOW);
  for(int i=0;i<length-1;i++)
     {
	 gotoxy(sn[i].x,sn[i].y);
	 cprintf("%c",sn[i].s);
     }
    textcolor(BLACK);
    gotoxy(sn[length-1].x,sn[length-1].y);
	 cprintf(" ");
     textcolor(WHITE);
}

void snake :: Draw_boundary()
{

   textcolor(BLUE);               //Draws Horizontal Boundaries
   gotoxy(X0-2,Y0-1);
   for(int ii=X0-2;ii<Xn+2;ii++)
     cprintf("Í");
   gotoxy(X0-2,Yn+1);
  for(ii=X0-2;ii<Xn+2;ii++)
      cprintf("Í");

   for(ii=Y0-1;ii<Yn+2;ii++)      //Draws Vertical Boundaries
   {
     gotoxy(X0-2,Y0+ii-4);
     cprintf("³");
   }
  for(ii=Y0-1;ii<Yn+2;ii++)
  {
     gotoxy(Xn+2,Y0+ii-4);
     cprintf("³");
  }
    textcolor(LIGHTGRAY);            //shows present level
    gotoxy(35,Y0-2);
    cprintf("LEVEL %d",level);
	textcolor(MAGENTA+BLINK);   //instructs to start
	gotoxy(X0,Y0-2);
	cprintf("Press any key to START");
	getch();
	textcolor(BLACK);
	gotoxy(X0,Y0-2);
	cprintf("Press any key to START");
    textcolor(GREEN);
    gotoxy(X0,Y0-2);
    cprintf("Press 'Esc' to QUIT!");

  textcolor(WHITE);

}
void snake :: check()
{
  if(length>50)
  {                        //Checks for level change
      n-=40;
      change=1;
      return;
  }
  if(sn[0].x==h && sn[0].y==k)
  {                               //Increments Length
    length+=3;
    Random();
  }

  for(int iii=1;iii<length-1;iii++)
   if(sn[0].x == sn[iii].x && sn[0].y == sn[iii].y)
	      {
		 textcolor(CYAN+BLINK);           //Self Collision
		 gotoxy(X0+30,Y0+10);
		  cprintf("GAME OVER!");
		  delay(3000);
		exit(0);
	      }
  textcolor(GREEN);
	gotoxy(Xn-10,Y0-2);
	cprintf("LENGTH=%d",length-1);
}

void snake :: Move(int a[],int n)
{
 while((sn[0].x>=X0 && sn[0].x<=Xn) && (sn[0].y>=Y0 && sn[0].y<=Yn))
 {
   get_key();
   if(scan==75)
     {
       if(!a[3])    //pressed  LEFT && prevoiusly not going RIGHT
	{
		 for(int t=0;t<4;t++)
		   a[t]=0;
		 a[2]=1;
		 while(sn[0].x>=X0 && !kbhit())
		   {
		      for(int i=length-1;i>0;i--)
			  sn[i]=sn[i-1];
		      sn[0].x--;
		      check();
		      if(change)  return;
		      print_snake();
		      delay(n);
		   }
	}
       else{              //pressed  LEFT && prevoiusly going RIGHT
		while(sn[0].x<=Xn && !kbhit())
		  {
			 for(int i=length-1;i>0;i--)
			     sn[i]=sn[i-1];
			 sn[0].x++;
			 check();
			 if(change)  return;
			 print_snake();
			 delay(n);
		  }
	   }
      }
   else if(scan==77)
       {
	if(!a[2])     //pressed  RIGHT && prevoiusly not going LEFT
	  {
		for(int t=0;t<4;t++)
		     a[t]=0;
		 a[3]=1;
		 while(sn[0].x<=Xn && !kbhit())
		    {
			 for(int i=length-1;i>0;i--)
			     sn[i]=sn[i-1];
			 sn[0].x++;
			 check();
			 if(change)  return;
			 print_snake();
			 delay(n);
		    }
	    }

	 else{        //pressed  RIGHT && prevoiusly going LEFT
		 while(sn[0].x>=X0 && !kbhit())
		   {
		      for(int i=length-1;i>0;i--)
			  sn[i]=sn[i-1];
		      sn[0].x--;
		      check();
		      if(change)  return;
		      print_snake();
		      delay(n);
		   }
	      }
	}
   else if(scan==72)
      {
	if(!a[1])    //pressed UP && prevoiusly not going DOWN
	    {
	       for(int t=0;t<4;t++)
		     a[t]=0;
		a[0]=1;
		while(sn[0].y>=Y0 && !kbhit())
		   {
		      for(int i=length-1;i>0;i--)
			 sn[i]=sn[i-1];
		      sn[0].y--;
		      check();
		      if(change)  return;
		      print_snake();
		      delay(n);
		   }
	     }
	else {                 //pressed UP && prevoiusly going DOWN
		 while(sn[0].y<=Yn && !kbhit())
		   {
		       for(int i=length-1;i>0;i--)
			   sn[i]=sn[i-1];
		       sn[0].y++;
		       check();
		       if(change)  return;
		       print_snake();
		       delay(n);
		   }
	      }
      }
   else	if(scan==80)
      {
	  if(!a[0])  //pressed DOWN && prevoiusly not going UP
	     {
		 for(int t=0;t<4;t++)
		    a[t]=0;
		 a[1]=1;
		 while(sn[0].y<=Yn && !kbhit())
		   {
		     for(int i=length-1;i>0;i--)
			   sn[i]=sn[i-1];
		      sn[0].y++;
		      check();
		      if(change)  return;
		      print_snake();
		      delay(n);
		   }
	      }
	   else {              //pressed DOWN && prevoiusly going UP
		    while(sn[0].y>=Y0 && !kbhit())
		      {
			 for(int i=length-1;i>0;i--)
			      sn[i]=sn[i-1];
			 sn[0].y--;
			 check();
			 if(change)  return;
			 print_snake();
			 delay(n);
		      }
		}
	}
   else if(scan==1)    exit(1);
  }
  textcolor(CYAN+BLINK);
  gotoxy(X0+30,Y0+10);
  cprintf("GAME OVER!");
  delay(3000);
  exit(1);
}

void main()
{
   while(level<5)
     {
	change=0;
	clrscr();
	snake S;
	int a[4]={0,0,0,0};      //UP,DOWN,LEFT,RIGHT
	   level = 6-n/40;
	   S.Draw_boundary();
	   S.print_snake();
	   S.Move(a,n);
     }
}
