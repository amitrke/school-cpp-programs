#define __run1__
#include<iostream.h>

#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include"hexcal.cpp"
// declaring cpu registers
  int a,b,c,d,e,h,l,bc,de,hl,sp,pc;
//declaring flags
  int cs,ac,z,s,p;
  char far *tempstring ;


void refresh_common(int fcs, int fac, int fz, int fs, int fp);
void pushme(int datatopush);

void ud_b_c();
void ud_d_e();
void ud_h_l();
void ud_hl();
void ud_bc();
void ud_de();

int main(int argc,char *argv[])
{

  clrscr();
  cout<<"Welcome to 8085 instruction code simulator program..";

  if (argc == 1)
    {
      cout << "\nERROR : You for got to enter the filename"
	   << "\n\nUsage.\n\tRUN1 <options> <filename>";
      exit(0);
    }


  FILE *fp;
  if ( (fp = fopen(argv[1],"r")) == NULL )
     {
	cout<<"\nERROR : Unable to open source file for input."
	    <<"\nAborting";
	exit(0);
     }
  cout<<"\nSource code file sucessfully opened.";


  //initilizing all variables to zero
  a=b=c=d=e=h=l=bc=de=hl=sp=pc = 0;
  bc = 1300;
  //initilizing all flags to zero
  cs=ac=z=s=p=0;

  cout<<"\nCPU registers initilised..";

  //defining structure for instruction
  struct instruction{
    int addr;//address of instruction
    int code;//instruction code
  }ins;

  //defining structure for labels
  struct lab1{
    int flag;//to check if a label is called or not
    int addr;//location that is to be seeked
  }label_chk;

  //two temp variables

  int temphex;

  //label
  int lastcode = 0;
  execute_program:

  label_chk.flag = 0;
   rewind(fp);
  //reading and execution of code starts here
   fscanf(fp,"%s %s",tempstring,tempstring);

   do{
      if (feof(fp)) break;
      fscanf(fp,"%x",&ins.addr);
      fscanf(fp,"%x",&ins.code);
      if (lastcode == ins.code)
	{
	   fscanf(fp,"%x",&ins.code);
	   if (lastcode == ins.code)
	     {
		cout<<"\n\nInvalid instruction code file ("<<argv[1]<<") !"
		    <<"\nAborting..\n\n\n\n\n\n\n";
		exit(0);
	     }
	}
      lastcode = ins.code;
      //check if this address is requested by some label
      if ((label_chk.flag == 1) && (label_chk.addr == ins.addr))
	{
	  label_chk.flag = 0;
	}

     //instruction is analized here

     switch (ins.code)
       {

	   case 0xd2:// jnc data
	   {
	     fscanf(fp,"%x",&temphex);
	     if ((label_chk.flag == 0) && (cs==1))
	      {
		label_chk.flag = 1;
		label_chk.addr = temphex;
		refresh_common(8,8,8,8,8);
	      }
	      break;
	     }

	 /*  case 0x0c://inr c
	     {
	       if (label_chk.flag == 0)
		 {
		   c++;
		   refresh_flags(7,7,7,7,7);
		 }
	       break;
	     }
	     */
	   case 0x32://sta data
	     {
	       fscanf(fp,"%x",&temphex);
		if (label_chk.flag == 0)
		 {               //memory calculation
		   printf("\nSTA %d written at memory location %x",a,temphex);
		   refresh_common(8,8,8,8,8);
		 }
		break;
	     }
	  /* case 0x79: //mov a,c
	     {
	       if (label_chk.flag == 0)
		 {
		   a = c;
		 }
	       break;
	     }
	   */


	  case 0xce: // aci data
	    {
		fscanf(fp,"%x",&temphex);
		if (label_chk.flag == 0)
		  {
		    a = a + temphex + cs;
		    refresh_common(7,7,7,7,7);

		  }
		break;
	    }
	  case 0x8f:// adc a
	    {
		if (label_chk.flag == 0)
		  {
		    a = a + a + cs;
		    refresh_common(7,7,7,7,7);
		  }
	    break;
	    }
	  case 0x88:// adc b
	    {
		if (label_chk.flag == 0)
		  {
		    a = a + b + cs;
		    refresh_common(7,7,7,7,7);
		  }
		break;
	     }
	  case 0x89:// adc c
	     {
	       if (label_chk.flag == 0)
		  {
		      a = a + c + cs;
		      refresh_common(7,7,7,7,7);
		  }
	       break;
	     }
	  case 0x8a:// adc d
	      {
		 if (label_chk.flag == 0)
		   {
		     a = a + d + cs;
		     refresh_common(7,7,7,7,7);
		   }
		 break;
	      }
	  case 0x8b:// adc e
	       {
		 if (label_chk.flag == 0)
		     {
			a = a + e + cs;
			refresh_common(7,7,7,7,7);
		     }
		 break;
		}
	  case 0x8c:// adc h
		{
		  if (label_chk.flag == 0)
		    {
		      a = a + h + cs;
		      refresh_common(7,7,7,7,7);
		    }
		  break;
		}
	  case 0x8d:// adc l
	       {
		 if (label_chk.flag == 0)
		    {
		     a = a + l + cs;
		     refresh_common(7,7,7,7,7);
		   }
		   break;
	       }
	  case 0x8e:// adc m
	      {
		if (label_chk.flag == 0)
		    {
		      a = a + hl + cs;
		      refresh_common(7,7,7,7,7);
		    }
		break;
	      }

	 // add instructions

	 case 0x87://add a
	     {
	       if  (label_chk.flag == 0)
		 {
		    a = a + a;
		    refresh_common(7,7,7,7,7);
		  }
		 break;
	      }
	 case 0x80://add b
	      {
		if  (label_chk.flag == 0)
		    {
			a = a + b;
			refresh_common(7,7,7,7,7);
		    }
		break;
	       }
	 case 0x81://add c
	       {
		 if  (label_chk.flag == 0)
		    {
		     a = a + c;
		     refresh_common(7,7,7,7,7);
		    }
		 break;
	       }
	case 0x82://add d
	      {
		if  (label_chk.flag == 0)
		   {
		     a = a + d;
		     refresh_common(7,7,7,7,7);
		   }
		break;
	      }
	case 0x83://add e
	  {
	     if  (label_chk.flag == 0)
	      {
		a = a + e;
		refresh_common(7,7,7,7,7);
	      }
	     break;
	  }
	case 0x84://add h
	  {
	    if  (label_chk.flag == 0)
	       {
		   a = a + h;
		   refresh_common(7,7,7,7,7);
		}
	       break;
	   }
	 case 0x85://add l
	    {
	       if  (label_chk.flag == 0)
		 {
		   a = a + l;
		   refresh_common(7,7,7,7,7);
		 }
	       break;
	     }
	 case 0x86://add m
	      {
		if  (label_chk.flag == 0)
		  {
		    a = a + hl;
		    refresh_common(7,7,7,7,7);
		  }
		break;
	      }

	 case 0xc6: // adi data
	      {
		fscanf(fp,"%x",&temphex);
		if (label_chk.flag == 0)
		   {
		     a = a + temphex;
		     refresh_common(7,7,7,7,7);
		   }
		break;
	       }

	   //ana ins

	  case 0xa7://ana a
	     {
	       if  (label_chk.flag == 0)
		  {
		    a = a & a;
		    refresh_common(0,1,7,7,7);
		   }
		  break;
	     }
	   case 0xa0://ana b
	       {
		  if  (label_chk.flag == 0)
		     {
		       a = a & b;
		       refresh_common(0,1,7,7,7);
		     }
	       break;
	       }
	    case 0xa1://ana c
		{
		   if  (label_chk.flag == 0)
		      {
			  a = a & c;
			  refresh_common(0,1,7,7,7);
		      }
		   break;
		 }
	    case 0xa2://ana d
		 {
		    if  (label_chk.flag == 0)
			{
			   a = a & d;
			   refresh_common(0,1,7,7,7);
			 }
			break;
		  }
	   case 0xa3://ana e
		{
		  if  (label_chk.flag == 0)
		     {
		       a = a & e;
		       refresh_common(0,1,7,7,7);
		     }
		  break;
		}
	   case 0xa4://ana h
	       {
		 if  (label_chk.flag == 0)
		      {
			a = a & h;
			refresh_common(0,1,7,7,7);
		      }
		 break;
	       }
	   case 0xa5://ana l
	       {
		 if  (label_chk.flag == 0)
		    {
		      a = a & l;
		      refresh_common(0,1,7,7,7);
		     }
		 break;
	       }
	   case 0xa6://ana m
	       {
		 if  (label_chk.flag == 0)
		     {
			a = a & hl;
			refresh_common(0,1,7,7,7);
		      }
		     break;
	       }

	  case 0xe6://ani data
		{
		  fscanf(fp,"%x",&temphex);
		  if  (label_chk.flag == 0)
		     {
		       a = a & temphex;
		       refresh_common(0,1,7,7,7);
		     }
		  break;
		}

	    case 0xcd: //call label
		 {
		    fscanf(fp,"%x",&temphex);
		    if  (label_chk.flag == 0)
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			 }
		    break;
		  }
	    case 0xdc: //cc label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && (cs == 1))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			 }
		    break;
		  }
	    case 0xfc: //cm label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && (s == 1))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			 }
		    break;
		  }
	     case 0x2f: //cma label
	       {
		 if (label_chk.flag == 0)
		 {

		 //find compliment of a ***********
		 refresh_common(7,8,8,8,8);
		 }
		 break;
	       }
	     case 0x3f://cmc
	       {
		if (label_chk.flag == 0)
		 {

		 refresh_common(8,2,8,8,8);
		 }
		 break;
	       }
	     case 0xbf://cmp a
	       {
		 if (label_chk.flag == 0)
		 {

		 temphex = a;
		 a = a - a;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
	       }
	       break;
	       }
	     case 0xb8://cmp b
	       {
		if (label_chk.flag == 0)
		 {

		 temphex = a;
		 a = a - b;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }
	     case 0xb9://cmp c
	       {

		if (label_chk.flag == 0)
		 {

		 temphex = a;
		 a = a - c;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }

	     case 0xba://cmp d
	       {

		if (label_chk.flag == 0)
		 {

		 temphex = a;
		 a = a - d;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }

	     case 0xbb://cmp e
	       {
		if (label_chk.flag == 0)
		 {
		 temphex = a;
		 a = a - e;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }
	     case 0xbc://cmp h
	       {
		if (label_chk.flag == 0)
		 {
		 temphex = a;
		 a = a - h;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }
	     case 0xbd://cmp l
	       {
		if (label_chk.flag == 0)
		 {
		 temphex = a;
		 a = a - l;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }
	     case 0xbe://cmp m
	       {
		if (label_chk.flag == 0)
		 {
		 temphex = a;
		 a = a - hl;
		 refresh_common(7,7,7,7,7);
		 a = temphex;
		 }
		 break;
	       }
	     case 0xd4: //cnc label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( cs == 0))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }

	     case 0xc4: //cnz label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( z == 0))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }
	     case 0xf4: //cp label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( s == 0))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }
	     case 0xec: //cpe label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( p == 1))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }

	     case 0xfe: //cpi label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( p == 1))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }
	     case 0xe4: //cpo label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( p == 0))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }
	     case 0xcc: //cz label
	       {
		    fscanf(fp,"%x",&temphex);
		    if  ((label_chk.flag == 0) && ( z == 1))
			{
			  label_chk.flag = 1;
			  label_chk.addr = temphex;
			  pushme(temphex);
			  refresh_common(8,8,8,8,8);
			}
		    break;
		  }
	       case 0x27: //daa
		  {
		    if (label_chk.flag == 0)
		      {
		    // ******************** memeory calculations
		    refresh_common(8,8,8,8,8);
		    } break;

		  }
	       case 0x09: //dad b
		 {
		  if (label_chk.flag == 0)
		      {
		   hl = hl + bc;
		   ud_h_l();
		   refresh_common(7,8,8,8,8);
		   }break;

		 }
	      case 0x19: //dad d
		 {
		  if (label_chk.flag == 0)
		      {
		   hl = hl + de;
		   ud_h_l();
		   refresh_common(7,8,8,8,8);
		   }
		   break;

		 }
	      case 0x29: //dad h
		 {
		 if (label_chk.flag == 0)
		      {
		   hl = hl + hl;
		   ud_h_l();
		   refresh_common(7,8,8,8,8);
		   }
		   break;

		 }
	     case 0x3d://dcr a
		{
		 if (label_chk.flag == 0)
		      {
		  a--;
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x05://dcr b
		{
		 if (label_chk.flag == 0)
		      {
		  b--;
		  ud_bc();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x0d://dcr c
		{
		 if (label_chk.flag == 0)
		      {
		  c--;
		  ud_bc();
		  refresh_common(8,7,7,7,7);
		  }break;
		}
	     case 0x15://dcr d
		{
		 if (label_chk.flag == 0)
		      {
		  d--;
		  ud_de();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x1d://dcr e
		{
		 if (label_chk.flag == 0)
		      {
		  e--;
		  ud_de();
		  refresh_common(8,7,7,7,7);
		  }break;
		}
	     case 0x25://dcr h
		{
		 if (label_chk.flag == 0)
		      {
		  h--;
		  ud_hl();
		  refresh_common(8,7,7,7,7);
		  }break;
		}
	     case 0x2d://dcr l
		{
		 if (label_chk.flag == 0)
		  {
		  l--;
		  ud_hl();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x35://dcr m
		{
		 if (label_chk.flag == 0)
		  {
		  hl--;
		  ud_h_l();
		  refresh_common(8,7,7,7,7);
		  }break;
		}

	     case 0x0b://dcx b
		{
		 if (label_chk.flag == 0)
		  {
		  bc--;
		  ud_b_c();
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x1b://dcx d
		{
		  if (label_chk.flag == 0)
		  {
		  de--;
		  ud_d_e();
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x2b://dcx h
		{
		  if (label_chk.flag == 0)
		  {
		  hl--;
		  ud_h_l();
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x3b://dcx sp
		{
		 if (label_chk.flag == 0)
		  {
		  sp--;
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x3c://inr a
		{
		  if (label_chk.flag == 0)
		  {
		  a++;
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x04://inr b
		{
		 if (label_chk.flag == 0)
		  {
		  b++;
		  ud_bc();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x0c://inr c
		{
		  if (label_chk.flag == 0)
		  {
		  c++;
		  ud_bc();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x14://inr d
		{
		  if (label_chk.flag == 0)
		  {
		  d++;
		  ud_de();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x1c://inr e
		{
		 if (label_chk.flag == 0)
		  {
		  e++;
		  ud_de();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x24://inr h
		{
		  if (label_chk.flag == 0)
		  {
		  h++;
		  ud_hl();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x2c://inr l
		{
		 if (label_chk.flag == 0)
		  {
		  l++;
		  ud_hl();
		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x34://inr m
		{
		 if (label_chk.flag == 0)
		  {
		  hl++;         //memory calculations

		  refresh_common(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x03://inx b
		{
		 if (label_chk.flag == 0)
		  {
		  bc++;
		  ud_b_c();
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x13://inx d
		{
		 if (label_chk.flag == 0)
		  {
		  de++;
		  ud_d_e();
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x23://inx h
		{
		 if (label_chk.flag == 0)
		  {
		  hl++;
		  ud_h_l();
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x33://inx sp
		{
		  if (label_chk.flag == 0)
		  {
		  sp++;
		  refresh_common(8,8,8,8,8);
		  }
		  break;
		}

	     case 0x7f: //mov a,a
	     {
	       if (label_chk.flag == 0)
		 {
		   a = a;
		   refresh_common(8,8,8,8,8);
		 }
	       break;
	     }

	     case 0x78: //mov a,b
	      {
	       if (label_chk.flag == 0)
		   a = b;
		   refresh_common(8,8,8,8,8);
	       break;
	      }

	     case 0x79: //mov a,c
	      {
	       if (label_chk.flag == 0)
		   a = c;
		   refresh_common(8,8,8,8,8);
	       break;
	      }
	     case 0x7a: //mov a,d
	      {
	       if (label_chk.flag == 0)
		   a = d;
		   refresh_common(8,8,8,8,8);
	       break;
	      }
	     case 0x7b: //mov a,e
	      {
	       if (label_chk.flag == 0)
		   a = e;
		   refresh_common(8,8,8,8,8);
	       break;
	      }

	     case 0x7c: //mov a,h
	      {
	       if (label_chk.flag == 0)
		   a = h;
		   refresh_common(8,8,8,8,8);
	       break;
	      }
	     case 0x7d: //mov a,l
	      {
	       if (label_chk.flag == 0)
		   a = l;
		   refresh_common(8,8,8,8,8);
	       break;
	      }
	    case 0x7e: //mov a,m
	      {
	       if (label_chk.flag == 0)
		   a = hl;//do memory operation
		   refresh_common(8,8,8,8,8);
	       break;
	      }
	    case 0x47: //mov b,a
	      {
	       if (label_chk.flag == 0)
		   {
		    b = a;
		     ud_bc();
		     refresh_common(8,8,8,8,8);
		    }
	       break;
	      }
	  case 0x40: //mov b,b
	      {
	       if (label_chk.flag == 0)
		   {
		   b = b;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	  case 0x41: //mov b,c
	      {
	       if (label_chk.flag == 0)
		   {
		   b = c;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	  case 0x42: //mov b,d
	      {
	       if (label_chk.flag == 0)
		   {
		   b = d;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	  case 0x43: //mov b,e
	      {
	       if (label_chk.flag == 0)
		   {
		   b = e;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	  case 0x44: //mov b,h
	      {
	       if (label_chk.flag == 0)
		   {
		   b = h;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	  case 0x45: //mov b,l
	      {
	       if (label_chk.flag == 0)
		   {
		   b = l;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x46: //mov b,m
	      {
	       if (label_chk.flag == 0)
		   {
		   b = d;    //memory calculation
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x4f: //mov c,a
	      {
	       if (label_chk.flag == 0)
		   {
		   c = a;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x48: //mov c,b
	      {
	       if (label_chk.flag == 0)
		   {
		   c = b;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x49: //mov c,c
	      {
	       if (label_chk.flag == 0)
		   {
		   c = c;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x4a: //mov c,d
	      {
	       if (label_chk.flag == 0)
		   {
		   c = d;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x4b: //mov c,e
	      {
	       if (label_chk.flag == 0)
		   {
		   c = e;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x4c: //mov c,h
	      {
	       if (label_chk.flag == 0)
		   {
		   c = h;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x4d: //mov c,l
	      {
	       if (label_chk.flag == 0)
		   {
		   c = l;
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x4e: //mov c,m
	      {
	       if (label_chk.flag == 0)
		   {
		   c = l;//memory calculation
		   ud_bc();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x57: //mov d,a
	      {
	       if (label_chk.flag == 0)
	       {
		   d = a;
		   ud_de();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x50: //mov d,b
	      {
	       if (label_chk.flag == 0)
		 {
		   d = b;
		   ud_de();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x51: //mov d,c
	      {
	       if (label_chk.flag == 0)
		   {
		   d = c;
		   ud_de();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x52: //mov d,d
	      {
	       if (label_chk.flag == 0)
		   {
		   d = d;
		   ud_de();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x53: //mov d,e
	      {
	       if (label_chk.flag == 0)
		   {
		   d = e;
		   ud_de();
		   refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x54: //mov d,h
	      {
	       if (label_chk.flag == 0)
		   {
		     d = h;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x55: //mov d,l
	      {
	       if (label_chk.flag == 0)
		   {
		    d = l;
		    ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x56: //mov d,m
	      {
	       if (label_chk.flag == 0)
		   {
		     d = l;//memory calculations
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }

	  case 0x5f: //mov e,a
	      {
	       if (label_chk.flag == 0)
		   {
		     e = a;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x58: //mov e,b
	      {
	       if (label_chk.flag == 0)
		   {
		     e = b;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x59: //mov e,c
	      {
	       if (label_chk.flag == 0)
		   {
		     e = c;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x5a: //mov e,d
	      {
	       if (label_chk.flag == 0)
		   {
		     e = d;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x5b: //mov e,e
	      {
	       if (label_chk.flag == 0)
		   {
		     e = e;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x5c: //mov e,h
	      {
	       if (label_chk.flag == 0)
		   {
		     e = h;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x5d: //mov e,l
	      {
	       if (label_chk.flag == 0)
		   {
		     e = l;
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x5e: //mov e,m
	      {
	       if (label_chk.flag == 0)
		   {
		     d = l;//memory calculations
		     ud_de();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }

	 case 0x67: //mov h,a
	      {
	       if (label_chk.flag == 0)
		   {
		     h = a;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x60: //mov h,b
	      {
	       if (label_chk.flag == 0)
		   {
		     h = b;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x61: //mov h,c
	      {
	       if (label_chk.flag == 0)
		   {
		     h = c;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x62: //mov h,d
	      {
	       if (label_chk.flag == 0)
		   {
		     h = d;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x63: //mov h,e
	      {
	       if (label_chk.flag == 0)
		   {
		     h = e;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x64: //mov h,h
	      {
	       if (label_chk.flag == 0)
		   {
		     h = h;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x65: //mov h,l
	      {
	       if (label_chk.flag == 0)
		   {
		     h = l;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x66: //mov h,m
	      {
	       if (label_chk.flag == 0)
		  {
		    h = l;//memory calculations
		    ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }


	  case 0x6f: //mov l,a
	      {
	       if (label_chk.flag == 0)
		   {
		     l = a;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x68: //mov l,b
	      {
	       if (label_chk.flag == 0)
		   {
		     l = b;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x69: //mov l,c
	      {
	       if (label_chk.flag == 0)
		   {
		     l = c;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x6a: //mov l,d
	      {
	       if (label_chk.flag == 0)
		   {
		     l = d;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x6b: //mov l,e
	      {
	       if (label_chk.flag == 0)
		   {
		     l = e;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x6c: //mov l,h
	      {
	       if (label_chk.flag == 0)
		   {
		     l = h;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x6d: //mov l,l
	      {
	       if (label_chk.flag == 0)
		   {
		     l = l;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x6e: //mov l,m
	      {
	       if (label_chk.flag == 0)
		   {
		     l = l;//memory calculations
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x70: //mov m,b
	      {
	       if (label_chk.flag == 0)
		   {
		     h = a;//memory calculations
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x71: //mov m,b
	      {
	       if (label_chk.flag == 0)
		   {
		     h = b; //memory calculations
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 /*case 0x72: //mov h,c
	      {
	       if (label_chk.flag == 0)
		   {         //mem calc , codes to be corrected
		     h = c;
		     ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x62: //mov h,d
	      {
	       if (label_chk.flag == 0)
		   {
		    h = d;
		    ud_hl();
		     refresh_common(8,8,8,8,8);
		   }
	       break;
	      }
	 case 0x63: //mov h,e
	      {
	       if (label_chk.flag == 0)
		   {
		    h = e;
	       break;
	      }
	 case 0x64: //mov h,h
	      {
	       if (label_chk.flag == 0)
		   h = h;
	       break;
	      }
	 case 0x65: //mov h,l
	      {
	       if (label_chk.flag == 0)
		   h = l;
	       break;
	      }
	 case 0x66: //mov h,m
	      {
	       if (label_chk.flag == 0)
		   d = l;//memory calculations
	       break;
	      }

	   */
	case  0x3e: //mvi a,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		a = temphex;
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x06: //mvi b,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		b = temphex;
		ud_bc();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x0e: //mvi c,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		c = temphex;
		ud_bc();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x16: //mvi d,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		d = temphex;
		ud_de();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x1e: //mvi e,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		e = temphex;
		ud_de();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x26: //mvi h,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		h = temphex;
		ud_hl();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x2e: //mvi l,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		l = temphex;
		ud_hl();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }
	case  0x36: //mvi m,data
	    {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		hl = temphex;//memory calculations
		ud_hl();
		refresh_common(8,8,8,8,8);
	      }
	      break;
	    }

	case 0x00: //nop
	   {
	     if (label_chk.flag == 0)
	      {
		refresh_common(8,8,8,8,8);
	      }
	      break;
	   }

	case 0xb7: //ora a
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | a;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb0: //ora b
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | b;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb1: //ora c
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | c;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb2: //ora d
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | d;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb3: //ora e
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | d;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb4: //ora h
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | h;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb5: //ora l
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | l;
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
	case 0xb6: //ora m
	   {
	     if (label_chk.flag == 0)
	      {
		a = a | hl;//memory calculations
		refresh_common(0,0,7,7,7);
	      }
	      break;
	   }
       }//end of switch
   }while(!feof(fp));
   if (label_chk.flag == 1) goto execute_program;
       //if the first pass is over and we slill have to serch a label the
       //strt the nest pass

   fclose(fp);//close the file

   //now showing condition of registers
   printf("\n **** Register contents *****");
   printf("\n A = %x B = %x C = %x D = %x E = %x H = %x L = %x",a,b,c,d,e,h,l);   printf("\n PC = %x Sp = %x ",pc,sp);
   printf("\n BC = %x DE = %x HL = %x",bc,de,hl);

   //flags
   printf("\n **** Flag contents *****");
   printf("\n CS = %d AC = %d Z = %d P = %d S = %d\n\n",cs,ac,z,p,s);

   return 0;
}//end of main

void refresh_common(int fcs, int fac, int fz, int fs, int fp)
{
  switch (fcs)
    {
      case 8 :break;
      case 0 : cs = 0 ; break;
      case 1 : cs = 1 ; break;
      case 2 :
	    {
	      if ( cs == 1) cs = 0;
	      if ( cs == 0) cs = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a > 255)
		{
		  cs = 1;
		  a = a - 256;
		}
	      else
		{
		  cs = 0;
		}
	      break;
	    }
    }//end of switch fcs

  switch (fac)
    {
      case 8 :break;
      case 0 : ac = 0 ; break;
      case 1 : ac = 1 ; break;
      case 2 :
	    {
	      if ( ac == 1) ac = 0;
	      if ( ac == 0) ac = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a > 255)
		{
		  ac = 1;
		  a = a - 256;
		}
	      else
		{
		  ac = 0;
		}
	      break;
	    }
    }//end of switch fac

  switch (fz)
    {
      case 8 :break;
      case 0 : z = 0 ; break;
      case 1 : z = 1 ; break;
      case 2 :
	    {
	      if ( z == 1) z = 0;
	      if ( z == 0) z = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a == 0)
		{
		  z = 1;
		}
	      else
		{
		  z = 0;
		}
	      break;
	    }
    }//end of switch z

    switch (fs)
    {
      case 8 :break;
      case 0 : s = 0 ; break;
      case 1 : s = 1 ; break;
      case 2 :
	    {
	      if ( s == 1) s = 0;
	      if ( s == 0) s = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a < 0)
		{
		  s = 1;
		  a = abs(a);
		}
	      else
		{
		  s = 0;
		}
	      break;
	    }
    }//end of switch s


    switch (fp)
    {
      case 8 :break;
      case 0 : p = 0 ; break;
      case 1 : p = 1 ; break;
      case 2 :
	    {
	      if ( p == 1) p = 0;
	      if ( p == 0) p = 1;
	      break;
	    }
      /*case 7 :
	    {
	      if (a < 0)
		{
		  s = 1;
		  a = abs(a);
		}
	      else
		{
		  s = 0;

		}
	      break;
	    }
      */
    }//end of switch s
}

void ud_hl()
{
  // update hl
  char s1[32],s2[16];
  h = 26;l = 33;
  strcpy(s1,dec_2_binstring(h));
  strcpy(s2,dec_2_binstring(l));
  strcat(s1,s2);
  hl = str_2_dec(s1);
}

void ud_bc()
{
  // update bc
  char s1[32],s2[16];
  strcpy(s1,dec_2_binstring(b));
  strcpy(s2,dec_2_binstring(c));
  strcat(s1,s2);
  bc = str_2_dec(s1);
}
void ud_de()
{
  // update de
  char s1[32],s2[16];
  strcpy(s1,dec_2_binstring(d));
  strcpy(s2,dec_2_binstring(e));
  strcat(s1,s2);
  de = str_2_dec(s1);
}

void pushme(int datatopush)
{
  datatopush = datatopush;
}
void ud_b_c()
{
   long templong;
   char tempstring2[16],m[16];

   //update b&c
   strcpy(tempstring2 , int_2_string(bc));
   strcpy(m,tempstring2);
   templong = str_2_8bit_lower(m);
   c = bin_2_dec(templong);
   templong = str_2_8bit_higher(m);
   b = bin_2_dec(templong);
}
void ud_d_e()
{
   long templong;
   char tempstring2[16],m[16];
   //update de pair
   strcpy(tempstring2 , int_2_string(de));
   strcpy(m,tempstring2);
   templong = str_2_8bit_lower(tempstring2);
   e = bin_2_dec(templong);
   templong = str_2_8bit_higher(m);
   d = bin_2_dec(templong);
}
void ud_h_l()
{
  long templong;
   char tempstring2[16],m[16];
  //update hl pair
   strcpy(tempstring2 , int_2_string(hl));
   strcpy(m,tempstring2);
   templong = str_2_8bit_lower(tempstring2);
   l = bin_2_dec(templong);
   templong = str_2_8bit_higher(m);
   h = bin_2_dec(templong);
}