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
    f.close();
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

int main()
{
    int pos, data;


}