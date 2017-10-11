#include <iostream>
using namespace std;

# define n 12

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;

}

int index(int a[], int m, int b)
{
    for(int i=0; i<m; i++)
        if(a[i] == b)
            return i;
    return -1;
}

int max(int a[], int m)
{
    int max = -1;
    for(int i=0; i<m; i++)
        if(max < a[i])
            max = a[i];
    return max;
}

int degree(int G[][n], int a)
{
    int deg = 0;
    for(int i=0; i<n; i++)
        if(G[a][i] == 1)
            deg++;
    return deg;
}

void splice(int main_visited[], int visited[], int visit, int &main_visit, int index)
{
    if(main_visit == 0)
        for(int i=0; i<visit; i++)
            main_visited[main_visit++] = visited[i];
    else {
        int *to_add = new int[main_visit], to_count = 0, j;
        for(int i=index+1; i<main_visit; i++)
            to_add[to_count++] = main_visited[i];
        for(j=0; j<visit; j++)
            main_visited[index + j] = visited[j];
        for(int i=0; i<to_count; i++)
            main_visited[index + j + i] =  to_add[i];
        main_visit += visit;
    }
}

int visited[n] = {0}, visit = 0;
void DFT(int G[][n], int start)
{
    int br = 1;
    if(start == ::visited[0])
    {
        ::visited[::visit++] = start;
        return ;
    }
    for(int i=0; i<n && br == 1; i++)
        if(start != i && G[start][i]) //  && index(visited, visit, i) == -1
            br = 0;
    if(br == 1)
    {
        ::visited[::visit++] = start;
        return;
    }
    ::visited[::visit++] = start;    
    //cout<<start<<" "<<::visited[::visit]<<" "<<::visit<<endl;
    for(int i=0; i<n; i++)
        if(G[start][i] && i != start) //  && index(visited, visit, i) == -1
        {
            G[start][i] = 0;
            G[i][start] = 0;
            DFT(G, i);
        }
}

int euler_path(int G[][n])
{
    int main_visited[2 * n] = {0}, main_visit = 0, done = 0, currnode = 0;
    while(done == 0)
    {
        int zeros = -1;
        ::visit = 0;
        int deg[2*n], deg_size = 0;
        
        DFT(G, currnode);
        for(int i=0; i< ::visit; i++)
            cout<<::visited[i]<<" ";
        cout<<endl;
        cout<<::visited[0]<<" : "<<::visited[::visit-1];
        for(int i=0; i<main_visit; i++)
            deg[i] = degree(G, main_visited[i]);
        
        zeros = max(deg, main_visit);
        if(zeros == 0)
            done = 1;
        else {
            int pos = index(deg, main_visit, zeros);
            splice(main_visited, ::visited, ::visit, main_visit, main_visited[pos]);
            currnode = main_visited[pos];
        }
    }
    return done;
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
    cout<<euler_path(G);
}