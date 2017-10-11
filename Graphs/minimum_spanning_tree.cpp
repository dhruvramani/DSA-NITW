#include <iostream>
using namespace std;

# define n 6

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;

}

int minimum(int G[][n], int &l, int &k)
{
    int min = 10000000;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(G[i][j] < min && G[i][j] != 0) 
            {
                min = G[i][j];
                l = i;
                k = j;
            }
    return min;
}

int visited[n] = {0}, count=0;
int is_cycle(int G[][n], int original,  int start)
{
    int br = 1;
    for(int i=0; i<n && br == 1; i++)
        if(start != i && G[start][i] && visited[i] == 0)
            br = 0;
    if(br == 1)
    {
        ::visited[start] = 1;
        return 0;
    }
    ::count++;
    if(G[start][original] && ::count > 2)
        return 1;
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start && ::visited[i] == 0 && start != original)
        {
            if(i != original) 
                ::visited[i] = 1;
            is_cycle(G, original, i);
        }
}

void main_logic(int G[][n])
{
    int done = 0;
    int newG[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            newG[i][j] = 0;

    while(done == 0)
    {
        int i, j, mini;
        mini = minimum(G, i, j);
        int zeros = 1;
        newG[i][j] = mini;
        newG[j][i] = mini;
        G[i][j] = 0;
        G[j][i] = 0;
        int cycle = is_cycle(newG, i, i);
        if(cycle == 1)
        {
            newG[i][j] = 0;
            newG[j][i] = 0;
        } else {
            for(int k=0; k<n; k++)
                G[i][k] = 0;
        }
        for(int i=0; i<n && zeros == 1; i++)
            for(int j=0; j<n; j++)
                if(G[i][j] != 0)
                    zeros = 0;
        done = zeros;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<newG[i][j]<<" ";
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
    main_logic(G);
    return 0;   
}