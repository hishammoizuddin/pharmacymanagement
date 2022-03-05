// Firstcare Pharmacy Management SOURCE CODE - Hisham Moizuddin

#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<ctype.h>

class pharmacy
{
int patno;
char name[40];
char prob[15];
char presmed[20];
char doc[40];
char phone[10];

public:

void main_menu();
void add();                 // to enter patient data
void display();             // to display patient record
void pres_med();              // to display the prescribed medicines
void edit();                // to edit patient record
int check(int);          // to check patient number status
void modify(int);
void delete_patrec(int);

void hosp_header ();
void calc();
};

void authenticate();

void pharmacy::hosp_header()
{
printf("\n\t                ************************************** ");
printf("\n\t                *                                    * ");
printf("\n\t                * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ * ");
printf("\n\t                * $                                $ * ");
printf("\n\t                * $           WELCOME TO           $ * ");
printf("\n\t                * $       FIRST CARE PHARMACY      $ * ");
printf("\n\t                * $                                $ * ");
printf("\n\t                * $   Road no. 72, Jubilee Hills   $ * ");
printf("\n\t                * $     Hyderabad , Telangana      $ * ");
printf("\n\t                * $                                $ * ");
printf("\n\t                * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ * ");
printf("\n\t                *                                    * ");
printf("\n\t                ************************************** ");
}

void pharmacy::main_menu()                                         // main menu
{
int ch;

do{
cout<<"\n\t\t\t\t- MAIN MENU - ";
cout<<"\n\n\t\t\t1. Enter Patient Record";
cout<<"\n\t\t\t2. Display Patient Record";
cout<<"\n\t\t\t3. Display All Medicines Prescribed ";
cout<<"\n\t\t\t4. Edit Record ";
cout<<"\n\t\t\t5. Billing ";
cout<<"\n\t\t\t6. Exit ";
cout<<"\n\n\t\t\tENTER YOUR CHOICE : ";
cin>>ch;
clrscr();
switch(ch)
{
case 1: add();
        break;
case 2: display();
        break;
case 3: pres_med();
        break;
case 4: edit();
        break;
case 5: calc();
        break;
case 6: exit(0);
        break;
default : { cout<<"\n\nPlease Enter A Valid Choide :)\n";}
}
}while(ch!=6);
}

void pharmacy::add()                                               //add record
{
int pno,flag;
ofstream fout("patient.dat",ios::binary|ios::app);
cout<<"\n\t\t\t\t ENTER PATIENT DETAILS : \n";
cout<<"  \t\t\t\t-----------------------";
cout<<"\n Patient Number : ";
cin>>pno;

flag=check(pno);

if(flag)
{cout<<"\n\n\t\t\tSorry, a Patient With Same Number already exists,\n\t\t\t please assign a different number.\n\n";
cout<<"\t\tPress any key to continue\n";
getch(); clrscr();}

else
{
patno=pno;
cout<<"\n Name : ";
gets(name);
cout<<"\n Diagnosed with : ";
gets(prob);
cout<<"\n Medicine Prescribed : ";
gets(presmed);
cout<<"\n Medicine Prescribed by : ";
gets(doc);
cout<<"\n Contact No. : ";
cin>>phone;
fout.write((char*)this,sizeof(pharmacy));
clrscr();
cout<<"\n\t\tRecord Added Succesfully \n\n";
}
fout.close();
}

void pharmacy::display()                                             //display
{
ifstream fin("patient.dat",ios::binary|ios::in);
int pno,flag=0;
cout<<"\nEnter Patient Number : ";
cin>>pno;

while(fin.read((char*)this,sizeof(pharmacy)))
{
if(patno==pno)
{
cout<<"\n\n\t\t  PATIENT DETAILS - ";
cout<<"\n\t\t --------------------\n";
cout<<"\n Patient Number            : "<<patno;
cout<<"\n Name                      : "<<name;
cout<<"\n Diagnosis                 : "<<prob;
cout<<"\n Medicine(s) Prescribed    : "<<presmed;
cout<<"\n Medicine(s) Prescribed by : "<<doc;
cout<<"\n Contact Number            : "<<phone;
cout<<"\n\n\t\tpress any key to continue ";
getch();
clrscr();
flag=1;
break;
}
}

if(flag==0)
cout<<"\n\n\t\tPatient Not Found, Please check the patient number.\n\n";

fin.close();
}

void pharmacy::pres_med()                        //list of prescribed medicines
{
ifstream fin("patient.dat",ios::binary|ios::in);
cout<<"\n\n\t\t\t - LIST OF MEDICINES PRESCRIBED - ";
cout<<"\n\n\t\t\t-----------------------------------\n";
cout<<"\n\nPatient No.\t  Name  \t  Medicine Prescribed \t  Contact\n";

while(fin.read((char*)this,sizeof(pharmacy)))
{
cout<<"\n\n"<<patno<<" \t    "<<name<<" \t      "<<presmed<<"\t   \t\t  "<<phone;
cout<<"\n";
}
fin.close();
cout<<"\n\n\t\tPress any key to continue ";
getch();
clrscr();
}

