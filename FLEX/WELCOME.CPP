void welcome_screen()
{
  setbkcolor(1);

  settextjustify(CENTER_TEXT,CENTER_TEXT);
  settextstyle(4,0,6);
  outtextxy(320,90,"to");
  setcolor(11);
  settextstyle(10,0,3);
  outtextxy(320,170,"IMAGE PROCESSOR - 2000");
  outtextxy(321,171,"IMAGE PROCESSOR - 2000");

  setcolor(10);
  settextstyle(5,0,3);
  outtextxy(320,220,"Created by Amit Kumar.");
  setcolor(7);
  settextstyle(6,0,3);
  outtextxy(320,270,"Roorkee Ph 71349");


  settextjustify(LEFT_TEXT,TOP_TEXT);

  void *buff1,*buff2;
  int area1,area2,count;
  setcolor(14);
  settextstyle(1,0,5);
  outtextxy(2,10,"Wel");
  outtextxy(525,10,"come");

  area1 = imagesize(2,18,70,55);
  area2 = imagesize(525,18,635,55);

  buff1 = malloc(area1);
  buff2 = malloc(area2);

  getimage(2,18,70,55,buff1);
  getimage(525,18,635,55,buff2);

  putimage(2,18,buff1,XOR_PUT);
  putimage(525,18,buff2,XOR_PUT);

  int p1 = 2,p2 = 525;

  do{
     if (p1 <= 256) p1++;
     if (p2 >= 320) p2--;


     putimage(p1,18,buff1,XOR_PUT);
     putimage(p2,18,buff2,XOR_PUT);

     delay(10);

     putimage(p1,18,buff1,XOR_PUT);
     putimage(p2,18,buff2,XOR_PUT);

     if ((p1 >= 256) && (p2 <= 320)) break;

  }while(!kbhit());

     putimage(p1,18,buff1,XOR_PUT);
     putimage(p2,18,buff2,XOR_PUT);
   settextstyle(10,0,3);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
     count = 0;
     do {
	if (count >= 15) count = 0;
	count ++;
	setcolor(count);
	outtextxy(320,170,"IMAGE PROCESSOR - 2000");
	delay(600);
	outtextxy(321,171,"IMAGE PROCESSOR - 2000");
	delay(600);
	outtextxy(322,172,"IMAGE PROCESSOR - 2000");
      }while(!kbhit());

  getch();

  free(buff1);
  free(buff2);
}