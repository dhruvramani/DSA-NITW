#include <iostream>
using namespace std;

#define n 12

void insert(int G[][n], int row, int column, int weight=1)
{ G[row-1][column-1] = weight; }

int stack[n] = {0}, visited[n] = {0}, count=0;
void topo_mini(int G[][n], int s)
{
    visited[s] = 1;
    for(int i=0; i<n; i++)
        if(G[s][i] && !visited[i]) 
            topo_mini(G, i);
    ::stack[::count++] = s;
}

void topological(int G[][n], int s)
{
    topo_mini(G, s);
    while(::count >= 0)
        cout<<::stack[::count--] + 1<<" ";
}

int main()
{
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    insert(G, 1, 7);
    insert(G, 2, 8);
    insert(G, 3, 6);
    insert(G, 4, 6);
    insert(G, 5, 11);
    insert(G, 6, 9);
    insert(G, 7, 10);
    insert(G, 8, 10);
    insert(G, 9, 12);
    insert(G, 10, 12);
    insert(G, 11, 12);
    
    return 0;
}