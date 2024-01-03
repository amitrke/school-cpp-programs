#include<iostream.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>

// declaring cpu registers
  int a,b,c,d,e,h,l,bc,de,hl,sp,pc;
//declaring flags
  int cs,ac,z,s,p;


void refresh_flags(int fcs, int fac, int fz, int fs, int fp);
void refresh_flags_pairreg(int fcs, int fac, int fz, int fs, int fp);
void pushme(int datatopush);

void main(int argc,char *argv[])
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
  char *tempstring;
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
	 case 0x0e:// mvi c data
	   {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		c = temphex;
		refresh_flags(8,8,8,8,8);
	      }
	      break;
	   }

	  case 0x3e:// mvi a data
	   {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		a = temphex;
		refresh_flags(8,8,8,8,8);
	      }
	      break;
	   }
	  case 0x06:// mvi b data
	   {
	     fscanf(fp,"%x",&temphex);
	     if (label_chk.flag == 0)
	      {
		b = temphex;
		refresh_flags(8,8,8,8,8);
	      }
	      break;
	     }
	   case 0xd2:// jnc data
	   {
	     fscanf(fp,"%x",&temphex);
	     if ((label_chk.flag == 0) && (cs==1))
	      {
		label_chk.flag = 1;
		label_chk.addr = temphex;
		refresh_flags(8,8,8,8,8);
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
		 {
		   printf("\nSTA %d written at memory location %x",a,temphex);
		   refresh_flags(8,8,8,8,8);
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
		    refresh_flags(7,7,7,7,7);
		  }
		break;
	    }
	  case 0x8f:// adc a
	    {
		if (label_chk.flag == 0)
		  {
		    a = a + a + cs;
		    refresh_flags(7,7,7,7,7);
		  }
	    break;
	    }
	  case 0x88:// adc b
	    {
		if (label_chk.flag == 0)
		  {
		    a = a + b + cs;
		    refresh_flags(7,7,7,7,7);
		  }
		break;
	     }
	  case 0x89:// adc c
	     {
	       if (label_chk.flag == 0)
		  {
		      a = a + c + cs;
		      refresh_flags(7,7,7,7,7);
		  }
	       break;
	     }
	  case 0x8a:// adc d
	      {
		 if (label_chk.flag == 0)
		   {
		     a = a + d + cs;
		     refresh_flags(7,7,7,7,7);
		   }
		 break;
	      }
	  case 0x8b:// adc e
	       {
		 if (label_chk.flag == 0)
		     {
			a = a + e + cs;
			refresh_flags(7,7,7,7,7);
		     }
		 break;
		}
	  case 0x8c:// adc h
		{
		  if (label_chk.flag == 0)
		    {
		      a = a + h + cs;
		      refresh_flags(7,7,7,7,7);
		    }
		  break;
		}
	  case 0x8d:// adc l
	       {
		 if (label_chk.flag == 0)
		    {
		     a = a + l + cs;
		     refresh_flags(7,7,7,7,7);
		   }
		   break;
	       }
	  case 0x8e:// adc m
	      {
		if (label_chk.flag == 0)
		    {
		      a = a + hl + cs;
		      refresh_flags(7,7,7,7,7);
		    }
		break;
	      }

	 // add instructions

	 case 0x87://add a
	     {
	       if  (label_chk.flag == 0)
		 {
		    a = a + a;
		    refresh_flags(7,7,7,7,7);
		  }
		 break;
	      }
	 case 0x80://add b
	      {
		if  (label_chk.flag == 0)
		    {
			a = a + b;
			refresh_flags(7,7,7,7,7);
		    }
		break;
	       }
	 case 0x81://add c
	       {
		 if  (label_chk.flag == 0)
		    {
		     a = a + c;
		     refresh_flags(7,7,7,7,7);
		    }
		 break;
	       }
	case 0x82://add d
	      {
		if  (label_chk.flag == 0)
		   {
		     a = a + d;
		     refresh_flags(7,7,7,7,7);
		   }
		break;
	      }
	case 0x83://add e
	  {
	     if  (label_chk.flag == 0)
	      {
		a = a + e;
		refresh_flags(7,7,7,7,7);
	      }
	     break;
	  }
	case 0x84://add h
	  {
	    if  (label_chk.flag == 0)
	       {
		   a = a + h;
		   refresh_flags(7,7,7,7,7);
		}
	       break;
	   }
	 case 0x85://add l
	    {
	       if  (label_chk.flag == 0)
		 {
		   a = a + l;
		   refresh_flags(7,7,7,7,7);
		 }
	       break;
	     }
	 case 0x86://add m
	      {
		if  (label_chk.flag == 0)
		  {
		    a = a + hl;
		    refresh_flags(7,7,7,7,7);
		  }
		break;
	      }

	 case 0xc6: // adi data
	      {
		fscanf(fp,"%x",&temphex);
		if (label_chk.flag == 0)
		   {
		     a = a + temphex;
		     refresh_flags(7,7,7,7,7);
		   }
		break;
	       }

	   //ana ins

	  case 0xa7://ana a
	     {
	       if  (label_chk.flag == 0)
		  {
		    a = a & a;
		    refresh_flags(0,1,7,7,7);
		   }
		  break;
	     }
	   case 0xa0://ana b
	       {
		  if  (label_chk.flag == 0)
		     {
		       a = a & b;
		       refresh_flags(0,1,7,7,7);
		     }
	       break;
	       }
	    case 0xa1://ana c
		{
		   if  (label_chk.flag == 0)
		      {
			  a = a & c;
			  refresh_flags(0,1,7,7,7);
		      }
		   break;
		 }
	    case 0xa2://ana d
		 {
		    if  (label_chk.flag == 0)
			{
			   a = a & d;
			   refresh_flags(0,1,7,7,7);
			 }
			break;
		  }
	   case 0xa3://ana e
		{
		  if  (label_chk.flag == 0)
		     {
		       a = a & e;
		       refresh_flags(0,1,7,7,7);
		     }
		  break;
		}
	   case 0xa4://ana h
	       {
		 if  (label_chk.flag == 0)
		      {
			a = a & h;
			refresh_flags(0,1,7,7,7);
		      }
		 break;
	       }
	   case 0xa5://ana l
	       {
		 if  (label_chk.flag == 0)
		    {
		      a = a & l;
		      refresh_flags(0,1,7,7,7);
		     }
		 break;
	       }
	   case 0xa6://ana m
	       {
		 if  (label_chk.flag == 0)
		     {
			a = a & hl;
			refresh_flags(0,1,7,7,7);
		      }
		     break;
	       }

	  case 0xe6://ani data
		{
		  fscanf(fp,"%x",&temphex);
		  if  (label_chk.flag == 0)
		     {
		       a = a & temphex;
		       refresh_flags(0,1,7,7,7);
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
		 refresh_flags(7,8,8,8,8);
		 }
		 break;
	       }
	     case 0x3f://cmc
	       {
		if (label_chk.flag == 0)
		 {

		 refresh_flags(8,2,8,8,8);
		 }
		 break;
	       }
	     case 0xbf://cmp a
	       {
		 if (label_chk.flag == 0)
		 {

		 temphex = a;
		 a = a - a;
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
		 refresh_flags(7,7,7,7,7);
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
			}
		    break;
		  }
	       case 0x27: //daa
		  {
		    if (label_chk.flag == 0)
		      {
		    // ********************
		    } break;

		  }
	       case 0x09: //dad b
		 {
		  if (label_chk.flag == 0)
		      {
		   hl = hl + bc;
		   refresh_flags_pairreg(7,8,8,8,8);
		   }break;

		 }
	      case 0x19: //dad d
		 {
		  if (label_chk.flag == 0)
		      {
		   hl = hl + de;
		   refresh_flags_pairreg(7,8,8,8,8);
		   }
		   break;

		 }
	      case 0x29: //dad h
		 {
		 if (label_chk.flag == 0)
		      {
		   hl = hl + hl;
		   refresh_flags_pairreg(7,8,8,8,8);
		   }
		   break;

		 }
	     case 0x3d://dcr a
		{
		 if (label_chk.flag == 0)
		      {
		  a--;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x05://dcr b
		{
		 if (label_chk.flag == 0)
		      {
		  b--;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x0d://dcr c
		{
		 if (label_chk.flag == 0)
		      {
		  c--;
		  refresh_flags(8,7,7,7,7);
		  }break;
		}
	     case 0x15://dcr d
		{
		 if (label_chk.flag == 0)
		      {
		  d--;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x1d://dcr e
		{
		 if (label_chk.flag == 0)
		      {
		  e--;
		  refresh_flags(8,7,7,7,7);
		  }break;
		}
	     case 0x25://dcr h
		{
		 if (label_chk.flag == 0)
		      {
		  h--;
		  refresh_flags(8,7,7,7,7);
		  }break;
		}
	     case 0x2d://dcr l
		{
		 if (label_chk.flag == 0)
		  {
		  l--;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x35://dcr m
		{
		 if (label_chk.flag == 0)
		  {
		  hl--;
		  refresh_flags_pairreg(8,7,7,7,7);
		  }break;
		}

	     case 0x0b://dcx b
		{
		 if (label_chk.flag == 0)
		  {
		  bc--;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }break;
		}
	     case 0x1b://dcx d
		{
		  if (label_chk.flag == 0)
		  {
		  de--;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x2b://dcx h
		{
		  if (label_chk.flag == 0)
		  {
		  hl--;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x3b://dcx sp
		{
		 if (label_chk.flag == 0)
		  {
		  sp--;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x3c://inr a
		{
		  if (label_chk.flag == 0)
		  {
		  a++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x04://inr b
		{
		 if (label_chk.flag == 0)
		  {
		  b++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x0c://inr c
		{
		  if (label_chk.flag == 0)
		  {
		  c++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x14://inr d
		{
		  if (label_chk.flag == 0)
		  {
		  d++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x1c://inr e
		{
		 if (label_chk.flag == 0)
		  {
		  e++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x24://inr h
		{
		  if (label_chk.flag == 0)
		  {
		  h++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x2c://inr l
		{
		 if (label_chk.flag == 0)
		  {
		  l++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x34://inr m
		{
		 if (label_chk.flag == 0)
		  {
		  hl++;
		  refresh_flags(8,7,7,7,7);
		  }
		  break;
		}
	     case 0x03://inx b
		{
		 if (label_chk.flag == 0)
		  {
		  bc++;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x13://inx d
		{
		 if (label_chk.flag == 0)
		  {
		  de++;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x23://inx h
		{
		 if (label_chk.flag == 0)
		  {
		  hl++;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}
	     case 0x33://inx sp
		{
		  if (label_chk.flag == 0)
		  {
		  sp++;
		  refresh_flags_pairreg(8,8,8,8,8);
		  }
		  break;
		}

	     case 0x7f: //mov a,a
	     {
	       if (label_chk.flag == 0)
		 {
		   a = a;
		 }
	       break;
	     }

	     case 0x78: //mov a,b
	      {
	       if (label_chk.flag == 0)
		   a = b;
	       break;
	      }

	     case 0x79: //mov a,c
	      {
	       if (label_chk.flag == 0)
		   a = c;
	       break;
	      }
	     case 0x7a: //mov a,d
	      {
	       if (label_chk.flag == 0)
		   a = d;
	       break;
	      }
	     case 0x7b: //mov a,e
	      {
	       if (label_chk.flag == 0)
		   a = e;
	       break;
	      }

	     case 0x7c: //mov a,h
	      {
	       if (label_chk.flag == 0)
		   a = h;
	       break;
	      }
	     case 0x7d: //mov a,l
	      {
	       if (label_chk.flag == 0)
		   a = l;
	       break;
	      }
	    case 0x7e: //mov a,m
	      {
	       if (label_chk.flag == 0)
		   a = hl;//do memory operation
	       break;
	      }
	    case 0x47: //mov b,a
	      {
	       if (label_chk.flag == 0)
		   b = a;
	       break;
	      }
	  case 0x40: //mov b,b
	      {
	       if (label_chk.flag == 0)
		   b = b;
	       break;
	      }
	  case 0x41: //mov b,c
	      {
	       if (label_chk.flag == 0)
		   b = c;
	       break;
	      }
	  case 0x42: //mov b,d
	      {
	       if (label_chk.flag == 0)
		   b = d;
	       break;
	      }
	  case 0x43: //mov b,e
	      {
	       if (label_chk.flag == 0)
		   b = e;
	       break;
	      }
	  case 0x44: //mov b,h
	      {
	       if (label_chk.flag == 0)
		   b = h;
	       break;
	      }
	  case 0x45: //mov b,l
	      {
	       if (label_chk.flag == 0)
		   b = l;
	       break;
	      }
	 case 0x46: //mov b,m
	      {
	       if (label_chk.flag == 0)
		   b = d;    //memory calculation
	       break;
	      }
	 case 0x4f: //mov c,a
	      {
	       if (label_chk.flag == 0)
		   c = a;
	       break;
	      }
	 case 0x48: //mov c,b
	      {
	       if (label_chk.flag == 0)
		   c = b;
	       break;
	      }
	 case 0x49: //mov c,c
	      {
	       if (label_chk.flag == 0)
		   c = c;
	       break;
	      }
	 case 0x4a: //mov c,d
	      {
	       if (label_chk.flag == 0)
		   c = d;
	       break;
	      }
	 case 0x4b: //mov c,e
	      {
	       if (label_chk.flag == 0)
		   c = e;
	       break;
	      }
	 case 0x4c: //mov c,h
	      {
	       if (label_chk.flag == 0)
		   c = h;
	       break;
	      }
	 case 0x4d: //mov c,l
	      {
	       if (label_chk.flag == 0)
		   c = l;
	       break;
	      }
	 case 0x4e: //mov c,m
	      {
	       if (label_chk.flag == 0)
		   c = l;//memory calculation
	       break;
	      }
	 case 0x57: //mov d,a
	      {
	       if (label_chk.flag == 0)
		   d = a;
	       break;
	      }
	 case 0x50: //mov d,b
	      {
	       if (label_chk.flag == 0)
		   d = b;
	       break;
	      }
	 case 0x51: //mov d,c
	      {
	       if (label_chk.flag == 0)
		   d = c;
	       break;
	      }
	 case 0x52: //mov d,d
	      {
	       if (label_chk.flag == 0)
		   d = d;
	       break;
	      }
	 case 0x53: //mov d,e
	      {
	       if (label_chk.flag == 0)
		   d = e;
	       break;
	      }
	 case 0x54: //mov d,h
	      {
	       if (label_chk.flag == 0)
		   d = h;
	       break;
	      }
	 case 0x55: //mov d,l
	      {
	       if (label_chk.flag == 0)
		   d = l;
	       break;
	      }
	 case 0x56: //mov d,m
	      {
	       if (label_chk.flag == 0)
		   d = l;//memory calculations
	       break;
	      }

	  case 0x5f: //mov e,a
	      {
	       if (label_chk.flag == 0)
		   e = a;
	       break;
	      }
	 case 0x58: //mov e,b
	      {
	       if (label_chk.flag == 0)
		   e = b;
	       break;
	      }
	 case 0x59: //mov e,c
	      {
	       if (label_chk.flag == 0)
		   e = c;
	       break;
	      }
	 case 0x5a: //mov e,d
	      {
	       if (label_chk.flag == 0)
		   e = d;
	       break;
	      }
	 case 0x5b: //mov e,e
	      {
	       if (label_chk.flag == 0)
		   e = e;
	       break;
	      }
	 case 0x5c: //mov e,h
	      {
	       if (label_chk.flag == 0)
		   e = h;
	       break;
	      }
	 case 0x5d: //mov e,l
	      {
	       if (label_chk.flag == 0)
		   e = l;
	       break;
	      }
	 case 0x5e: //mov e,m
	      {
	       if (label_chk.flag == 0)
		   d = l;//memory calculations
	       break;
	      }

	 case 0x67: //mov h,a
	      {
	       if (label_chk.flag == 0)
		   h = a;
	       break;
	      }
	 case 0x60: //mov h,b
	      {
	       if (label_chk.flag == 0)
		   h = b;
	       break;
	      }
	 case 0x61: //mov h,c
	      {
	       if (label_chk.flag == 0)
		   h = c;
	       break;
	      }
	 case 0x62: //mov h,d
	      {
	       if (label_chk.flag == 0)
		   h = d;
	       break;
	      }
	 case 0x63: //mov h,e
	      {
	       if (label_chk.flag == 0)
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


	  case 0x6f: //mov l,a
	      {
	       if (label_chk.flag == 0)
		   l = a;
	       break;
	      }
	 case 0x68: //mov l,b
	      {
	       if (label_chk.flag == 0)
		   l = b;
	       break;
	      }
	 case 0x69: //mov l,c
	      {
	       if (label_chk.flag == 0)
		   l = c;
	       break;
	      }
	 case 0x6a: //mov l,d
	      {
	       if (label_chk.flag == 0)
		   l = d;
	       break;
	      }
	 case 0x6b: //mov l,e
	      {
	       if (label_chk.flag == 0)
		   l = e;
	       break;
	      }
	 case 0x6c: //mov l,h
	      {
	       if (label_chk.flag == 0)
		   l = h;
	       break;
	      }
	 case 0x6d: //mov l,l
	      {
	       if (label_chk.flag == 0)
		   l = l;
	       break;
	      }
	 case 0x6e: //mov l,m
	      {
	       if (label_chk.flag == 0)
		   l = l;//memory calculations
	       break;
	      }
	 case 0x70: //mov m,b
	      {
	       if (label_chk.flag == 0)
		   h = a;//memory calculations
	       break;
	      }
	 case 0x71: //mov m,b
	      {
	       if (label_chk.flag == 0)
		   h = b; //memory calculations
	       break;
	      }
	 /*case 0x72: //mov h,c
	      {
	       if (label_chk.flag == 0)
		   h = c;
	       break;
	      }
	 case 0x62: //mov h,d
	      {
	       if (label_chk.flag == 0)
		   h = d;
	       break;
	      }
	 case 0x63: //mov h,e
	      {
	       if (label_chk.flag == 0)
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

       }//end of switch
   }while(!feof(fp));
   if (label_chk.flag == 1) goto execute_program;

   fclose(fp);


   //now showing condition of registers
   printf("\n **** Register contents *****");
   printf("\n A = %x B = %x C = %x D = %x E = %x H = %x L = %x",a,b,c,d,h,l);
   printf("\n PC = %x Sp = %x ",pc,sp);
   //flags
   printf("\n **** Flag contents *****");
   printf("\n CS = %d AC = %d Z = %d P = %d S = %d\n\n",cs,ac,z,p,s);

}//end of main
void refresh_flags(int fcs, int fac, int fz, int fs, int fp)
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
		  //a = a - 256;
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
void pushme(int datatopush)
{

}
void refresh_flags_pairreg(int fcs, int fac, int fz, int fs, int fp)
{
}