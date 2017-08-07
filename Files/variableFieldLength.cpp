#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef char integer[4];
typedef char floating[6];

char* record_delim = "#";
char* delim = "|"; 
struct student {
    integer  rno;
    char* name;
    floating marks;
};

class Buffer
{
    int nextpos;
    public :
    char* buff;
    Buffer()
    {
        nextpos=0;
        buff = new char();
    }
    void pack(student s)
    {   
        strcat(buff, s.rno);
        strcat(buff, delim);
        strcat(buff, s.name);
        strcat(buff, delim);
        strcat(buff, s.marks);
        strcat(buff, record_delim);
        nextpos += 13 + strlen(s.name);
        fstream f("file1.txt", ios::app);
        f<<buff;
        f.close();
    }

    student unpack(fstream &f)
    {
        char c, *co = &c;
        student s;
        for(int count=1; count <= 3; count++)
        {
            do
            {
                f>>c;
                if(c != delim[0] && c != record_delim[0])
                   if(count == 1)
                        strcat(s.rno, co);
                    else if(count == 2)
                        strcat(s.name, co);
                    else if(count == 3)
                        strcat(s.marks, co);
            } while(c != delim[0] && c != record_delim[0]);
        }
        return s;
    }
};

void read(Buffer b)
{
    fstream f("file1.txt", ios::in);
    while(!f.eof()) {
        student s=b.unpack(f);
        cout<<"Roll : "<<s.rno<<" Name : "<<s.name<<" Marks : "<<s.marks<<"\n";
    }
}

int search(char* rno, Buffer b)
{
    student s;
    int count=0;
    fstream f("file1.txt", ios::in);
    while(!f.eof())
    {
        count++;
        student s=b.unpack(f);
        if(strcmp(rno, s.rno) == 0)
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
    s.name = new char();
    Buffer b;
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
                b.pack(s);
                break;
            case 2:
            {
                char rno[4];
                cout<<"Roll to search : ";
                cin>>rno;
                int a=search(rno, b);
                if(a != -1)
                    cout<<"Roll No. found";
                else cout<<"Roll No. not found";
                break;
            }
            case 3: 
                read(b);
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