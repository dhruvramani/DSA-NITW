#include <iostream>
using namespace std;

# define n 6

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;

}

int maximum(int G[][n], int &l, int &k)
{
    int max = -10000000;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(G[i][j] > max && G[i][j] != 0) 
            {
                max = G[i][j];
                l = i;
                k = j;
            }
    return max;
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

void max_span(int G[][n])
{
    int done = 0;
    while(done == 0)
    {
        int r, c, max;
        max = maximum(G, r, c);
        if(r != 0 && c != 1)
            cout<<r + 1<<" "<<c + 1<<" "<<is_bridge(G, r, c)<<endl;
        if(!is_bridge(G, r, c))
        {
            G[r][c] = 0;
            G[c][r] = 0;
        }
        int count = 0;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if(G[i][j])
                    count++;
        if((count/2) == n-1)
            done = 1;
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<G[i][j]<<" ";
        cout<<endl;
    }

}

int main()
{
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            G[i][j] = 0;

    insert(G, 1, 2, 2);
    insert(G, 1, 3, 5);
    insert(G, 2, 3, 2);
    insert(G, 2, 4, 3);
    insert(G, 3, 4, 4);
    insert(G, 3, 5, 6);
    insert(G, 4, 6, 8);
    insert(G, 4, 5, 4);
    insert(G, 5, 6, 7);
    max_span(G);
    return 0;   
}