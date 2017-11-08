#include <iostream>
#include <stdio.h>
using namespace std;

#define max_size 50

struct mlnode 
{
    int element;
    mlnode *down;
    mlnode *next;
};

typedef mlnode *mlptr;

int index_of(int a[], int n, int k)
{
    for(int i=0; i<n; i++)
        if(a[i] == k)
            return i;
    return -1;
}

void print(mlptr m)
{
    mlptr node = m;
    int down[] = {5, 3, 10};
    int counter = 0;
    /*while(node != NULL)
    {
        if(node->down != NULL)
            down[counter++] = node->element;
        cout<<node->element<<" ";
        node = node->next;
    }
    cout<<endl; */
    while(counter < 3)
    {
        node = m;
        while(node != NULL)
        {
            if(node->element != 0)
                cout<<node->element<<" ";
            if(node->element == down[counter])
            {
                mlptr noda = node->next;
                while(noda != NULL)
                {

                    cout<<noda->element<<" ";
                    noda = noda->next;
                } 
                cout<<endl;
                mlptr nodi = m;
                while(nodi->element != node->element)
                {
                    cout<<nodi->element<<" ";
                    nodi = nodi->next;
                }
                node = node->down;
                counter++;
            } else {
                node = node->next;
            }
        }
        cout<<endl;
    }
}

mlptr init(mlptr m)
{
    m = new mlnode;
    m->next = NULL;
    m->down = NULL;
    return m;
}

mlptr create(mlptr head)
{
    mlptr l1 = head;
    l1->element = 1;
    l1->down = NULL;
    l1->next = new mlnode;
    l1 = l1->next;
    l1->element = 2;
    l1->down = NULL;
    l1->next = new mlnode;
    l1 = l1->next;
    l1->element = 3;
    l1->down = new mlnode;

    mlptr downvar = l1->down;
    downvar->element = 10;
    downvar->down = new mlnode;
    
    mlptr newdown = downvar->down;
    newdown->element = 13;
    newdown->down = NULL;
    newdown->next = new mlnode;
    newdown = newdown->next;
    newdown->element = 14;
    newdown->down = NULL;
    newdown->next = new mlnode;
    newdown = newdown->next;
    newdown->element = 15;
    newdown->down = NULL;
    newdown->next = NULL;

    downvar->next = new mlnode;
    downvar = downvar->next;
    downvar->element = 11;
    downvar->down = NULL;
    downvar->next = new mlnode;
    downvar = downvar->next;
    downvar->element = 12;
    downvar->down = NULL;
    downvar->next = NULL;

    l1->next = new mlnode;
    l1 = l1->next;
    l1->element = 4;
    l1->down = NULL;
    l1->next = new mlnode;
    l1 = l1->next;
    l1->element = 5;
    l1->down = new mlnode;

    downvar = l1->down;
    downvar->element = 8;
    downvar->next = new mlnode;
    downvar = downvar->next;
    downvar->element = 9;
    downvar->down = NULL;
    downvar->next = NULL;

    l1->next = new mlnode;
    l1 = l1->next;
    l1->element = 6;
    l1->down = NULL;
    l1->next = new mlnode;
    l1 = l1->next;
    l1->element = 7;
    l1->down = NULL;
    l1->next = NULL;
    return head;
}


int main()
{
    mlptr head;
    head = init(head);
    head = create(head);
    print(head);
    return 0;
}