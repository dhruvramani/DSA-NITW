#include <fstream>
#include <iostream>
using namespace std;

void write(fstream &f, int a)
{
    f<<a;
}

void read(fstream &f)
{
    int data;
    while(f>>data)
        cout<<"Roll : "<<s.rno<<" Name : "<<s.name<<" Marks : "<<s.marks<<"\n";
    f.seekg(ios::beg);
}

int search(int data, fstream &f)
{
    int count=0, k;
    while(f>>k)
    {   
        count++;
        if(k == data)
            return count;
    }
    return -1;
}   

void insert_at(fstream &f, int pos, int data)
{
    f.seekp(pos, ios::curr);
    f<<data;
}
void read_at(fstream &f, int pos)
{
    f.seekg(pos, ios::curr);
    f>>data;
}
int main()
{
    int pos, data;


}