#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef char integer[4];
typedef char floating[6];

char* record_delim = "#";
char* delim = "|"; 

struct boo
{
    integer stno, ctno;
};
union addr 
{   
    boo b;
    char cell[10];
};
struct student {
    integer  rno;
    char* name;
    floating marks;
    integer tag;
    union addr address;
};

class Buffer
{
    int nextpos;
    public :
    char buff[100];
    Buffer()
    {
        nextpos=0;
        buff = "";
    }
    void pack(student s)
    {   
        strcat(buff, s.rno);
        strcat(buff, delim);
        strcat(buff, s.name);
        strcat(buff, delim);
        strcat(buff, s.marks);
        strcat(buff, delim);
        strcat(buff, s.tag);
        strcat(buff, delim);
        if(strcmp(s.tag, "0") == 0)
        {
            nextpos += 8;
            strcat(buff, s.address.b.stno);
            strcat(buff, delim);
            strcat(buff, s.address.b.ctno);
        } else {
            nextpos += 10;
            strcat(buff, s.address.cell);
        }
        strcat(buff, record_delim);
        nextpos += 17 + strlen(s.name);
        fstream f("file2.txt", ios::app);
        f<<buff;
        f.close();
    }

    student unpack(fstream &f)
    {
        char c, *co = &c;
        student s;
        for(int count=1, count2=1; count <= 4; count++)
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
                        strcat(s.tag, co);
                    else if(count == 4)
                        if(strcmp(s.tag, "0") == 0)
                        {
                            if(count2 <= 4)
                            {
                                strcat(s.address.b.stno, co);
                                count2++
                            } else if(count2 <= 8)
                                strcat(s.address.b.ctno, co);
                        } else {
                            strcat(s.address.cell, co);
                        }
            } while(c != delim[0] && c != record_delim[0]);
        }
        return s;
    }
};

void read(Buffer b)
{
    fstream f("file2.txt", ios::in);
    while(!f.eof()) {
        student s=b.unpack(f);
        cout<<"Roll : "<<s.rno<<" Name : "<<s.name<<" Marks : "<<s.marks;
        if(strcmp(s.tag, "0") == 0)
            cout<<"Street Number : "<<s.address.b.stno<<" City Number : "<<s.address.b.stno<<endl;
        else 
            cout<<"Cell : "<<s.address.cell;
    }
}

int search(char* rno, Buffer b)
{
    student s;
    int count=0;
    fstream f("file2.txt", ios::in);
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
                cout<<"Street Number & City Number (0) or Cell (1)";
                cin>>s.tag;
                if(strcmp(s.tag, "0") == 0)
                {
                    cout<<"Street Number :";
                    cin>>s.address.b.stno;
                    cout<<"City Number :";
                    cin>>s.address.b.ctno;
                } else {
                    cout<<"Cell : ";
                    cin>>s.address.cell;
                }
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