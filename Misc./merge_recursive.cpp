#include <iostream>
using namespace std;

void merge(int a1[], int a2[], int a3[], int c1, int c2, int c3, int m, int n)
{
    if(c1 >= m && c2 >=n)
        return ;
    if((c1 >= m-1 && c2 < n) || (a2[c2] < a1[c1]))
    {
        a3[c3] = a2[c2];
        return merge(a1, a2, a3, c1, c2+1, c3+1, m, n);
    }
    if((c1 < m && c2 >= n-1) || (a1[c1] < a2[c2]))
    {
        a3[c3] = a1[c1];
        return merge(a1, a2, a3, c1+1, c2, c3+1, m, n);
    } 
}

int main()
{
    int m=7, n=10, a[] = {2, 4, 5, 24, 32, 43, 53}, b[] = {1, 3, 7, 23, 28, 42, 133, 283, 318, 9803}, c[17];
    merge(a, b, c, 0, 0, 0, m, n);
    for(int i=0; i<m+n; i++)
        cout<<c[i]<<" ";
    return 0;
}