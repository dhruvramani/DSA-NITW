#include <fstream>
using namespace std;

#define max_size 50

void sort(int a[], int n)
{
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i; j++)
            if(a[j] > a[j+1])
            {
                int k = a[j];
                a[j] = a[j+1];
                a[j+1] = k;
            }
}

int merge(int arr1[], int arr2[], int arr3[], int n, int m)
{
    int i=0, j=0, k=0;
    while(i<n && j<m)
        if(arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else 
            arr3[k++] = arr2[j++];
    while(i<n)
        arr3[k++] = arr1[i++];
    while(j<m)
        arr3[k++] = arr2[j++];
}

void display(int a[], int n)
{
    for(int i=0; i<n; i++)
        cout<<a[i]<<"\t";
    cout<<endl;
}

int main()
{
    fstream i1("input1.txt", ios::in), i2("input2.txt", ios::in);
    int arr1[max_size], arr2[max_size], arr3[max_size + max_size] i, j;
    
    while(i1>>arr1[i++]);
    while(i2>>arr2[j++]);
    sort(arr1);
    sort(arr2);
    merge(arr1, arr2, arr3, i, j);
    display(arr3, i+j);
}