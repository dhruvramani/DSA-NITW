#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

struct records{
    string roll;
    string name;
    string branch;
};

void unpack(string original, records *buffer, char delim, char record_delim )
{
    int flag = 0, v1 = 0, v2 = 0, v3 = 0;
    for(int i = 0 ; i < original.length() ; i++){

        if(original[i] == record_delim)
            break;
        else if(original[i] == delim){
            flag++;
            continue;
        }

        if(flag == 0){
            buffer->roll[v1] = original[i];
            v1++;
        }
        else if(flag == 1){
            buffer->name[v2] = original[i];
            v2++;
        }
        else if(flag == 2){
            buffer->branch[v3] = original[i];
            v3++;
        }
    }
}

string pack(records buffer, char delim, char record_delim)
{
    string bfr = "";
    bfr = bfr + buffer.roll + " " + delim + " " + buffer.name + " " + delim + " " + buffer.branch + " " +record_delim;
    return bfr;
}

void search(records *buffer, string r, fstream& f1)
{
    string roll;
    string tmp[5];

    while(!f1.eof()){
        f1>>roll>>tmp[0]>>tmp[1]>>tmp[2]>>tmp[3]>>tmp[4];
        if(roll == r){
            buffer->roll = r;
            buffer->name = tmp[1];
            buffer->branch = tmp[3];
        }
    }
}

int hsh(int k, int size){
    return k%size;
}

records read(fstream &f1, int r ){
    f1.seekg(0, f1.beg);
    records buffer;
    string original;
    getline(f1, original);

    while(--r){
        getline(f1, original);
    }

    int flag = 0, v1 = 0, v2 = 0, v3 = 0;
    for(int i = 0 ; i < original.length() ; i++)
    {
        if(original[i] == '|')
            break;
        else if(original[i] == '#')
        {
            flag++;
            continue;
        }

        if(flag == 0)
        {
            buffer.roll[v1] = original[i];
            v1++;
        }
        else if(flag == 1)
        {
            buffer.name[v2] = original[i];
            v2++;
        }
        else if(flag == 2)
        {
            buffer.branch[v3] = original[i];
            v3++;
        }
    }
    return buffer;
}

void write(fstream &f1, int r, records buffer)
{
    string ans = pack(buffer, '|', '#'), str = "1";
    f1.seekg(0, f1.beg);
    while(--r){
        getline(f1, str);
        if(str == "")
            f1<<"\n" ;
    }
    f1<<ans;
}

void add(fstream &f3, records buffer, int n)
{
    records tbuffer;
    int k = atoi((buffer.roll).c_str()), cntr = 0, r = hsk(k, n);
    int r = hsh(k, n);

    while(tbuffer.roll != ""){
        tbuffer = read(f3, r);
        r = (r + 1) % n;
        cntr++;
        if(cntr > n)
            break;
    }

    if(cntr < n){
        string ans = pack(buffer, '|', '#'), str = "1";
        ifstream f1("output.txt");
        fstream f2;
        f2.open("output.txt", ios::out | ios::in );
        string original = "";
        while(--r){
            if(original == "")
                f2<<"\n"<<endl;
            getline(f1, original);
    
        }
        int pos = f1.tellg();
        f2.seekp(pos, f2.beg);
        f2<<ans;
    }
}

int search(int element)
{       
    ifstream fin("output.txt");
    int n, loc = element % 10, element2 = element;
    string original = "";
    char ch;
    for(int i = 0 ; !fin.eof() && element2-- ; i++);
    string ch1 = original[0] + "";
    int n1 = atoi(ch1.c_str());
    if(n1==element)
        return 1;
    for(int i = 0 ; !fin.eof() && element2-- ; i++){
        getline(fin, original);   
        if(n=element)
            return 1;
    }
    return 0;
}

int main()
{
    int size;
    fstream of1("output.txt");
    cout<<"Number of Records : "<<endl;
    cin>>size;
    records buffer[size];
    for(int i = 0 ; i < size ; i++){
        cout<<"Enter Roll Number, Name, Branch : " ;
        cin>>buffer[i].roll>>buffer[i].name>>buffer[i].branch ;
        add(of1, buffer[i], 10);
    }

    records op;
    of1.seekp(0, of1.beg);
    int n, n2;
    cout<<"Record to Print"<<endl;
    cin>>n;
    of1.seekp(of1.beg + 27*n);
    cout<<"Roll to Print"<<endl;
    cin>>n2;
    cout<<search(n2);
    of1.seekg(0, of1.beg);
    of1.close();
    return 0;
}