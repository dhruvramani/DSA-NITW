#include <iostream>
using namespace std;

#define max_size 50

struct stack {
	int top1, top2, size;
	int elements[2 * max_size];
};

int is_empty(stack S, int tag)
{
	return (tag == 1)?S.top1 == -1:S.top2 == 2*S.size;
}

int is_full(stack S)
{
	return (tag == 1)?S.top1 == S.size - 1:S.top2 == S.size + 1;
}

int pop(stack& S, int tag)
{
	if(is_empty(S))
		return -1000;
	return (tag == 1)?S.elements[S.top1--]S.elements[S.top2++];
}

void push(stack& S, int x. int tag)
{
	if(is_full(S))
	{
		cout<<"Stack is full."<<endl;
		return;
	}
	if(tag == 1)
		S.elements[++S.top1] = x;
	else 
		S.elements[S.top2--] = x;	
}

void init_stack(stack &S)
{
	S.size = max_size;
	S.top1 = -1;
	S.top2 = S.size * 2;
}


int main()
{
	int n, a[max_size];
	cout<<"Enter number of elements : ";
	cin>>n;
	for(int i=0; i<n; i++)
	{
		cout<<"Enter Number : ";
		cin>>a[i];
	}
	bubble_sort(a, n);
	for(int i=0; i<n; i++)
		cout<<a[i]<<" ";
	return 0;
}
