# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <conio.h>
# include "hash.h"
# define MAX_ERR 26
typedef unsigned char byte;
typedef unsigned int word;

/*********************DATA STRUCTURES*************/
struct objcode{
   int validopcode;
   int flag;
   int no;   // see's if next contains an objcode or not
   char label[10];
   byte first;
   word next;
   objcode():no(0),first(0),next(0),flag(0),validopcode(0){}

   void display()
     {
     int i,j;
     if(validopcode==1){
	if(no==1)
	  printf("%x",first);
	else
	  printf("%x %x",first,next);
	 }
    else
       printf("Invalid Opcode");
     putchar('\n');
     }
   void display(FILE *fp,long loc)
     {
     int i,j;
     char bt[4];
     char l[5];
     char wd[5];
     if(no==2) {
     if(next>0x0f)
	 itoa(next,wd,16);
     else
	 sprintf(wd,"0%x",next);
     }
     if(no==3)
	{
	 itoa(next,wd,16);
	 int len = strlen(wd);
	 for(int i=0;i<5;i++,len--)
	     if(len>=0)
		   wd[4-i] = wd[len];
	     else
		   wd[4-i] = '0';

	}
     if(first > 0x0f)
	 itoa(first,bt,16);
     else
	 sprintf(bt,"0%x",first);

     if(validopcode==1){
	ltoa(loc,l,16);
	int lent = strlen(l);
	 for(int j=0;j<5;j++,lent--)
	     if(lent>=0)
		   l[4-j] = l[lent];
	     else
		   l[4-j] = '0';

	if(no==1)
	  fprintf(fp,"%s \t%s\n",l, bt);
	else
	  fprintf(fp,"%s \t%s %s\n",l , bt,wd);
	 }
    else
       fprintf(fp,"Invalid Opcode\n");
     putchar('\n');
     }
};

struct LINE{
int error;
int no;
long loc;
objcode obj;
char instruction[3][10];
LINE() : loc(0),error(-1){}
int isLabel();
};
int LINE :: isLabel()
  {
  char reg[12][4]={"B","C","D","E","H","L","M","A","sp","psw"};
  char noi[10]={'1','2','3','4','5','6','7','8','9','0'};
  char twoi[18][4]={"jc","jm","jmp","jnc","jnz","jp","jpe","jpo","jz","cnc","cnz","cp","cpe","cpo","cz","cm","cc","call"};
  char lab[80][5]={"mov","mvi","lda","sta","lhld","shld","xchg","lxi","ldax","stax","add","adc","adi","aci","sub","sbb","sbi","sui","inr","inx","dad","dcr","dcx","daa","ana","ani","xra","xri","ora","ori","cmp","cpi","rlc","ral","rrc","rar","cma","cmc","stc","jc","jm","jmp","jnc","jnz","jp","jpe","jpo","jz","cnc","cnz","cp","cpe","cpo","cz","cm","cc","call","in","ret","rnz","rz","rnc","rc","rpo","rpe","rp","rm","pchl","push","pop","xthl","sphl","out","ei","di","hlt","rst","nop","rim","sim"};
  for(int k=0;k<18;k++)
   if(no==2 && (stricmp(instruction[0],twoi[k])==0))
      {
      for(int i=0;i<10;i++)
	    if((stricmp(instruction[1],reg[i])==0)||(instruction[1][0]==noi[i]))
		 return 2;
      for(int j=0;j<80;j++)
	    if(stricmp(instruction[1],lab[i])==0)
		 return 2;
	    return 1;
      }
   return 0;
  }
struct onebyte{
   char a[10];
   byte b;
};
int add2i(char *wrd)
  {
  return atoi(wrd);
  }
