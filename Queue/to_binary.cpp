#include <iostream>
#include <string>
using namespace std;

string to_base(int a, int base)
{
    string strk = "0123456789ABCDEF";
    return (base > a)? strk[a]: strcat(strk[a%base], to_base(a/base, base));
}

int main()
{
    int n, b;
    cout<<"Enter Number and Base : ";
    cin>>n>>b;
    cout<<to_base(n, b);
    return 0;
}