#include <iostream>
using namespace std;

# define n 6

#define size 7
int s[size];
int find_root(int i)
{
    if(::s[i] == 0)
        return i;
    return find_root(::s[i]);
}

void uni(int i, int j)
{
    if(j == 0)
        ::s[j] = i;
    else if(i == 0)
        ::s[i] = j;
    else 
        ::s[find_root(j)] = i;
}

int find(int a, int b)
{
    return find_root(a) == find_root(b);
}

void insert(int G[][n], int row, int column, int weight=1)
{ 
    G[row-1][column-1] = weight;
    G[column-1][row-1] = weight;

}

int minimum(int G[][n], int i, int &k)
{
    int min = 10000000;
    for(int j=0; j<n; j++)
        if(G[i][j] < min && G[i][j] != 0) 
        {
            min = G[i][j];
            k = j;
        }
    return min;
}

void sollins(int G[][n])
{
    int r, c, mini;
    for(r=0; r<n; r++)
    {
        mini = minimum(G, r, c);
        if(!find(r + 1, c + 1))
            uni(r + 1, c + 1);
    }

    for(int i=1; i<size; i++)
        cout<<i<<" "<<::s[i]<<endl;
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
    sollins(G);
    return 0;   
}