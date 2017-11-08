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

char* strip(char a[])
{
    static char c[max_size];
    for(int i=0, j=0; a[i]; i++)
        if(a[i] != ',' && a[i] != ' ' && a[i] != '(' && a[i] != ')')
            c[j++] = a[i];
    return c;
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

int search(mlptr run, char a[], int inside=0, int count=0)
{
    if(run == NULL)
        return inside;
    if(run->tag == 0)
    {
        if(run->data.element == a[count])
            if(inside == 0)
                return 1;
            else 
                return 1 && search(run->next, a, 1, count + 1);
        else 
            if(inside == 0)
                return search(run->next, a);
            else
                return 0;
    } else if(run->tag == 1 && strlen(a) != 1) {
        mlptr k = run;
        run = run->data.down;
        int r = search(run, a, 1);
        if(r == 1)
            return 1;
        run = k;
        return search(run->next, a);
    } else if(strlen(a) == 1)
        return search(run->next, a);
}

int main()
{
    mlptr head;
    head = init(head);
    char a[max_size];
    cout<<"Enter Expression : ";
    gets(a);
    head = create(head, a);
    cout<<"Enter Expression to Search : ";
    gets(a);
    char *c = strip(a);
    if(search(head, c) == 0)
        cout<<"Not ";
    cout<<"Found";
    return 0;
}