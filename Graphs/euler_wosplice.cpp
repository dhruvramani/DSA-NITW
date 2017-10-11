#include <iostream>
using namespace std;

# define n 12

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;
}

int visited[n] = {0}, bridge_count=0;

void reset()
{
    for(int i=0; i<n; i++)
        ::visited[i] = 0;
    ::bridge_count = 0;
}

void DFT(int G[][n], int start)
{
    int br = 1;
    for(int i=0; i<n && br == 1; i++)
        if(start != i && G[start][i] && visited[i] == 0)
            br = 0;
    if(br == 1)
    {
        ::visited[start] = 1;
        ::bridge_count++;
        return;
    }
    ::visited[start] = 1;
    ::bridge_count++;
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start && ::visited[i] == 0)
            DFT(G, i);
} 


int is_bridge(int G[][n], int row, int column)
{
    reset();
    DFT(G, row);
    int old = ::bridge_count;
    reset();
    G[row][column] = 0;
    DFT(G, row);
    int curr = ::bridge_count;
    reset();
    G[row][column] = 1;
    return !(old == curr);
}

void euler_cycle(int G[][n], int start)
{
    int done = 0;
    while(done == 0)
    {
        int count = 0, index = 0;
        for(int i=0; i<n; i++)
            if(G[start][i])
            {
                index = i;
                count++;
            }
        if(count == 1)
        {
            G[start][index] = 0;
            G[index][start] = 0;
            cout<<start + 1<<" ";
            start = index;
        } else {
            for(int i=0; i<n; i++)
                if(G[start][i] && !is_bridge(G, start, i))
                {
                    G[start][i] = 0;
                    G[i][start] = 0;
                    cout<<start + 1<<" ";
                    start = i;
                    break;
                }
        }

        done = 1;
        for(int i=0; i<n && done == 1; i++)
            for(int j=0; j<n; j++)
                if(G[i][j])
                    done = 0;
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