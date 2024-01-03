void aout(int col,char *str)
{
  textcolor(col);
  cprintf(str);
  textcolor(7);
}

char status_bar(char *str)
{
 char ch1;
  gotoxy(1,24);
  textbackground(1);
  aout(1,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴");
  gotoxy(1,24);
  textcolor(139);
  cprintf(str);
  ch1 = getch();
  textcolor(7);
  textbackground(0);
  return ch1;
}

void exit_main()
{
}
void welcome_screen()
{

  textcolor(7);
  textbackground(0);
  clrscr();
  aout(12,"Welcome_to_seico's_data_management_program");
  cout<<"\nVersion 1.0.0";
  cout<<"\nCreated by Amit kumar";
  cout<<"\nFor technical details and source code contact at..."
	<<"\n76/10 purvawali ganeshpur\nRoorkee\nINDIA\nPh - 71349";

  status_bar("Press any key to continue...");
}

