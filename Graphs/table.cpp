#include <iostream>
using namespace std;

# define n 12

void insert(int G[][n], int row, int column, int weight=1)
{ G[row-1][column-1] = weight; }

int table[n] = {0}, table_size = 0;
int table_visited[n] = {0};

int add_table(int G[][n], int index= -1)
{
    int done = 0;
    for(int j=0; j<n-1 && done == 0; j++)
    {
        int count = 0;
        for(int k=0; k<n; k++)
            if(k != j)
                count += G[k][j];
        if(count == 0 && ::table_visited[j] == 0)
        {
            table_visited[j] = 1;
            if(index == -1)
                ::table[::table_size++] = j;
            else
            {
                done = 1;
                ::table[index] = j;
            }
        }
    }
    return done;
}

int modify_table(int G[][n])
{
    int table_count = 0;
    for(int i=0; i< ::table_size; i++)
        if(::table[i] != -1 && ::table_visited[::table[i]] == 1)
        {
            int done = add_table(G, i);
            if(done == 0)
                ::table[i] = -1;
            break;
        }

    for(int i=0; i< ::table_size; i++)
        if(::table[i] != -1)
        {
            table_count ++;
            cout<<::table[i]<<" ";
        }
    cout<<endl;
    return table_count;
}

void run(int G[][n])
{
    int table_count = 1;
    add_table(G);
    /*for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<G[i][j];
        cout<<endl;
    }*/

    while(table_count > 0)
    {
        int first = 0;
        for(int i=0; i< ::table_size; i++)
            if(::table[i] != -1)
            {
                first = ::table[i];
                break;
            }
        ::table_visited[first] = 1;
        for(int i=0; i<n; i++)
            G[first][i] = 0;
        table_count = modify_table(G);
    }  
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
    run(G);
    return 0;
}