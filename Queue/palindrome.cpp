#include <iostream>
using namespace std;

#define max_size 50

struct queue {
	int front, rear, size;
	int elements[max_size];
};

struct stack {
	int top, size;
	int elements[max_size];
};

int isempty(queue Q)
{
	return Q.rear == -1 || Q.front == -1;
}

int is_full(queue Q)
{
	return (Q.rear + 1) % Q.size == Q.front;
}

void enqueue(queue& Q, int x)
{
	if(is_full(Q))
	{
		cout<<"Queue is full."<<endl;
		return ;
	}
	if(isempty(Q))
		Q.front=0;
	Q.elements[(++Q.rear) % Q.size] = x;
}

int dequeue(queue& Q)
{
	if(isempty(Q))
		return -1;
	int x = Q.elements[Q.front];
	if(Q.front == Q.rear)
	{
		Q.rear = -1;
		Q.front = -1;
	} else 
		Q.front = (Q.front + 1) % Q.size;
	return x;
}

int isempty(stack S)
{
	return S.top == -1;
}

int is_full(stack S)
{
	return S.top == S.size - 1;
}

int pop(stack& S)
{
	if(isempty(S))
		return -1000;
	return S.elements[S.top--];
}

void push(stack& S, int x)
{
	if(is_full(S))
	{
		cout<<"Stack is full."<<endl;
		return;
	}
	S.elements[++S.top] = x;	
}


void reverse(queue &Q)
{
	stack S;
	S.top = -1; S.size = Q.size;
	while(!isempty(Q))
		push(S, dequeue(Q));
	while(!isempty(S))
		enqueue(Q, pop(S));
}

int palindrome(queue Q)
{
	queue Q2 = Q;
	reverse(Q2);
	while(!isempty(Q))
		if(dequeue(Q) != dequeue(Q2))
			return 0;
	return 1;
} 

int main()
{
	queue Q;
	Q.front = -1; Q.rear = -1;
	cout<<"Enter number of elements in the queue : ";
	cin>>Q.size;
	for(int i=0; i<Q.size; i++)
	{
		int n;
		cout<<"Enter Number : ";
		cin>>n;
		enqueue(Q, n);
	}
	int a = palindrome(Q);
	if(a == 1)
		cout<<"It's a Palindrome";
	else
		cout<<"It's not a Palindrome";
	return 0;
}
