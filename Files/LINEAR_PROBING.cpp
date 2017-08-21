#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef char integer[4];
typedef char floating[6];

char* record_delim = "#";
char* delim = "|"; 

struct employee {
    integer  empno;
    char name[10];
};

class Buffer
{
    int nextpos;
    public :
    char buff[100];
    int size;
    Buffer()
    {
        size = 40;
        nextpos=0;
        strcpy(buff, "");
    }

    void init(fstream &f)
    {
        for(int i=0; i<size; i++)
            f<<" "<<record_delim[0];
    }

    int hash(char *empno)
    {
        return stoi(empno) % size;
    }

    void add(fstream &f, employee em)
    {
        int position = hash(em.empno), count = 0;
        while(cout < size -1)
        {
            cout<<position<<" "<<count;
            while(pack(f, em, position) == 0 && position < size)
            {
                position++;
                count++;
            }
            if(position == size - 1 && count != size -1)
                position = 0;
        }
        if(count == size - 1)
            cout<<"Overflow";
    }

    int pack(fstream &f,employee em, int position)
    {   
        strcpy(buff, "");
        strcat(buff, em.empno);
        strcat(buff, delim);
        strcat(buff, em.name);
        //strcat(buff, record_delim);
        nextpos += 14;
        f.clear();
        f.seekp(0, ios::beg);
        f.seekg(0, ios::beg);
        char c;
        int i=0;
        while(i<position)
        {
            f>>c;
            //cout<<c<<" "<<i<<" "<<record_delim[0]<<endl;
            if(c == '#')
                i++;
        }
        f>>c;
        if(c == ' ')
            return 0;
        f<<buff;
        return 1;
    }

    employee unpack(fstream &f)
    {
        char c, *co = &c;
        employee s;
        for(int count=1; count <= 2; count++)
        {
            do
            {
                f>>c;
                if(c != delim[0] && c != record_delim[0])
                {
                   if(count == 1)
                        strcat(s.empno, co);
                    else if(count == 2)
                        strcat(s.name, co);
                }
            } while(c != delim[0] && c != record_delim[0]);
        }
        return s;
    }
};

void read(Buffer b)
{
    fstream f("file3.txt", ios::in);
    while(!f.eof()) {
        employee s=b.unpack(f);
        cout<<"Roll : "<<s.empno<<" Name : "<<s.name<<endl;
    }
}

int search(char* empno, Buffer b)
{
    employee s;
    int count=b.hash(empno);
    fstream f("file3.txt", ios::in);
    f.seekg(count);
    while(!f.eof())
    {
        employee s=b.unpack(f);
        if(strcmp(empno, s.empno) == 0)
        {
            f.close();
            return count;
        }
        count++;
    }
    f.close();
    return -1;
}   

int main()
{
    int op;
    employee em;
    Buffer b;
    fstream f("file3.txt", ios::out | ios::in);
    b.init(f);
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
                b.add(f, em);
                break;
            case 2:
            {
                char empno[4];
                cout<<"Empno to search : ";
                cin>>empno;
                int a=search(empno, b);
                if(a != -1)
                    cout<<"Emp No. found";
                else cout<<"Emp No. not found";
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
    f.close();
    return 0;
}