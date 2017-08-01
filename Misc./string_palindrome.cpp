#include <iostream>
using namespace std;

int string_palindrome(char str[], int pos, int n)
{
    if(pos == n/2)
        return 1;
    return (str[pos] == str[n-pos-1]) && string_palindrome(str, pos+1, n);
}

int main()
{
    char a[] = "radar";
    cout<<"Palindrome? : "<<string_palindrome(a, 0, 5);
    return 0;
}