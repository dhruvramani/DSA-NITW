#include <iostream>
using namespace std;

#define max_size 50

struct queue {
	int front, rear, size;
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

void init_queue(queue &Q)
{
	Q.size = max_size;
	Q.front = -1;
	Q.rear = -1;
}

void bubble_sort(int a[], int n)
{
	queue Q;
	init_queue(Q);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
			if(a[j] > a[j+1] && j != n-1)
			{
				enqueue(Q, a[j+1]);
				enqueue(Q, a[j]);
				j++;
			} else 
				enqueue(Q, a[j]);
		for(int j=0; j<n; j++)
			a[j] = dequeue(Q);
	}
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
