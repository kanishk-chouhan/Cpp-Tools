#include<iostream>
#include<stdio.h>
#include<string.h>
#include<limits>
#include<ios>
using namespace std;
class OutputFileStream
{
private:
int mode;
int lastOperationFailed;
FILE *f;
public:
const static int append =1;
const static int overwrite =2;
const static int binary = 4;
OutputFileStream()
{
this->f = NULL;
this->mode = -1;
this->lastOperationFailed=0;
}
OutputFileStream(const char *FileName , int mode)
{
this->f =NULL;
this->mode =-1;
this->lastOperationFailed=0;
open(FileName , mode);
}
void open(const char *FileName , int mode)
{
if(f!=NULL)
{
fclose(f);
this->f = NULL;
this->mode =-1;
}
this->lastOperationFailed=1;
if(FileName == NULL) return;
if(mode!= append && mode!= overwrite && mode!= (append | binary) && mode!= (overwrite | binary)) return;
if(mode== append)
{
f = fopen(FileName,"a");
}
else if(mode== overwrite)
{
f= fopen(FileName , "w");
}
else if(mode == (append | binary))
{
f =fopen(FileName , "ab");
}
else if(mode == (overwrite | binary))
{
f= fopen( FileName  , "wb");
}
if(f== NULL) return;
this->lastOperationFailed =0 ;
}
void close()
{
this->lastOperationFailed =0;
if(this->f== NULL) return;
fclose(this->f);
}

int fail()
{
return this->lastOperationFailed;
}

OutputFileStream & operator<<(char c)
{
this->lastOperationFailed =1;
if(this->f == NULL) return *this;
fputc(c ,this->f);
this->lastOperationFailed =0;
return *this;
}


OutputFileStream & operator<<(const char *str)
{
this->lastOperationFailed =1;
if(this->f== NULL) return *this;
fputs(str , this->f);
this->lastOperationFailed =0;
return *this;
}


OutputFileStream & operator<<( string &str)
{
this->lastOperationFailed =1;
if(this->f== NULL) return *this;
fputs(str.c_str() , this->f);
this->lastOperationFailed =0;
return *this;
}

OutputFileStream & operator<<( int num)
{
char str[21];
sprintf(str, "%d", num);
this->lastOperationFailed =1;
if(this->f== NULL) return *this;
fputs(str, this->f);
this->lastOperationFailed =0;
return *this;
}

void write(const char *stream , int size)
{
this->lastOperationFailed =1;
if(this->f == NULL) return;
fwrite(stream , size , 1,f);
this->lastOperationFailed =0;
}
};

class InputFileStream
{
private:
FILE *f;
int  lastOperationFailed;
int mode;
public:
const static int binary =4;
const static int  reading = 1;
InputFileStream()
{
this->mode =-1;
this->f =NULL;
this->lastOperationFailed = 0;
}
InputFileStream(const char *FileName  )
{
this->mode =-1;
this->f =NULL;
this->lastOperationFailed= 0;
open(FileName , reading);
}
InputFileStream(const char *FileName, int mode )
{
this->mode =-1;
this->f =NULL;
this->lastOperationFailed= 0;
open(FileName , mode);
}

void open(const char *FileName , int mode)
{
if(this->f!=NULL)
{
fclose(this->f);
this->lastOperationFailed=0;
}
this->lastOperationFailed=1;
if(mode!= reading && mode!= binary) return;
if(FileName == NULL) return;
this->mode =mode;
if(mode== reading) 
{
this->f = fopen(FileName , "r");
}
else
{
this->f = fopen(FileName , "rb");
}
if(this->f== NULL) return ;
this->lastOperationFailed=0;
}

int fail()
{
return this->lastOperationFailed;
}

InputFileStream  & operator>> (char &c)
{
this->lastOperationFailed=1;
if(this->f== NULL) return *this;
if(feof(this->f)) return *this;
c = fgetc(this->f);
if(feof(this->f)) return *this;
this->lastOperationFailed=0;
return *this;
}

InputFileStream  & operator>> (char *str)
{
this->lastOperationFailed=1;
if(this->f== NULL) return *this;
if(feof(this->f)) return *this;
char g;
char *p=str;
while(1)
{
g= fgetc(this->f);
if(feof(this->f) || g== '\n') break;
*p =g;
p++;
}
*p= '\0';
this->lastOperationFailed =0;
return *this;
}

InputFileStream  & operator>> ( string &str)
{
str.clear();
this->lastOperationFailed = 1;
if(this->f == NULL) return *this;
if(feof(this->f) ) return *this;
char g;
while(1)
{
g =fgetc(this->f);
if(feof(this->f) || g== '\n') break;
str.push_back(g);
}
this->lastOperationFailed = 0;
return *this;
}

InputFileStream  & operator>> (int &num)
{
char a[21];
this->lastOperationFailed = 1;
if(this->f == NULL) return *this;
if(feof(this->f)) return *this;
char g;
int x=0;
while(1)
{
g= fgetc(this->f);
if(feof(this->f) || g== ' ' || g== '\n') break;
a[x] = g;
x++;
}
if(x==0) return *this;
a[x]= '\0';
this->lastOperationFailed = 0;
num = atoi(a);
return *this;
}
void close()
{
this->lastOperationFailed=0;
if(this->f!= NULL) fclose(this->f);
}

void read(char *stream , int size)
{
this->lastOperationFailed = 1;
if(this->f == NULL) return;
if(feof(this->f)) return ;
fread(stream , size , 1, f);
if(feof(this->f)) return;
this->lastOperationFailed = 0;
}
};
void addStudent()
{
int Rollnumber;
string  name ;
char gender ;
cout<<"Enter the rollnumber :";
cin>>Rollnumber;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout<<" Enter name :";
getline(cin , name);
cout<<"Enter Gender  (M/F):";
cin>>gender;
OutputFileStream f("student.data", OutputFileStream::append);
f<<Rollnumber;
f<<" ";
f<<name;
f<<'\n';
f<<gender; 
f.close();
}
void displayListOfStudents()
{
string name;
int Rollnumber;
char gender;
InputFileStream f("student.data" );
if(f.fail())
{
cout<<"No Student added"<<endl;
}
while(1)
{
f>>Rollnumber;
if(f.fail()) break;
f>>name;
f>>gender;
cout<<"Roll Number : "<<Rollnumber<<", Name : "<<name<<", Gender : "<<gender<<endl;
}
f.close();
}
int main ()
{
int ch;
while(1)
{
cout<<"1. Add Friends : "<<endl;
cout<<"2. Display List Of Students : "<<endl;
cout<<"3. Exit"<<endl;
cout<<"Enter your Choice : ";
scanf("%d" , &ch);
fflush(stdin);
if(ch==1) addStudent();
if(ch==2) displayListOfStudents();
if(ch==3) break;
}
return 0;
}



