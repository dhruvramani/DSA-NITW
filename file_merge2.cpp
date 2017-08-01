#include <iostream>
#include <fstream>
using namespace std;

#define max_size 50

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

void merge(int arr1[], int arr2[], fstream &file, int n, int m)
{
    int i=0, j=0;
    while(i<n && j<m)
        if(arr1[i] < arr2[j])
            file<<arr1[i++]<<"\t";
        else 
            file<<arr2[j++]<<"\t";
    while(i<n)
        file<<arr1[i++]<<"\t";
    while(j<m)
        file<<arr2[j++]<<"\t";
}

void display(int a[], int n, fstream &file)
{
    for(int i=0; i<n; i++)
    {
        cout<<a[i]<<"\t";
        file<<a[i]<<"\t";
    }
    cout<<endl;
}

int main()
{
    fstream i1("input1.txt", ios::in), i2("input2.txt", ios::in);
    fstream o1("output1.txt", ios::out), o2("output2.txt", ios::out), o3("output3.txt", ios::out);
    int arr1[max_size], arr2[max_size], i=0, j=0;
    
    while(i1>>arr1[i++]);
    while(i2>>arr2[j++]);
    j--; i--;
    sort(arr1, i);
    sort(arr2, j);
    display(arr1, i, o1);
    display(arr2, j, o2);
    merge(arr1, arr2, o3, i, j);
    return 0;
}