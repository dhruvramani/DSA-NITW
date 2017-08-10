#include <iostream>
using namespace std;

#define max_size 50

int pow(int x, int p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * pow(x, p-1);
}

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

void radix_sort(int a[], int n, int base)
{
	int go = 0, j=0;
	for(int i=0; i<n; i++)
		if(a[i]/pow(10, base) != 0)
			go = 1;
	if(go == 0)
		return ;
	queue list[10];
	for(int i=0; i<10; i++)
		init_queue(list[i]);
	for(int i=0; i<n; i++)
		enqueue(list[(a[i] % pow(10, base)) / pow(10, base-1)], a[i]);
	for(int i=0; i<10; i++)
		while(!isempty(list[i]))
			a[j++] = dequeue(list[i]);
			
	radix_sort(a, n, base + 1);
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
	radix_sort(a, n, 1);
	for(int i=0; i<n; i++)
		cout<<a[i]<<" ";
	return 0;
}
