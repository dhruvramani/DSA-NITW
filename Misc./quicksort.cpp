#include <iostream>
using namespace std;

void quicksort(int a[], int low, int high)
{
    if(low == high-1 || low == high)
        return ;
    int pivot = low, l = pivot + 1, h = high-1; 
    while(l < h)
    {
        while(a[l] < a[pivot])
            l++;
        while(a[h] > a[pivot])
            h--;
        if(l >= h) 
            break;
        int k = a[l];
        a[l] = a[h];
        a[h] = k;
    }
    l--;
    h++;
    int k = a[pivot];
    a[pivot] = a[l];
    a[l] = k;
    quicksort(a, low, l+1);
    quicksort(a, h, high);
}

int main()
{   
    int a[] = {15, 8, 1, 27, 32, 9, 4, 22, 11};
    quicksort(a, 0, 9);
    for(int i=0; i<9; i++)
        cout<<a[i]<<" ";
    return 0;
}