void GetObjectCode(char word1[10][10],int no,objcode &obj)
   {
    int i1,i2,i;
    char reg[8][2]={"B","C","D","E","H","L","M","A"};
    char dreg[][4]={"b","d","h","psw"};
    char areg[][4]={"b","d","h","sp"};
    char word[10][10];
    onebyte on[]={"nop",0,"pchl",0x0e9,"ral",0x017,"rar",0x01f,"rc",0x0d8,"ret",0x0c9,"rim",0x020,"rlc",0x07,"rm",0x0f8,"rnc",0x0d0,"rnz",0x0c0,"rp",0x0f0,"rpe",0x0e8,"rpo",0x0e0,"rrc",0x0f,"rz",0x0c8,"sim",0x030,"sphl",0x0f9,"stc",0x037,"xchg",0x0eb,"xthl",0x0e3,"cma",0x02f,"cmc",0x03f,"daa",0x027,"di",0x0f3,"ei",0x0fb,"hlt",0x076};
    onebyte two[]={"jc",0x0da,"jm",0x0fa,"jmp",0x0c3,"jnc",0x0d2,"jnz",0x0c2,"jp",0x0f2,"jpe",0x0ea,"jpo",0x0e2,"jz",0x0ca,"lda",0x03a,"lhld",0x02a,"cnc",0x0d4,"cnz",0x0c4,"cp",0x0f4,"cpe",0x0ec,"cpo",0x0e4,"cz",0x0cc,"cm",0x0fc,"cc",0x0dc,"call",0x0cd,"shld",0x022,"sta",0x032,"sbi",0x0de,"sui",0x0d6,"xri",0x0ee,"adi",0x0c6,"ani",0x0e6,"in",0xdb,"cpi",0x0fe,};
    int len = strlen(word1[0]);
    if(word1[0][len-1]==':')
	 {
	 obj.flag = 1;
	 strcpy(obj.label,word1[0]);
	 for(int ii=1;ii<no;ii++)
	      strcpy(word[ii-1], word1[ii]);
	 no --;

	 }
    else
	for(int ii=0;ii<no;ii++)
	  strcpy(word[ii],word1[ii]);
    int tocheck=0;
    switch(no)
    {
    case 3:
	    tocheck = 0;
	    /*      for mov   */
	    if(stricmp(word[0],"mov")==0)
		  {
		  tocheck ++;
		  obj.no = 1;
		  for(i=0;i<8;i++)
			{
			if(stricmp(word[1],reg[i])==0)
			  {
			      tocheck++;
			      i1=i;
			  }
			if(stricmp(word[2],reg[i])==0)
			   {
			      tocheck++;
			      i2=i;
			   }
			}
		   obj.first=64;
		   obj.first += i1*8 + i2;
		   }
	     /*  for mvi         */
	    if(stricmp(word[0],"mvi")==0)
		  {
		  obj.no=2;
		  tocheck++;
		  for(i=0;i<8;i++)
			if(stricmp(word[1],reg[i])==0)
			      {
			      if(i%2)
				 {
				   obj.first = 16*(i/2)+14;
				   tocheck++;
				 }
			      else
				 {
				   obj.first = 16*(i/2)+6;
				   tocheck++;
				 }
			      obj.next = add2i(word[2]) ;
			      tocheck++;
			      break;
			      }

		  }
   if(stricmp(word[0],"lxi")==0)
	      {
	      tocheck++;
			for(i=0;i<4;i++)
			  if(stricmp(word[1],areg[i])==0)
			      {
			      tocheck++;
			      obj.no=3;
			      obj.first = (i)*16 +  1;
			      break;
			      }
	      tocheck++;
	      obj.next=add2i(word[2]);
	       }

	    if(tocheck==3)
	       obj.validopcode = 1;
	    break;   // for case 3
  case 2:
		  int flg=0;
		  obj.no = 2;
	    if(stricmp(word[0],"ori")==0)
		  {
		  obj.validopcode = 1;
		  obj.first = 0x0f6;
		  obj.next = add2i(word[1]);
		  break;
		  }
	    for(i=0;i<29;i++)
		 if(stricmp(word[0],two[i].a)==0)
		     {
		     obj.validopcode = 1;
		     if(i<22)
			  obj.no = 3;

			  obj.first=two[i].b;
			  obj.next = add2i(word[1]);
			  flg = 1;
			  break;
		     }
		 if(flg)
			 break;

	    if(stricmp(word[0],"out")==0)
		  {
		  obj.validopcode = 1;
		  obj.first = 0x0d3;
		  obj.next = add2i(word[1]);
		  break;
		  }

	      obj.no = 1;  // for the rest of the instruction given below

	   if(stricmp(word[0],"ora")==0)
		{
		obj.no=1;
		tocheck++;
		obj.first=11*16;
		for(i=0;i<8;i++)
		     if(stricmp(word[1],reg[i])==0)
			   {
			     obj.first += i;
			     tocheck++;
			     break;
			   }
		}

	    if(stricmp(word[0],"pop")==0)
	      {
		tocheck++;
			for(i=0;i<4;i++)
			     if(stricmp(dreg[i],word[1])==0)
			       {
				  obj.first = (12+i)*16 + 1;
				  tocheck++;
				  break;
				}
	      }
	    if(stricmp(word[0],"push")==0)
	      {
	      tocheck++;
			for(i=0;i<4;i++)
			     if(stricmp(dreg[i],word[1])==0)
			       {
			       tocheck++;
				  obj.first = (12+i)*16 + 5;
				  break;
				}
	      }
	    if(stricmp(word[0],"rst")==0)
		  {
		  tocheck++;
		  for(i=0;i<8;i++)
			if(word[1][0]=='0' + i)
			      {
			      if(i%2){
				   tocheck++;
				   obj.first = 16*(12 + i/2)+15;
				   }
			      else {
				   tocheck++;
				   obj.first = 16*(12 + i/2)+7;
				   }
			      break;
			      }

		  }
	    if(stricmp(word[0],"dcr")==0)
		  {
		  tocheck++;
		  for(i=0;i<8;i++)
			if(stricmp(word[1],reg[i])==0)
			      {
			      if(i%2){
				   tocheck++;
				   obj.first = 16*(13 + i/2)+13;
				   }
			      else {
				   tocheck++;
				   obj.first = 16*(i/2)+5;
				   }
			      break;
			      }

		  }
	    if(stricmp(word[0],"inr")==0)
		  {
		  tocheck++;
		  for(i=0;i<8;i++)
			if(stricmp(word[1],reg[i])==0)
			      {
			      if(i%2){
				   obj.first = 16*(13 + i/2)+ 0x0c;
				   tocheck++;
				   }
			      else {
				   obj.first = 16*(i/2)+4;
				   tocheck++;
				   }
			      break;
			      }
		  }
	     if(stricmp(word[0],"sbb")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first = 9*16 + i+8;
			      break;
			      }
	       }
	     if(stricmp("stax",word[0])==0)
		  {
		  tocheck++;
		  if(stricmp(word[1],"b")==0)
		       {
			 tocheck++;
			 obj.first = 0x02;
		       }
		  if(stricmp(word[1],"d")==0)
		       {
			 tocheck++;
			 obj.first = 0x12;
		       }
		  }
	     if(stricmp("ldax",word[0])==0)
		  {
		  tocheck++;
		  if(stricmp(word[1],"b")==0)
		      {
			 tocheck++;
			 obj.first = 0x0a;
		      }
		  if(stricmp(word[1],"d")==0)
		      {
			 tocheck++;
			 obj.first = 0x1a;
		      }
		  }

	     if(stricmp(word[0],"sub")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first = 9*16 + i;
			      break;
			      }
	       }
	     if(stricmp(word[0],"xra")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first = 10*16 + i+8;
			      break;
			      }
	       }
	     if(stricmp(word[0],"adc")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first =  8*16 + i+8;
			      break;
			      }
	       }
	     if(stricmp(word[0],"add")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first =  8*16 + i;
			      break;
			      }
	       }
	     if(stricmp(word[0],"ana")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first = 10*16 + i;
			      break;
			      }
	       }
	     if(stricmp(word[0],"cmp")==0)
	      {
	      tocheck++;
			for(i=0;i<8;i++)
			  if(stricmp(word[1],reg[i])==0)
			      {
			      tocheck++;
			      obj.first = 11*16 + i+8;
			      break;
			      }
	       }
	     if(stricmp(word[0],"dad")==0)
	       {
	       tocheck++;
			for(i=0;i<4;i++)
			  if(stricmp(word[1],areg[i])==0)
			      {
			      tocheck++;
			      obj.first = (i)*16 + 9;
			      break;
			      }
	       }
	     if(stricmp(word[0],"dcx")==0)
	      {
	      tocheck++;
			for(i=0;i<4;i++)
			  if(stricmp(word[1],areg[i])==0)
			      {
			      tocheck++;
			      obj.first = (i)*16 + 11;
			      break;
			      }
	       }
   if(stricmp(word[0],"inx")==0)
	      {
	      tocheck++;
			for(i=0;i<4;i++)
			  if(stricmp(word[1],areg[i])==0)
			      {
			      tocheck++;
			      obj.first = (i)*16 +  3;
			      break;
			      }
	       }
	     if(tocheck==2)
		 obj.validopcode = 1;
	     break; // for case 2
  case 1:
	   obj.no = 1;
	   for(i=0;i<27;i++)
		if(stricmp(word[0],on[i].a)==0)
		  {
		    obj.validopcode = 1;
		    obj.first = on[i].b;
		     break;
		  }
	    break;  // for case 1
    } // end of switch

   }
