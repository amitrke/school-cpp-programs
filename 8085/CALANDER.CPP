#include<iostream.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>
#define BASE_YR 1999
#define BASE_DT 1
#define BASE_MT 1
int check_date_err(int m,int d,int y);
int isleap(int year);
long calculate_date(int m, int d,int y);
int getdays(int m,int y);

void main()
{
  clrscr();
  int mm,dd,yyyy;
  cout << "Enter date (MM/DD/YYYY) : ";
  scanf("%d/%d/%d", &mm,&dd,&yyyy);
  if (check_date_err(mm,dd,yyyy) == 1)
    {
      cout<<"\ERROR: Invalid date entered \nAborting..";
      exit(0);
    }
  cout<<"result = "<<calculate_date(mm,dd,yyyy);
  getch();
}
int check_date_err(int m,int d,int y)
{
  if ((y < 1970) || (y > 2050)) return 1;
  if ((m > 12)||( m < 1)) return 1;
  if (d < 1) return 1;
  switch (m)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:if (d > 31) return 1;break;
      case 4:
      case 6:
      case 9:
      case 11: if (d > 30) return 1;break;
      case 2 :
	  {
	    if (isleap(y) == 1)
	      {
		if (d > 29) return 1;
	      }
	    else
	      {
		if (d > 28) return 1;
	      }
	      break;
	  }
    }
}
int isleap(int year)
{
  if ((year == 2000)||(year == 1995)) return 1;
}
long calculate_date(int m, int d,int y)
{
  long result = 0;
  int how_many_yrs,temp;
  if (y >= BASE_YR)
    {
      //first adding yrs
      how_many_yrs = ((y - BASE_YR) - 1);
      for(temp = 0;temp <= how_many_yrs;temp++)
	{
	  if ( isleap(BASE_YR + temp) == 1 )
	    result = result + 366;
	  else
	     result = result + 365;
	}
      //now adding months

	for (temp = BASE_MT; temp <= (m-1) ; temp ++)
	  {
	    result = result + getdays(temp,y);
	  }
      // now adding days
	result = result + d;
    }

  if (y < BASE_YR)
    {
      //first sub yrs
      how_many_yrs = ((BASE_YR - y) - 1);
      for(temp = 0;temp <= how_many_yrs;temp++)
	{
	  if ( isleap(BASE_YR - temp) == 1 )
	    result = result - 366;
	  else
	     result = result - 365;
	}
      //now sub months

	for (temp = BASE_MT; temp <= (m-1) ; temp ++)
	  {
	    result = result - getdays(temp,y);
	  }
      // now sub days
	result = result - d;
    }
    return result;
}
int getdays(int m,int y)
{
 int result;
  switch (m)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:result = 31;break;
      case 4:
      case 6:
      case 9:
      case 11: result = 30;break;
      case 2 :
	  {
	    if (isleap(y) == 1)
	      result = 29;
	    else
	      result = 28;
	      break;
	  }
    }
  return result;
}