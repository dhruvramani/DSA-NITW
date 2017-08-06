#include <fstream>
#include <iostream>
using namespace std;

#define max_size 70
typedef char integer[4];
typedef char floating[6];

struct student {
    int  rno;
    char name[10];
    float marks;
};

void write(student s)
{
    fstream f("file.txt", ios::app);
    f<<s.rno<<" "<<s.name<<" "<<s.marks<<"\n";
    f.close();
}

void read()
{
    fstream f("file.txt", ios::in);
    student s;
    while(f>>s.rno>>s.name>>s.marks)
        cout<<"Roll : "<<s.rno<<" Name : "<<s.name<<" Marks : "<<s.marks<<"\n";
    f.close();
}

int search(int rno)
{
    fstream f("file.txt", ios::in);
    student s;
    int count=0;
    while(f>>s.rno>>s.name>>s.marks)
    {   
        count++;
        if(s.rno == rno)
        {
            f.close();
            return count;
        }
    }
    f.close();
    return -1;
}   

int main()
{
    int op;
    student s;
    do {
        cout<<"\n1. Enter Record\n2. Search Records\n3. View Records\n0. Quit\nEnter Option : ";
        cin>>op;
        switch(op) 
        {
            case 1:
                cout<<"Roll : ";
                cin>>s.rno;
                cout<<"Name : ";
                cin>>s.name;
                cout<<"Marks : ";
                cin>>s.marks;
                write(s);
                break;
            case 2:
            {
                int rno;
                cout<<"Roll to search : ";
                cin>>rno;
                int a=search(rno);
                if(a != -1)
                    cout<<"Roll No. found";
                else cout<<"Roll No. not found";
                break;
            }
            case 3: 
                read();
                break;
            case 0:
                cout<<"Quitting";
                break;
            default :
                cout<<"Invalid Option";
        }
    } while(op != 0);
    return 0;
}