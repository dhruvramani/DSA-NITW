#include <iostream>
using namespace std;

#define max_size 50

struct stack {
	int top1, top2, size;
	int elements[2 * max_size];
};

int isempty(stack S, int tag)
{
	return (tag == 1)?S.top1 == S.size/2:S.top2 == S.size/2;
}

int is_full(stack S, int tag)
{
	return (tag == 1)?S.top1 == 0:S.top2 == S.size;
}

int pop(stack& S, int tag)
{
	if(isempty(S, tag))
		return -1000;
	return (tag == 1)?S.elements[S.top1++]:S.elements[S.top2--];
}

void push(stack& S, int x, int tag)
{
	if(is_full(S, tag))
	{
		cout<<"Stack is full."<<endl;
		return ;
	}

	if(tag == 1)
		S.elements[--S.top1] = x;
	else 
		S.elements[++S.top2] = x;	
}

void init_stack(stack &S)
{
	S.size = max_size;
	S.top1 = S.size/2;
	S.top2 = S.size/2;
}


int main()
{
	stack s;
 	init_stack(s);
 	int op, i;
    do {
    	cout<<"\n1. Push in Stack 1\n2. Push in Stack 2\n3. Pop from Stack 1\n4. Pop from Stack 2\n0. Quit\nChoose one : ";
        cin>>op;
        switch(op)
        {
            case 1:
                cout<<"Enter Value : ";
                cin>>i;
                push(s, i, 1);
                break;
            case 2:
                cout<<"Enter Value : ";
                cin>>i;
                push(s, i, 2);
                break;
            case 3:
                cout<<"Value : "<<pop(s, 1)<<endl;
                break;
            case 4:
                cout<<"Value : "<<pop(s, 2)<<endl;
                break;
            case 0:
            	cout<<"Quiting.";
            	break;
            default :
                cout<<"Bad Choice";
        }
    } while(op != 0);
    return 0;
}
