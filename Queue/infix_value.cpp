#include <fstream>
#include <iostream>
using namespace std;

#define max_size 50

union op
{
	char operate;
	int operand;
};

struct queue {
	int front, rear, size;
	int tags[max_size];
	union op elements[max_size];
};

struct stack {
	int top, size;
	int tags[max_size];
	union op elements[max_size];
};

int isempty(queue Q)
{
	return Q.rear == -1 || Q.front == -1;
}

int is_full(queue Q)
{
	return (Q.rear + 1) % Q.size == Q.front;
}

void enqueue(queue& Q, int tag, op a)
{
	if(is_full(Q))
	{
		cout<<"Queue is full."<<endl;
		return ;
	}
	if(isempty(Q))
		Q.front=0;
	Q.elements[(++Q.rear) % Q.size] = a;
	Q.tags[Q.rear % Q.size] = tag;
	Q.size++;
}

op dequeue(queue& Q)
{
	op x;
	x.operand = -1000;
	if(isempty(Q))
		return x;
	x = Q.elements[Q.front];
	if(Q.front == Q.rear)
	{
		Q.rear = -1;
		Q.front = -1;
	} else 
		Q.front = (Q.front + 1) % Q.size;
	Q.size--;
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

op pop(stack& S)
{
	op x;
	x.operand = -1000;
	if(isempty(S))
		return x;
	return S.elements[S.top--];
}

int tag_peep(stack& S)
{
	if(isempty(S))
		return -1;
	return S.tags[S.top];
}

void push(stack& S, int tag, op a)
{
	if(is_full(S))
	{
		cout<<"Stack is full."<<endl;
		return;
	}
	S.elements[++S.top] = a;
	S.tags[S.top] = tag;	
} 

op perform_operation(op inta, op intb, op operatr)
{
	op k;
	k.operand = -1;
	char l = operatr.operate;
	switch(l)
	{
		case '+':
			k.operand = inta.operand + intb.operand;
			break;
		case '-':
			k.operand = inta.operand - intb.operand;
			break;
		case '*':
			k.operand = inta.operand * intb.operand;
			break;
		case '/':
			k.operand = inta.operand / intb.operand;
			break;
	}
	return k;
}

void prefix_value(queue &Q)
{
	stack S;
	S.top = -1; S.size = Q.size;
	int original_size = Q.size;
	while(Q.size > 0)
	{
		push(S, Q.tags[Q.front % Q.size], dequeue(Q));
		if(tag_peep(S) == 0)
		{
			push(S, Q.tags[Q.front % Q.size], dequeue(Q));
			if(tag_peep(S) == 0)
			{
				enqueue(Q, 0, pop(S));
				enqueue(Q, 0, pop(S));
			} else {
				push(S, Q.tags[Q.front % Q.size], dequeue(Q));
				if(tag_peep(S) != 0)
				{
					push(S, Q.tags[Q.rear], dequeue(Q));
					if(tag_peep(S) != 0)
						enqueue(Q, 1, perform_operation(pop(S), pop(S), pop(S)));
				}
			}
		}
		if(Q.size < original_size)
			prefix_value(Q);
		else 
			break;	
	}
	op k = dequeue(Q);
	cout<<"Value : "<<k.operand;
}


int main()
{
	cout<<"Hello";
	queue Q;
	Q.front = -1; Q.rear = -1; Q.size = 0;
	fstream f("input.txt", ios::in);
	int tag;
	while(f>>tag)
	{
		union op a;
		if(tag == 0)
		{
			f>>a.operate;
			cout<<a.operate<<" ";
		}
		else 
		{
			f>>a.operand;
			cout<<a.operand<<" ";
		}
		enqueue(Q, tag, a);
	}
	cout<<endl;
	Q.front = 0;
	f.close();
	prefix_value(Q);
	return 0;
}
