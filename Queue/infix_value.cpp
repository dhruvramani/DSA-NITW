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

int is_empty(queue Q)
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
	if(is_empty(Q))
		Q.front=0;
	Q.elements[(++Q.rear) % Q.size] = a;
	Q.tags[Q.rear % Q.size] = tag;
}

op dequeue(queue& Q)
{
	op x;
	x.operand = -1000;
	if(is_empty(Q))
		return x;
	x = Q.elements[Q.front];
	if(Q.front == Q.rear)
	{
		Q.rear = -1;
		Q.front = -1;
	} else 
		Q.front = (Q.front + 1) % Q.size;
	return x;
}

int is_empty(stack S)
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
	if(is_empty(S))
		return x;
	return S.elements[S.top--];
}

int tag_peep(stack& S)
{
	if(is_empty(S))
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

op perform_operation(op operatr, op inta, op intb)
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

op prefix_value(queue Q)
{
	stack S;
	S.top = -1; S.size = Q.size;
	while(Q.rear != Q.front)
	{
		int original_size = Q.size;
		for(int i=0; i < original_size; i+=2)
		{
			op a = dequeue(Q);
			if(a.operand == -1000)
			{
				while(!is_empty(S))
					enqueue(Q, S.tags[S.top], pop(S));
				break;
			}
			push(S, Q.tags[Q.rear], a);
			if(tag_peep(S) == 0)
			{
				push(S, Q.tags[Q.rear], dequeue(Q));
				if(tag_peep(S) == 0)
				{
					op k = pop(S); 
					cout<<k.operate<<endl;
					return k;
					enqueue(Q, 0, pop(S));
					enqueue(Q, 0, pop(S));
				} 	
			} else if(tag_peep(S) == 1) {
				push(S, Q.tags[Q.rear], dequeue(Q));
				if(tag_peep(S) == 1)
				{
					push(S, Q.tags[Q.rear], dequeue(Q));
					if(tag_peep(S) == 0)
						enqueue(Q, 1, perform_operation(pop(S), pop(S), pop(S)));
					i += 1;
				}
			}
		}	
	}
	return dequeue(Q);
} 

int main()
{
	queue Q;
	Q.front = -1; Q.rear = -1;
	fstream f("input.txt", ios::in);
	int tag;
	while(f>>tag)
	{
		union op a;
		Q.size++;
		cout<<tag<<" ";
		if(tag == 0)
			f>>a.operate;
		else 
			f>>a.operand;
		enqueue(Q, tag, a);
	}
	f.close();
	op k = prefix_value(Q);
	//cout<<"Value : "<<k.operand;
	return 0;
}
