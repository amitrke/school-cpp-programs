
void create_new_main_file()
{
  // new main file is created here
  ofstream mainfil("main.txt",ios::out | ios :: binary );
  if (!mainfil)
    {
      cout<<"\nERROR : Cannot create data file..Aborting";
      exit(0);
    }
  mainfil.close();
}