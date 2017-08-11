#include <iostream>
using namespace std;

void perm(char a[], int n, int start=0, int size=0)
{
	if(start + size >= n)
		return perm(a, n, 0, size + 1);
	if(size == 0)
	{
		cout<<a[start]<<endl;
		return perm(a, n, start + 1, size);
	}
	for(int j = start + 1; j<n; j ++)
	{
		if(j+size > n)
			continue;
		cout<<a[start];
		for(int i = j; i<j + size; i++)
			cout<<a[i];
		cout<<"\n";
	}
	return perm(a, n, start + 1, size);
}

int main()
{
	char a[] = "abcde";
	perm(a, 5);
	return 0;
}
