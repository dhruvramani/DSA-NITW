#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef char integer[4];
typedef char floating[6];

char* record_delim = "#";
char* delim = "|"; 

struct child
{
    integer age;
    char name[15];
}
struct employee {
    integer  empno;
    char name[10];
    integer num_child;
    struct child **children;
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
    void pack(employee s)
    {   
        strcat(buff, em.empno);
        strcat(buff, delim);
        strcat(buff, em.name);
        strcat(buff, delim);
        strcat(buff, em.num_child);            
        for(int i=0; i<stoi(em.num_child); i++)
        {
            nextpos += 19;
            strcat(buff, delim);
            strcat(buff, em.children[i]->age);
            strcat(buff, delim);
            strcat(buff, em.children[i]->name);
        }
        strcat(buff, record_delim);
        nextpos += 27
        fstream f("file1.txt", ios::app);
        f<<buff;
        f.close();
    }

    employee unpack(fstream &f)
    {
        char c, *co = &c;
        employee s;
        for(int count=1, count2=1; count <= 3; count++)
        {
            do
            {
                f>>c;
                cout<<endl<<count<<" "<<c<<endl;
                if(c != delim[0] && c != record_delim[0])
                   if(count == 1)
                        strcat(em.empno, co);
                    else if(count == 2)
                        strcat(em.name, co);
                    else if(count == 3)
                        strcat(em.num_child, co);
                    else if(count == 4)
                        for(int i=0; i<stoi(em.num_child); i++)
                            {
                                for(int j=0; j<4; j++)
                                    if(c == "|" || c == "#")
                                        break;
                                    else
                                    strcat(em.children[i]->age, co);
                                for(int j=0; j<15; j++)
                                    if(c == "|" || c == "#")
                                        break;
                                    else 
                                        strcat(em.children[i]->name, co);
                            }
            } while(c != delim[0] && c != record_delim[0]);
        }
        return s;
    }
};

void read(Buffer b)
{
    fstream f("file1.txt", ios::in);
    while(!f.eof()) {
        employee s=b.unpack(f);
        cout<<"Roll : "<<em.empno<<" Name : "<<em.name<<"\nChildren : \n";
        for(int i=0; i<stoi(em.num_child); i++)
            cout<<"Name : "<<em.children[i]->name<<" Age : "<<em.children[i]->age<<endl;
    }
}

int search(char* empno, Buffer b)
{
    employee s;
    int count=0;
    fstream f("file1.txt", ios::in);
    while(!f.eof())
    {
        count++;
        employee s=b.unpack(f);
        if(strcmp(empno, em.empno) == 0)
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
    employee em;
    Buffer b;
    do {
        cout<<"\n1. Enter Record\n2. Search Records\n3. View Records\n0. Quit\nEnter Option : ";
        cin>>op;
        switch(op) 
        {
            case 1:
                cout<<"Employee Number : ";
                cin>>em.empno;
                cout<<"Name : ";
                cin>>em.name;
                cout<<"Number of Children";
                cin>>em.num_child;
                em.children = new child*[stoi(em.num_child)];
                for(int i=0; i<stoi(em.num_child); i++)
                {
                    em.children[i] = new child[stoi(em.num_child)];
                    cout<<"Name : ";
                    cin>>em.children[i]->name;
                    cout<<" Age : ";
                    cin>>em.children[i]->age;
                }
                b.pack(s);
                break;
            case 2:
            {
                char empno[4];
                cout<<"Roll to search : ";
                cin>>empno;
                int a=search(empno, b);
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