int validchar(char ch)
  {
  if((ch>='a' && ch<='z') || (ch>='0' && ch<='9') || (ch>='A' && ch<='Z'))
	return 1;
  if(ch=='_'|| ch==':' || ch=='?')
	return 1;
	return 0;
  }

void getword(char *line,char word[10][10],int &wno)
 {
 int flag;    // =1 means reading a word
 register int i=0,j=0;
 wno = 0;
 if(strcmp(word[0],"mov")==0)
	wno = 0;

 while(1)
    {
    if(validchar(line[i]))
       {
		flag=1;
		word[wno][j++]=line[i];
       }
    else
       {
		if(flag==1)
			flag=0,word[wno++][j]='\0',j=0;
		if(line[i]==';' || line[i]=='\0')
			break;
       }
    i++;
    }
 }
 int  GetLine(objcode &obj,FILE *fp,char word[10][10])
  {
  char a[100];
  fgets(a,90,fp);
  int wno = 0;
  getword(a,word,wno);
  GetObjectCode(word,wno,obj);
  return wno;
  }

  class Error{
    int no;
    int errorcode[MAX_ERR];
    char error[4][20];
    int line_no[MAX_ERR];
public :
    Error();
    void Push(objcode,int,int,char word[10][10] );
    void Display();
};