void pharmacy::edit()                                            //edit record
{
cout<<"\n\n Please Authenticate your Identity once again\n";
authenticate();
int ch,p;
cout<<"\n\t1. Modify Patient Record ";
cout<<"\n\t2. Delete Patient Record ";
cout<<"\n\tEnter Your Choice : ";
cin>>ch;
cout<<"\n Enter Patient Number : ";
cin>>p;
switch(ch)
{
case 1: modify(p);
        break;
case 2: delete_patrec(p);
        break;
default: cout<<"\nInvalid\n";
}
}

int pharmacy::check(int p)                              // check patient number
{
int flag=0;
ifstream fin("patient.dat",ios::binary|ios::in);
while(!fin.eof())
{
fin.read((char*)this,sizeof(pharmacy));
if(patno==p)
{flag=1;
break;}
}
fin.close();
return(flag);
}


void pharmacy::modify(int p)                              //modify record
{
long pos,flag=0;
fstream f("patient.dat",ios::in|ios::out|ios::binary);
while(!f.eof())
{
pos=f.tellg();
f.read((char*)this,sizeof(pharmacy));
if(patno==p)
{
cout<<"\nEnter New Patient Details";
cout<<"\nName : ";
gets(name);
cout<<"\nDiagnosed With : ";
gets(prob);
cout<<"\nMedicine Prescribed : ";
gets(presmed);
cout<<"\nMedicine Prescribed by : ";
gets(doc);
cout<<"\nContact No. : ";
cin>>phone;
f.seekg(pos);
f.write((char*)this,sizeof(pharmacy));
cout<<"\nPatient Record Modified Succesfully\n";
cout<<"\n\t\tPress any key to continue ";
getch();
clrscr();
flag=1;
break;
}
}
if(flag==0)
cout<<"\nPatient Not Found\n ";
f.close();}


void pharmacy::delete_patrec(int p)                     // delete record
{
int flag=0;
char c;

ifstream fin("patient.dat",ios::binary|ios::in);
ofstream fout("temp.dat",ios::binary|ios::out);

while(fin.read((char*)this,sizeof(pharmacy)))
{
if(patno==p)
 {
cout<<"\n Name Of the Patient : "<<name;
cout<<"\n Do you want to delete all the data associated with this patient ? (y/n) ";
cin>>c;
if(c=='n')
{fout.write((char*)this,sizeof(pharmacy));
flag=1; }
 }

else
fout.write((char*)this,sizeof(pharmacy));}

fin.close();
fout.close();
if(flag==1)
cout<<"\nInvalid\n";
else
{
remove("patient.dat");
rename("temp.dat","patient.dat");
cout<<"\n\nSuccesfully Deleted Patient Data \n\n";
cout<<"Press any key to continue ";
getch();
clrscr();
}
}


void pharmacy::calc()                                    //bill calculation
{

float pod,pc,tot,total;
char pname[40];

cout<<"\nEnter the Price of the Drug : ";
cin>>pod;
cout<<"\nEnter Prescription Charge (for the chemist) : ";
cin>>pc;
cout<<"\nEnter Patient Name : ";
cin>>pname;

tot=(pod+pc)*0.05;
total=tot+pod+pc;

cout<<"Total Amount (inclusive of 5% Tax) : "<<total<<" Rs\n";
}

void authenticate()                                    //password authentication
{
int i,counter=0,flag=0;
char uid[25],pwd[25],s_uid[][25]={"dr.hisham"};
char s_pwd[][25]={"hisham786"},ch='a';
/*dummy character in ch */
start:
cout<<"\n\n Enter the Username : ";
cin>>uid;
printf("\n Enter the Password : ");
i=0;
while(1)
{
	ch=getch();
	if(ch==13)
	break;
	else if(ch==8)
	{       if(i!=0) /*this is for avoiding the ENTER instructions getting deleted */
		{
			cout<<"\b";  /*printing backspace to move cursor 1 pos back*/
			printf("%c",32);/*making the char invisible which is already on console*/
			printf("\b"); /*printing backspace to move cursor 1 pos back*/
			i--;
			pwd[i]='\0';
		}
		else
		continue;
	}
	else
	{
	putchar('*');/* char - '*' will be printed instead of the character */
	pwd[i]=ch;
	i++;
	}
}
pwd[i]='\0';
for(i=0;i<=2;i++)
{
	if((stricmp(uid,s_uid[i]))==0 && (strcmp(pwd,s_pwd[i]))==0)
	{
		flag=1;
		break;
	}
}
if(flag)
{clrscr();
printf(" \n\n\t\t\t\t   ACCESS GRANTED\n ");}
else
{clrscr();
printf("\n\n\n\t\t\t Invalid Username or Password ");
cout<<"\n\t\t\t Press any key to continue\n";
getch();
goto start;}
}


void main()
{

cout<<"\n\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
cout<<"\n\t\t\t- Firstcare Pharmacy Management -";
cout<<"\n\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

cout<<"\n\n\t\t\tCreated By : Hisham Moizuddin\n";
authenticate();
pharmacy p;
p.hosp_header();
cout<<"\n\n\t\t\t\tPress any key to continue ";
getch();
clrscr();
p.main_menu();
getch();
}




































