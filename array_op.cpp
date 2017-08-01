#include <iostream>
using namespace std;

float* array_op(int a[], int start, int n)
{
    if(start == n-1)
    {
        static float to_return[3] = {a[start], a[start]/float(n), a[start]};
        return to_return;
    }
    static float to_return[3] = {a[start], a[start], a[start]};
    float *next = array_op(a, start + 1, n);
    to_return[1] = next[1] + a[start]/float(n);
    if(next[0] > a[start])
        to_return[0] = next[0];
    if(next[2] < a[start])
        to_return[2] = to_return[2];
    return to_return;
}

int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    float *b = array_op(a, 0, 5);
    cout<<"Max : "<<b[0]<<"\tAverage : "<<b[1]<<"\tMin : "<<b[2];
    return 0;
}