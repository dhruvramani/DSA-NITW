#include <iostream>
using namespace std;

# define n 10

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
}

int search(int edges[][2], int m, int a, int b)
{
    for(int i=0; i<m; i++)
        if(edges[i][0] == a && edges[i][1] == b)
            return 1;
    return 0;
}

int visited[n] = {0}, count[n] = {0}, boo_count = 0;
int components[n][n] = {0}, count_comp[n] = {0}, curr_count;
int DFT(int G[][n], int start, int first=0)
{
    ::visited[start] = 1;
    
    if(first == 0)
    {
        ::components[::curr_count][::count_comp[::curr_count]++] = start;
        cout<<start + 1<<" ";
        ::count[start] = -1;
    }
    
    for(int i=0; i<n; i++)
        if(G[start][i] && ::visited[i] == 0)
            DFT(G, i, first);
    if(first == 1)
        ::count[start] = ++boo_count;
    return 0;
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

    int newG[n][n] = {0};
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            {
                newG[i][j] = G[j][i];
                newG[j][i] = G[i][j];
            }

    done = 0;
    for(int i=0; i<n; i++)
        ::visited[i] = 0;
    ::curr_count = 0;
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
        cout<<::curr_count<<" : ";
        DFT(newG, ind, 0);
        cout<<endl;
        ::curr_count++;
    }
    /*
    cout<<endl;
    for(int i=0; i< ::curr_count; i++)
    {
        for(int j=0; j< ::count_comp[i]; j++)
            cout<<::components[i][j] + 1<<" ";
        cout<<endl;
    }
    */
    cout<<endl;
    int edges[n][2] = {0}, ecount = 0;
    for(int i=0; i< ::curr_count; i++)
        for(int j=0; j< ::count_comp[i]; j++)
            for(int k=0; k < ::curr_count; k++)
                for(int l=0; l< ::count_comp[k]; l++)
                    if(k != i && G[j][l] && !search(edges, ecount, i, k) && !search(edges, ecount, k, i))
                    {
                        edges[ecount++][0] = i;
                        edges[ecount][1] = k;
                    }
    for(int i=0; i<ecount; i++)
        cout<<edges[i][0]<<" - "<<edges[i][1]<<endl;
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