#include <iostream>
using namespace std;

struct lnode 
{
    int data;
    int c;
    lnode **next;
};
typedef lnode *lptr;

llptr init(lptr m)
{
    m = new lnode;
    m->next = NULL;
    return m;
}

lptr create(lptr head)
{
    lptr l1 = head;
    l1->element = 1;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1 = l1->next[0];
    l1->element = 2;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1 = l1->next[0];
    l1->element = 3;
    l1->c = 2;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1->next[1] = new lnode;
    l2 = l1->next[1];
    l2->element = 10;
    l2->c = 2;
    l2->next = new lptr*[l2->c];
    l2->next[0] = new lnode;
    l2->next[1] = new lnode;
    l2 = l2->next[0];
    l3 = l2->next[1];
    l2->element = 11;
    l2->c = 1;
    l2->next = new lptr*[l2->c];
    l2->next[0] = new lnode;
    l2 = l2->next[0];
    l2->element = 12;
    l2->c = 0;
    l2->next = NULL;
    l3->element = 13;
    l3->c = 1;
    l3->next = new lptr*[l3->c];
    l3->next[0] = new lnode;
    l3 = l3->next[0];
    l3->element = 14;
    l3->c = 1;
    l3->next = new lptr*[l3->c];
    l3->next[0] = new lnode;
    l3 = l3->next[0];
    l3->element = 15;
    l3->c = 0;
    l3->next = NULL;
    l1 = l1->next[0];
    l1->element = 4;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1 = l1->next[0];
    l1->element = 5;
    l1->c = 2;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1->next[1] = new lnode;
    l2 = l1->next[1];
    l2->element = 8;
    l2->c = 1;
    l2->next = new lptr*[l2->c];
    l2->next[0] = new lnode;
    l2 = l2->next[0];
    l2->element = 9;
    l2->c = 1;
    l2->next = NULL;
    l1 = l1->next[0];
    l1->element = 6;
    l1->c = 1;
    l1->next = new lptr*[l1->c];
    l1->next[0] = new lnode;
    l1 = l1->nex[0];
    l1->element = 7;
    l1->c = 0;
    l1->next = NULL;
    return head;
}

void print(lptr head)
{
    cout<<head->element;
    for(int i=0; i<head->c; i++)
    {
        print(head->next[i]);
        cout<<endl;
    }
}

int main()
{
int main()
{
    lptr head;
    head = init(head);
    head = create(head);
    print(head);
    return 0;
}