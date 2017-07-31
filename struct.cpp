#include <iostream>
using namespace std;
#define max_size 70

struct record {
    string name;
    int roll;
    double CGPA;
};

int search(record rec[], int roll)
{
    int n = sizeof(rec) / sizeof(record);
    for(int i=0;i<n;i++)
        if(rec[i].roll == roll)
            return 1;
    return 0;
}

void print(record rec)
{
    cout<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.CGPA;
}

void input(int n, record rec[])
{
    for(int i=0; i<n; i++)
    {
        cout<<"Roll Number ";
        cin>>rec[i].roll;
        cout<<"Name ";
        cin>>rec[i].name;
        cout<<"CGPA ";
        cin>>rec[i].CGPA;
    }
}
int main()
{
    record recs[max_size];
    int n, o;
    cout<<"Enter your option\n1. Enter record(s)\n2. Search record\n3. Print records\n";
    cin>>o;
    switch(o)
    {
        case 1:
            cout<<"Enter No. of records ";
            cin>>n;
            input(n, recs);
        case 2:
            cout<<"Enter Roll No to search";
            cin>>n;
            cout<<search(recs, n);
        case 3:
            n = sizeof(rec) / sizeof(record);
            for(int i = 0; i<n; i++)
                print(recs[i]);
        default : 
            cout<<"Invalid Option";
    }
    return 0;
}