Error :: Error ()
 {
 no = 0;
 char *temp[20]={"Duplicate Label Used","Invalid Instruction Used","Undefined Label Used","Invalid Label Used"};
 for(int i=0;i<4;i++)
    strcpy(error[i],temp[i]);
 }
void Error :: Push(objcode obj,int ec,int line,char word[10][10])
  {
  line_no[no]=line;
  errorcode[no++]=ec;
  }
void Error :: Display()
  {
  if(no==0)
	printf("No Errors found\n");
  else
   {
  printf(" %d errors found\n",no);
  for(int i=0;i<no;i++)
	 printf("Error in line number %d : %s\n",line_no[i]+1,error[errorcode[i]]);
    }
  }
 int isLabel(char a[10])
   {
   int len=strlen(a);
   if(a[len-1]==':')
      return 1;
      return 0;
   }
  void PASS2(char *fileint,char *fileobj,HASH &sym,Error &err)
    {
  FILE *fp = fopen(fileint,"rb");
  FILE *objpointer = fopen(fileobj,"w");
  fprintf(objpointer,"%s\t%s \n","LOCCTR","OBJ-CODE");
  if(fp==NULL)
    {
    printf("\nUnable to locate file %s",fileint);
    printf("\nPress any key to continue ...");
    getch();
    exit(1);
    }

  if(objpointer==NULL)
    {
    printf("\nUnable to locate file %s",fileobj);
    printf("\nPress any key to continue ...");
    getch();
    exit(1);
    }
  char word[10][10];
  LINE item;
  int lno=-1;
  long l=0;
  item_type ins;
  char *Operand = new char[20] ;
  item.loc = -1;
  while(!feof(fp))
       {
       lno++;
       l = item.loc;
      fread(&item , sizeof ( item ) , 1 , fp);
      if(item.loc == l)
	 break;
      if(item.error!=1)
	  {
	    if(item.isLabel()==1)
	       {
		   if(sym.Search(item.instruction[1],Operand))
			      item.obj.next = atoi(Operand);   //save the locctr for the label;                        //sprintf(objstr,"%s%s",address+1,Operand);
		   else
		    {
			   strcpy(Operand,"0");
			   err.Push(item.obj,2,lno,word);
		    }
		}
	     if(item.isLabel()==2)
		 err.Push(item.obj,3,lno,word);
	   } // if symbol found
	     item.obj.display(objpointer,item.loc);
       }
 fcloseall();
}
  void PASS1(char *file,HASH &sym,Error &err)
  {
  int wno;
  long locctr = 0,locold;
  char *operand = new char [20];
  char fileint[]="temp.int";
  char filename[100];
  strcpy(filename,file);
  int lno=0,flg=0;
  FILE *fp,*fp1;
  fp1 = fopen(fileint,"wb");
  fp = fopen(filename,"rb");
    if(fp==NULL)
    {
    printf("\nUnable to locate file %s",filename);
    printf("\nPress any key to continue ...");
    getch();
    exit(1);
    }

    if(fp1==NULL)
    {
    printf("\nUnable to locate file %s",fileint);
    printf("\nPress any key to continue ...");
    getch();
    exit(1);
    }
    objcode item;

    item_type ins;
    char word[10][10];
    while( !feof(fp) )
	 {
	 flg=1;
	 locold = locctr;
	 item.validopcode = item.flag = item.no = 0;
	 wno = GetLine(item,fp,word);

		if(item.flag==1)
		    {
		     if(sym.Search(item.label,operand))
			    err.Push(item,0,lno,word);
		     else
			   {
			     char temp[20];
			     strcpy(ins.mne,item.label);
			     if(locctr>255)
				strcpy(ins.op,ltoa(locctr,temp,16));
			     else
				sprintf(ins.op,"0%s",ltoa(locctr,temp,16));
				ins.mne[strlen(item.label)-1]='\0';
			     sym.Input(&ins);
			   }
		    }
		  if(item.validopcode==1)
			locctr += item.no;
		  else
			err.Push(item,1,lno,word);

	      if(flg)  {
		LINE Line;
			  Line.obj = item;
			  Line.error = 1- item.validopcode;
			  Line.loc = locold;
			if(isLabel(word[0])){
			  Line.no = wno-1;
			    for(int ii=1;ii<wno;ii++)
				   strcpy(Line.instruction[ii-1],word[ii]);
			  }
			else {
			    Line.no = wno;
			    for(int ii=0;ii<wno;ii++)
				   strcpy(Line.instruction[ii],word[ii]);
			     }
			fwrite(&Line, sizeof(Line), 1, fp1); // write struct item to file
		       }
	      lno++;
	 }
	fclose(fp1);
	fclose(fp);
  }

