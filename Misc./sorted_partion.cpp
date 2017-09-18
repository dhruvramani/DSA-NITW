#include <iostream>
using namespace std;

int main()
{
    int a[] = {24, 4, 8, 19, 12, 7, 2, 20, 18, 6, 17, 9 , 16, 10, 11, 21, 22, 1, 23, 3, 13, 15, 14, 5}, min = -1, max = -1;
    for(int i=0; i<sizeof(a)/sizeof(int); i++)
    {
        if(max == -1)
        {
            max = a[i];
            continue;
        }
        if(a[i] > max && min == -1)
        {
            cout<<max<<" ";
            min = max;
            max = a[i];
            continue;
        }
        if(a[i] < max && min == -1)
        {
            cout<<a[i]<<" ";
            min = a[i];
            continue;
        }

        if(a[i] < max && a[i] > min && min != -1 && max != -1)
        {
            cout<<a[i]<<" ";
            min = a[i];
        } else {
            min = -1;
            cout<<max<<endl;
            max = a[i];
        }
    }
    return 0;
}