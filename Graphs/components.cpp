#include <iostream>
using namespace std;

# define n 7

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;

}

int index(int a[], int m, int l)
{
    for(int i=0; i<m; i++)
        if(a[i] == l)
            return i;
    return -1;
}

int visited[n] = {0}, num[n], parent[n], low[n], stack[n] = {0}, art_boys[n] = {0}, art_count = 0, stack_count = 0, count=0;
void init()
{
    for(int i=0; i<n; i++)   
    {
        ::visited[i] = 0;
        ::num[i] = 1000000;
        ::parent[i] = -1;
        ::low[i] = 1000000;
    }
    ::count = 0;
}

int mini(int G[][n], int v)
{
    int min = ::num[v], min_back = 1000, min_low = 1000;
    for(int i=0; i<n; i++)
        if(v != i && G[v][i])
        {
            if(::parent[i] == v && ::low[i] < min_low)
                min_low = ::low[i];
            else if(i != ::parent[v] && ::num[i] < min_back)
                min_back = ::num[i];
        }
    if(min <= min_back && min <= min_low)
        return min;
    else if(min_back <= min && min_back <= min_low)
        return min_back;
    else if(min_low <= min && min_low <= min_back)
        return min_low;
}

void articulation(int G[][n], int v)
{
    ::visited[v] = 1;
    ::num[v] = ::count++;
    ::stack[::stack_count++] = v;
    for(int i=0; i<n; i++)
        if(v != i && G[v][i] && ::visited[i] == 0)
        {
            ::parent[i] = v;
            articulation(G, i);
        }
    ::low[v] = mini(G, v);
    for(int i=0; i<n; i++)
        if(v != i && G[v][i] && ::parent[i] == v)
            if((::parent[v] == -1 && low[i] > num[v]) || (::parent[v] != -1 && low[i] >= num[v]))
            {
                ::art_boys[::art_count++] = v;
                ::stack_count--;
                while(::stack_count >= 0 && index(art_boys, art_count, ::stack[::stack_count]) == -1)
                    cout<<::stack[::stack_count--] + 1<<" ";
                cout<<::stack[::stack_count] + 1;
                cout<<endl;
                break;
            }
    if(::parent[v] == -1)
    {
        while(::stack_count >= 0) //&& ::stack[::stack_count] != v)
            cout<<::stack[::stack_count--] + 1<<" ";
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
    insert(G, 3, 4);
    insert(G, 4, 5);
    insert(G, 4, 6);
    insert(G, 5, 6);
    insert(G, 3, 7);
    init();
    articulation(G, 0);
    return 0;
}