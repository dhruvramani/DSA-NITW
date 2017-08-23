#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

typedef char integer[4];
typedef char floating[6];

char* record_delim = "#";
char* delim = "|"; 

struct employee {
    integer  empno;
    char name[10];
    integer fwdptr, bptr;
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

    void init()
    {
    	fstream f("file3.txt", ios::out);
        for(int i=0; i<size; i++)
            f<<" "<<record_delim[0];
        f.close();
    }

    int hash(char *empno)
    {
        return stoi(empno) % size;
    }

    void add(employee em)
    {
        int position = hash(em.empno), count = 0, original = position;
        while(cout < size -1)
        {
            int done = 0;
            while(done == 0 && position < size)
            {
                done = pack(em, position, original);
                position++;
                count++;
            }
            if(done == 1)
                break;
            if(position == size - 1 && count != size -1)
                position = 0;
        }
        if(count == size - 1)
            cout<<"Overflow";
    }

	int pos(int n, char *delimi)
	{
		
		char c;
		int i = 0, j = 0;
		fstream f("file3.txt", ios::in);
		while(i < n - 1)
        {
            f.get(c);
            if(c == delimi[0])
                i++;
            j++;
        }
        f.close();
        return j;
	}
	
    int pack(employee em, int position, int original)
    {   
        char org[4];
        memcpy(&original, org, sizeof(int));
    	fstream f("file3.txt", ios::out | ios::in);
        strcpy(buff, "");
        strcat(buff, "\r\r #");
        strcat(buff, em.empno);
        strcat(buff, delim);
        strcat(buff, em.name);
        strcat(buff, delim);
        strcat(buff, "-100");
        strcat(buff, delim);
        strcat(buff, org);
        nextpos += 22;
        f.seekp(pos(original, record_delim), ios::beg);
        f.seekg(pos(original, record_delim), ios::beg);
        char c, str[22 * 40];
        int i=0;
        f.clear();
        f.seekp(pos(2, delim), ios::beg);
        f.seekg(pos(2, delim), ios::beg);
        	f<<original;
		f.clear();
		f.seekp(pos(position, record_delim), ios::beg);
        f.seekg(pos(position, record_delim), ios::beg);	
        if(c != ' ')
            return 0;
        fstream f2("file3.txt", ios::in);
        f2.seekg(pos(position + 1, record_delim), ios::beg);
        while(!f2.eof())
        	f2.get(str[i++]);
        f2.close();
        f<<buff<<str;
        f.close();
        return 1;
    }

	employee unpack(int index)
    {
        fstream f("file3.txt", ios::in);
        char c, *co = &c;
        employee s;
		f.seekg(pos(index, record_delim), ios::beg);
        for(int count=1; count <= 4; count++)
        {
            do
            {
                f.get(c);
                if(c != delim[0] && c != record_delim[0])
                {
                   	if(count == 1)
                        strcat(s.empno, co);
                    else if(count == 2)
                        strcat(s.name, co);
                    else if(count == 3)
                    	strcat(s.fwdptr, co);
                    else if(count == 4)
                    	strcat(s.bptr, co);
                }
            } while(c != delim[0] && c != record_delim[0]);
        }
        //while(c ! = record_delim[0] && !f.eof())
        //	f.get(c);
        f.close();
        return s;
    }
};

void read(Buffer b)
{
    fstream f("file3.txt", ios::in);
    char a[100];
    while(!f.eof()) {
        f.getline(a, 100, '#');
        if(strlen(a) >= 3)
            cout<<a<<endl;
    }
    f.close();
}

int search(char* empno, Buffer b)
{
    employee s;
    fstream f("file3.txt", ios::in);
    char a[100], emp[4];
    int count=b.pos(b.hash(empno), record_delim);
    while(!f.eof())
    {
    	strcpy(emp, "");
        f.seekg(count);
        f.getline(a, 100, '#');
        for(int i=0; a[i] != delim[0]; i++)
            emp[i] = a[i];

        if(strcmp(empno, s.empno) == 0) {
        	f.close();
            return count;
    	} else {
        	int fwd = stoi(s.fwdptr);
        	if(fwd == -100) {
        		f.close();
        		return -1;
        	}
        	count = b.pos(fwd, record_delim);
		}
    }
    f.close();
    return -1;
}   

int del(char *empno, Buffer b)
{
	employee s;
    fstream f("file3.txt", ios::in | ios::out);
    int count = b.pos(b.hash(empno), record_delim);
    while(!f.eof())
    {
    	f.seekg(count);
        employee s = b.unpack(count);
        if(strcmp(empno, s.empno) == 0)
        {
    		int to_copy = count;
			char c, str[22 * 39];
			while(c != record_delim[0])
			{
				f.get(c);
				to_copy++;
			}
			f.seekp(to_copy, ios::beg);
			f.getline(str, 22*39);
			f.seekp(cout, ios::beg);
			f<<str;
			f.seekp(to_copy - count, ios::end);
			while(!f.eof())
				f<<' ';
			f.close();
			return 1;
        } else {
        	int fwd = stoi(s.fwdptr);
        	if(fwd == -100)
        	{
        		f.close();
        		return -1;
        	}
        	count = b.pos(fwd, record_delim);
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
    b.init();
    do {
        cout<<"\n1. Enter Record\n2. Search Records\n3. View Records\n4. Delete Records\n0. Quit\nEnter Option : ";
        cin>>op;
        switch(op) 
        {
            case 1:
                cout<<"Employee Number : ";
                cin>>em.empno;
                cout<<"Name : ";
                cin>>em.name;
                b.add(em);
                break;
            case 2:
            {
                char empno[4];
                cout<<"Empno to search : ";
                cin>>empno;
                int a = search(empno, b);
                if(a != -1)
                    cout<<"Emp No. found";
                else cout<<"Emp No. not found";
                break;
            }
            case 3: 
                read(b);
                break;
            case 4: 
            {
            	char empno[4];
                cout<<"Empno to delete : ";
                cin>>empno;
                int a = del(empno, b);
                if(a != -1)
                    cout<<"Emp Deleted.";
                else cout<<"Emp No. not found";
                break;
            }
            case 0:
                cout<<"Quitting";
                break;
            default :
                cout<<"Invalid Option";
        }
    } while(op != 0);
    return 0;
}
