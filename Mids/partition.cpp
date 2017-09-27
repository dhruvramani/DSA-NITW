#include <fstream>
#include <iostream>
using namespace std;

void merge(int a[], int b[], int c[], int n, int m)
{
    int i=0, j=0, k=0;
    while(i<n && j<m)
        if(a[i] < b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    while(i<n)
        c[k++] = a[i++];
    while(j<m)
        c[k++] = b[j++];
}

void sort(int a[], int n)
{
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(a[j] > a[j+1])
            {
                int k = a[j];
                a[j] = a[j+1];
                a[j+1] = k;
            }
}


int main()
{
    fstream f1("part1.txt", ios::in), f2("part2.txt", ios::in), f3("partout.txt", ios::out);
    int a[1000], count1=0, co=0;
    while(!f1.eof())
    {   
        int c[100], input, i=0;
        char d;
        while(f1>>input>>d)
        {
            c[i++] = input;
            if(d == '|')
                break;
        }
        if(i > 0)
        {
            int j[1000];
            for(int i=0; i<count1; i++)
                j[i] = a[i];
            merge(c, j, a, i, count1);
            count1 += i;
        }
        co++;
    }
    while(!f2.eof())
    {   
        int c[100], input, i=0;
        char d;
        while(f2>>input>>d)
        {
            c[i++] = input;
            if(d == '\n')
                break;
        }
        if(i > 0)
        {
            int j[1000];
            for(int i=0; i<count1; i++)
                j[i] = a[i];
            merge(c, j, a, i, count1);
            count1 += i;
        }
        co++;
    }
    f1.close();
    f2.close();
    sort(a, count1);
    for(int i=0; i<count1; i++)
        f3<<a[i]<<" ";
    f3.close();
    return 0;
}