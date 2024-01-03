# ifndef __HASHTABLE_
# define __HASHTABLE_
# include<iostream.h>
# include <stdio.h>
# include <string.h>
# include<conio.h>

    const int HASHSIZE = 100;
    typedef struct {
	       char mne[20];
	       char  op[10];
	      }item_type;
    typedef struct tag{
		item_type  info;
		tag  *next;
	      }hashtable;
    class HASH{
	     hashtable *H[HASHSIZE];
	     int hash(char roll[20]);
	     public:
	     HASH();
	     void Input(item_type *);
	     int Search(char roll[20],char opc[20]);
	     void Delete(char roll[20]);
	     void Display();
	     };

int HASH :: hash(char mne[20])
  {
  int to = mne[0]*17 + mne[1]*mne[2] +9;
  return to;
  }
   void HASH ::Input(item_type *p)
    {
     int i,flag=1;
     hashtable  *D,*temp;
     i=hash(p->mne)%HASHSIZE;
     temp=H[i];
     while(temp&&flag)
      {
	 if(strcmp(temp->info.mne,p->mne)==0)
	  {
	  flag=0;
	  cout<<"    DUPLICATE";
	  break;
	  }
	 else
	  temp=temp->next;
      }

     if(flag)
      {
       D=new(hashtable );
       D->info=*p;
       D->next=H[i];
       H[i]=D;
//       printf("%d %s - %s\n",i,H[i]->info.mne ,H[i]->info.op);
      }
    }
   void   HASH ::Delete(char mne[20])
   {
     int i,flag=1;
     hashtable  *temp,*temp1;
     i=hash(mne)%HASHSIZE;
     temp=H[i];
     temp1=H[i];
     if(strcmp(temp->info.mne,mne)==0)
	{
	  H[i]=temp->next;
	  flag=0;
	}
     else
	{ temp=H[i]->next;
	while(temp&&flag)
	  {
	    if(strcmp(temp->info.mne,mne)==0)
	       {
		temp1->next=temp->next;
		flag=0;
	       }
	   else
	      {
	       temp=temp->next;
	       temp1=temp1->next;
	       }
	 }//end of while
       }//end of else

    }


  int HASH ::Search(char mne[20],char opcode[20])
   { int i,flag=1;
     hashtable *temp;
     i=hash(mne)%HASHSIZE;
     temp=H[i];
     while(temp&&flag)
     {
       if(strcmp(temp->info.mne,mne)==0){
       strcpy(opcode,temp->info.op);
	flag=0;
	}
       else
	  {
	   temp=temp->next;
	  }
     }
     return !flag;
    }

    HASH ::HASH()
    {int i;
     for(i=0;i<HASHSIZE;i++)
     {
     H[i]=new(hashtable);
     H[i]=H[i]->next=NULL;
     }
    }
    void HASH :: Display()
      {
     hashtable *temp ;
      //getch();
      cout<<"Symbol  Address\n";
      for(int i=0;i<HASHSIZE;i++)  {
      temp = H[i];
      if(temp!=NULL)
	  {
	  printf("%s      %s\n",H[i]->info.mne,H[i]->info.op);
	  temp = temp->next;
	  }
      }
    }
#endif