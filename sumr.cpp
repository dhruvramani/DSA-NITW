#include <iostream>
using namespace std;

int sum(int n)
{
    if(n/10 == 0)
        return n;
    return n%10 + sum(n/10);
}

int main()
{
    int n;
    cout<<"Enter Number : ";
    cin>>n;
    cout<<sum(n);
    return 0;
}