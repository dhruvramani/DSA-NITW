#include <iostream>
using namespace std;

# define n 12

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;

}

void euler_cycle(int G[][n], int a)
{
    int start = a, stack1[2*n] = {0}, stack2[n] = {0}, count1=0, count2=0;
    while(count2 < n)
    {
        int to_go = 0;
        for(int i=0; i<n && to_go == 0; i++)
            if(G[a][i] && a != i)
            {
                G[a][i] = 0;
                G[i][a] = 0;
                stack1[count1++] = a;
                a = i;
                to_go++;
            }
        if(to_go == 0)
        {
            cout<<stack1[count1]<<" ";
            stack2[count2++] = stack1[count1--];
            cout<<stack2[count2-1]<<endl;
            a = stack1[count1];
        }
    }

    for(int i=count2-1; i>=0; i--)
    {
        cout<<stack2[i]+1<<" ";
    }
}

int main()
{
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    insert(G, 1, 2);
    insert(G, 1, 4);
    insert(G, 2, 3);
    insert(G, 2, 4);
    insert(G, 2, 6);
    insert(G, 2, 7);
    insert(G, 2, 5);
    insert(G, 3, 4);
    insert(G, 4, 5);
    insert(G, 4, 8);
    insert(G, 4, 9);
    insert(G, 5, 7);
    insert(G, 5, 8);
    insert(G, 6, 7);
    insert(G, 7, 8);
    insert(G, 7, 10);
    insert(G, 7, 11);
    insert(G, 8, 9);
    insert(G, 8, 10);
    insert(G, 8, 12);
    insert(G, 5, 8);
    insert(G, 11, 12);
    euler_cycle(G, 0);
}