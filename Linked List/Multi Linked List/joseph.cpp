#include <iostream>
#include <stdio.h>
using namespace std;

#define max_size 50

struct mlnode 
{
    int element;
    mlnode *next;
};

typedef mlnode *mlptr;

mlptr init(mlptr m)
{
    m = new mlnode;
    m->next = NULL;
    return m;
}

void print(mlptr head)
{
    if(head == NULL)
        return ;
    cout<<head->element;
    print(head->next);
}

mlptr create(mlptr head, int &k)
{
    mlptr run = head;
    cout<<"Enter No. of Elements : ";
    cin>>k;
    int n = k;
    for(; n>1; n--)
    {
        cout<<"Enter Value : ";
        cin>>run->element;
        run->next = new mlnode;
        run = run->next;
    }
    cout<<"Enter Value : ";
    cin>>run->element;
    run->next = head;
    return head;
}

int joseph(mlptr head, int n)
{
    while(head->next != head)
    {
        int move = (rand() % (n+1)) + 1;
        for(int i=0; i<move; i++)
            head = head->next;
        mlptr k = head->next;
        head->next = k->next;
        delete k;
    }
    return head->element;
}

int main()
{
    mlptr head;
    head = init(head);
    int n;
    head = create(head, n);
    cout<<joseph(head, n);
    return 0;
}