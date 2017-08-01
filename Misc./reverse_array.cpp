#include <iostream>
using namespace std;

void reverse(int a[], int count, int n)
{
    if(count ==  n/2)
        return ;
    int k = a[count];
    a[count] = a[n-count-1];
    a[n-count-1] = k;
    return reverse(a, count+1, n);
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    reverse(a, 0, 5);
    for(int i=0; i<5; i++)
        cout<<a[i]<<"\t";
    return 0;
}