void main(int argc,char *argv[])
  {
  clrscr();
  HASH sym;
  Error err1,err2;
  if(argc==1)
       strcpy(argv[1],"PRG1.CRS");
  if(argc==3)

       if(strcmp(argv[1],"-i")==0)
	   {
	   strcpy(argv[1],argv[2]);
	   LINE Line;
	   FILE *fp;
	   clrscr();
	   printf("Printing the intermediate file.Press ESC to terminate...\n");
	   long l;
		fp = fopen("TEMP.INT","rb");
		int i;
		Line.loc = -1;
		while(!feof(fp))
		 {
			l = Line.loc;
			fread(&Line, sizeof(Line),1, fp); // write struct item to file
			if(l==Line.loc)
				break;
			printf("\nError : %d",Line.error);
			printf("\nLocation Ctr : %d \n",Line.loc);
			for(i=0;i<Line.no;i++)
				printf("%s ",Line.instruction[i]);
			printf("\nNoOf Instructions : %d\n",Line.no);
			Line.obj.display();
		putchar('\n');
			if(getch()==27)
				exit(1);
		  }
	       }
       PASS1(argv[1],sym,err1);

       printf("\n-----Errors found in PASS I-----\n");
       err1.Display();
       cout<<"\n";
       sym.Display();

       printf("\n-----Errors found in PASS II-----\n");
       PASS2("TEMP.INT","TEMP.OBJ",sym,err2);
       err2.Display();

   //    char check;
   //   cout<<"do you want to see symbol table:";
  //     cin>>check;
  //     if(check=='Y'||check=='y')
  //	{ sym.Display();
  //	  getch();
  //	 }
  }