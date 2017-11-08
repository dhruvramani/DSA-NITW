#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#define max_size 50

struct mlnode 
{
    int tag;
    union u {
        char element;
        mlnode *down;
    } data;
    mlnode *next;
};

typedef mlnode *mlptr;

void print(mlptr node)
{   
    if(node == NULL)
        return ;
    if(node->tag == 0)
    {
        if(node->data.element)
            cout<<node->data.element<<", ";
        print(node->next);
    }
    else if(node->tag == 1){
        cout<<"(";
        print(node->data.down);
        cout<<")";
        if(node->next != NULL)
            print(node->next);
    }
}

mlptr init(mlptr m)
{
    m = new mlnode;
    m->next = NULL;
    return m;
}

mlptr create(mlptr head, char a[])
{
    mlptr run = head, old[max_size];
    int old_count = 0;
    for(int i=0; a[i]; i++)
        if(a[i] == '(')
        {
            run->tag = 1;
            run->data.down = new mlnode;
            old[old_count++] = run;
            run = run->data.down;
        } else if (a[i] == ')')
        {
            run->next = NULL;
            run = old[--old_count];
            run->next = new mlnode;
            run = run->next;
        }
        else if(a[i] == ',' || a[i] == ' ');
        else {
            run->tag = 0;            
            run->data.element = a[i];
            run->next = new mlnode;
            run = run->next;
        }
    run->next = NULL;
    return head;
}

mlptr add(mlptr head, char a[])
{
    mlptr run = head;
    while(run->next != NULL)
        run = run->next;
    run->next = new mlnode;
    run = run->next;
    if(strlen(a) == 1)
    {
        run->tag = 0;
        run->data.element = a[0];
        run->next = NULL;
    } else {
        run->next = NULL;
        run = create(run, a);
    }
    return head;
}

int main()
{
    mlptr head;
    head = init(head);
    int n;
    cout<<"Enter Number to be added : ";
    cin>>n;
    for(; n>=0; n--)
    {
        char a[max_size];
        cout<<"Enter Expression : ";
        gets(a);
        head = add(head, a);
        print(head);
        cout<<endl<<endl;
    }
    return 0;
}