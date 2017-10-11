#include <iostream>
using namespace std;

#define n 10

int s[n];
int find_root(int i)
{
    if(::s[i] == 0)
        return i;
    return find_root(::s[i]);
}

void uni(int i, int j)
{
    if(j == 0)
        ::s[j] = i;
    else if(i == 0)
        ::s[i] = j;
    else 
        ::s[find_root(j)] = i;
}

int find(int a, int b)
{
    return find_root(a) == find_root(b);
}

int main()
{
    for(int i=0; i<10; i++)
        ::s[i] = 0;
    int i = 0, j = 0;
    while(i != -1 || j != -1)
    {
        cout<<"Enter I, J (-1 to quit): ";
        cin>>i>>j;
        uni(i-1, j-1);
        for(int i=0; i<10; i++)
            cout<<i<<" "<<::s[i]<<endl;
        cout<<endl;
    }
    return 0;
}