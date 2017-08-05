#include <iostream>
using namespace std;
#define max_size 70

struct addr {
    int stno;
    int ctno;
};

union address
{
    int cell;
    struct addr ad;
}; 

struct record {
    string name;
    int roll;
    double CGPA;
    int tag;
    union address a;
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
    cout<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.CGPA<<"\t";
    if(rec.tag == 0)
        cout<<rec.a.cell;
    else 
        cout<<rec.a.ad.stno<<"\t"<<rec.a.ad.ctno;
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
        cout<<"Cell (0) or Address [street number & city number] (1)? ";
        cin>>rec[i].tag;
        cout<<"Enter Value : "
        if(rec[i].tag == 0)
            cin>>rec[i].a.cell;
        else
            cin>>rec[i].a.ad.stno>>rec[i].a.ad.ctno;
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
            n = sizeof(recs) / sizeof(record);
            for(int i = 0; i<n; i++)
                print(recs[i]);
        default : 
            cout<<"Invalid Option";
    }
    return 0;
}