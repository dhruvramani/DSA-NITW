#include <iostream>
using namespace std;

void* sum(int a, int b)
{	
	int *c; 
	c = new int(a+b);
	return c;	
}
int main()
{
	void *a;
	a = sum(1, 2);
	cout<<*(int *)a;
}
