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

int isempty(stack S)
{
	return S.top == -1;
}

int is_full(queue Q)
{
	return (Q.rear + 1) % Q.size == Q.front;
}

int is_full(stack S)
{
	return S.top == S.size - 1;
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
	reverse(Q);
	for(int i=0; i<Q.size; i++)
		cout<<dequeue(Q)<<" ";
	return 0;
}
