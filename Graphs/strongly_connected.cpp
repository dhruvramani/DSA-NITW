#include <iostream>
using namespace std;

# define n 10

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
}

int visited[n] = {0}, count[n] = {0}, curr_count = 0;
void DFT(int G[][n], int start, int first=0)
{
    int br = 1;
    for(int i=0; i<n && br == 1; i++)
        if(start != i && G[start][i] && visited[i] == 0)
            br = 0;
    if(br == 1)
    {
        ::visited[start] = 1;
        if(first == 0)
        {
            ::count[start] = -1;
            cout<<start + 1<<" ";
        }
        else
            ::count[start] = ++curr_count;
        return;
    }
    ::visited[start] = 1;
    if(first == 0)
    {
        cout<<start + 1<<" ";
        ::count[start] = -1;
    }
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start && ::visited[i] == 0)
            DFT(G, i, first);
    if(first == 1)
        ::count[start] = ++curr_count;
}       

void connected_comp(int G[][n])
{
    int done = 0;
    while(done == 0)
    {
        int index = -1;
        for(int i=0; i<n && index == -1; i++)
            if(::visited[i] == 0)
                index = i;
        if(index == -1)
            break;
        DFT(G, index, 1);
    }

    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            {
                int k = G[i][j];
                G[i][j] = G[j][i];
                G[j][i] = k;
            }

    done = 0;
    for(int i=0; i<n; i++)
        ::visited[i] = 0;
    while(done == 0)
    {
        done = 1;
        int max = -10000, ind=-1;
        for(int i=0; i<n && done == 1; i++)
            if(::count[i] != -1)
                done = 0;
        if(done == 1)
            break;
        for(int i=0; i<n; i++)
            if(::count[i] > max)
            {
                ind = i;
                max = ::count[i];
            }
        DFT(G, ind, 0);
        cout<<endl;
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
    insert(G, 2, 6);
    insert(G, 3, 1);
    insert(G, 3, 4);
    insert(G, 3, 5);
    insert(G, 4, 5);
    insert(G, 6, 3);
    insert(G, 7, 6);
    insert(G, 7, 8);
    insert(G, 8, 6);
    insert(G, 8, 10);
    insert(G, 10, 9);
    insert(G, 9, 8);

    cout<<endl;
    connected_comp(G);
    return 0;
}