
#include<iostream.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
				       //Header Files..
class Book
{
 private:
  int bookid;
  char bookname[20];
  float bookprice;                     //Main Base Class..
 public:
  void input();
  void show();
  int retst()
  {
   return bookid;
  }
};

Book b;

void Book :: input()                   //Function To Accept Record..
{
 cout<<"\n\t\t Enter Book Id:";     cin>>bookid;
 cout<<"\n\t\t Enter Book Name:";   gets(bookname);
 cout<<"\n\t\t Enter Book Price:";  cin>>bookprice;
}

void Book :: show()                    //Function To Display Record..
{
 cout<<"\n\t\t Book Id Is:"<<bookid;
 cout<<"\n\t\t Book Name Is:"<<bookname;
 cout<<"\n\t\t Book Price Is:"<<bookprice;
}

void Create();
void Add();
void Display();
void Modify();
void Delete();

fstream fio;
int main()
{
 textmode(80);
 textcolor(RED);
 textbackground(WHITE);
 int ch;
 while(1)
 {                                     //Main Function..
  clrscr();
  cout<<"\n\t\t\t || ******************** ||";
  cout<<"\n\t\t\t || #######:MENU:####### ||";
  cout<<"\n\t\t\t || ******************** ||";
  cout<<"\n\t\t\t || 1. Create Data File. ||";
  cout<<"\n\t\t\t || 2. Add New Record... ||";
  cout<<"\n\t\t\t || 3. Display Record... ||";
  cout<<"\n\t\t\t || 4. Modify Record.... ||";
  cout<<"\n\t\t\t || 5. Delete Record.... ||";
  cout<<"\n\t\t\t || 6. Exit Page........ ||";
  cout<<"\n\t\t\t || ******************** ||";
  cout<<"\n\t\t\t    Enter Your Choice:";
  cin>>ch;
  switch(ch)
  {
   case 1:  Create();   getch();  break;
   case 2:  Add();      getch();  break;
   case 3:  Display();  getch();  break;
   case 4:  Modify();   getch();  break;
   case 5:  Delete();   getch();  break;
   case 6:  exit(0);
  default: {
	    cout<<"\n\t\t Wrong Choice.. Press Any Key..";
	    getch();
	    clrscr();
	   }
  }
  }
}

void Create()                          //Function To Create Data File..
{
  char ch='y';
  fio.open( "binary.dat" ,ios :: out | ios :: binary );
  while(ch=='y')
  {
   b.input();
   fio.write((char *)&b, sizeof(b));
   cout<<"\n\t\t Do You Want To Continue ?";
   cin>>ch;
  }
   fio.close();
}

void Add()                             //Function To Add New Record..
{
  char ch='y';
  fio.open( "binary.dat" , ios :: app | ios :: binary );
  while(ch=='y')
  {
   b.input();
   fio.write((char *)&b, sizeof(b));
   cout<<"\n\t\t Do You Want To Continue ?";
   cin>>ch;
  }
   fio.close();
}

void Display()                         //Function To Display Record..
{
  int n;
  cout<<"\n\t\t Enter Book Id To Be Searched For:";
  cin>>n;
  fio.open( "binary.dat" , ios :: in | ios :: binary );
  if(!fio)
  {
   cout<<"\n\t\t File Not Found..";
   exit(0);
  }
  else
  {
   fio.read((char *)&b, sizeof(b));
   while(!fio.eof())
   {
    if(b.retst()==n)
    {
     b.show();
     cout<<"\n\t\t Press Any Key..";
     getch();
    }
    else
    {
     cout<<"\n\t\t Press Any Key..";
     getch();
    }
    fio.read((char *)&b ,sizeof(b));
   }
  }
  fio.close();
}

void Modify()                          //Function To Modify Record..
{
int i=0,n=0;
long pos;
fstream fio1( "binary.dat" , ios::in | ios::out | ios::binary );
cout<<"\n Enter Book Id To Modify The Record:"; cin >> n;
while(!fio1.eof())
 {
 pos = fio1.tellg();
 fio1.read((char *) &b,sizeof(b));
 if(b.retst()==n)
 {
  cout<<"\n Enter New Details:";
  b.input();
  fio1.seekg(pos);
  fio1.write((char *) &b, sizeof(b));
  cout<<"\n Record Is Modified..";
  i='1'; break;
  }
 }
 if(i=='0')
 cout << "\n Not found";
 fio1.close();
 getch();
}

void Delete()
 {                                      //Function To Delete Record..
 char ch;
 int i=0,n;
 ifstream fio( "binary.dat" , ios::in | ios :: binary);
 ofstream temp("temp.dat", ios::out | ios :: binary);
 cout<<"\n Enter Book Id Whose Reocrd Is to be deleted:"; cin >> n;
 while(!fio.eof())
 {
  fio.read((char *)&b, sizeof( b ));
  if(b.retst()==n)
  {
   b.show();
   cout<<"\n Do You Want To Delete This Record?";
   cin >> ch;
   if(ch=='n')
   {
    temp.write((char*) &b, sizeof( b ));
    i=1;
   }
  }
   else
   temp.write((char*) &b, sizeof( b ));
 }
 fio.close();
 temp.close();
 if(i==1)
  cout<<"\n Press Any Key..";
 else
 {
  cout<<"\n Press Any Key..";
  remove( "binary.dat" );
  rename( "temp.dat" , "binary.dat" );
 }
  getch();
}                                      //End..

//  Completed..