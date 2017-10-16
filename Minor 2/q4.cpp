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

void krushkal_secondmin(int G[][n])
{
    int done = 0, r, c, mini;
    while(done == 0)
    {
        mini = minimum(G, r, c);
        if(!find(r + 1, c + 1))
            uni(r + 1, c + 1);
        G[r][c] = 0;
        G[c][r] = 0;
        done = 1;
        for(int i=0; i<n && done == 1; i++)
            for(int j=0; j<n; j++)
                if(G[i][j])
                    done = 0;
    }
    cout<<"First MST\n";
    for(int i=1; i<size; i++)
        cout<<i<<" - "<<s[i]<<endl;
    mini = minimum(G, r, c); 
    if(r > c)
    {
        int k = c;
        c = r;
        r = k;
    }
    for(int i=1; i<size; i++)
        if(i != r && s[r] == s[i])
        {
            s[i] = c;
            s[c] = r;
        }
    cout<<"Second MST\n";
    for(int i=1; i<size; i++)
        cout<<i<<" - "<<s[i]<<endl;
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
    krushkal_secondmin(G);
    return 0;   
}