#include <iostream>
using namespace std;

# define n 7

struct fields
{
    int visited, cost, previous;
};

struct foo 
{
    int cost, index;
};

void init(fields filed[n])
{
    for(int i=0; i<n; i++)
    {
        filed[i].visited = 0;
        filed[i].cost = 100000;
        filed[i].previous = -1;
    }
}

void heap_insert(foo heap[], int &size, foo k)
{
    heap[size++] = k;
    int pos = size-1;
    while(heap[pos/2].cost > k.cost)
    {
        foo l = heap[pos/2];
        heap[pos/2] = heap[pos];
        heap[pos] = l;
        pos /= 2;
    }
}

foo heap_delete(foo heap[], int &size)
{
    foo l = heap[0], k = heap[size-1];
    int pos = 0;
    heap[0] = heap[--size];
    while(heap[2*pos + 1].cost < k.cost || heap[2*pos+2].cost < k.cost)
    {
        int index;
        if(heap[2*pos + 1].cost < k.cost)
            index = 2*pos+1;
        else
            index = 2*pos+2;
        foo m = heap[pos];
        heap[pos] = heap[index];
        heap[index] = heap[pos];
        pos = index;
    }
    return l;
}

void shortest_path(int G[][n], int source, int des)
{   
    fields filed[n];
    init(filed);
    int finished = 0, current = source;
    filed[source].cost = 0;
    while(finished == 0)
    {
        for(int i=0; i<n; i++)
        {
            if(G[current][i] != 0 && filed[i].visited == 0)
                if(filed[i].previous == -1 || (filed[i].previous != -1 && filed[i].cost > filed[current].cost + G[current][i])) {
                    filed[i].cost = filed[current].cost + G[current][i];
                    filed[i].previous = current;
                }
        }
        
        filed[current].visited = 1;
        // Change this part
        foo heap[n+1];
        int size = 0; 
        for(int i=0; i<n; i++)
            if(filed[i].visited == 0 && filed[i].cost < 10000)
            {
                foo for_heap = {filed[i].cost, i};
                heap_insert(heap, size, for_heap);
            }

        foo min = heap_delete(heap, size);    
        int ind = min.index;
        cout<<ind<<endl;
        int ones = 0;
        for(int i=0; i<n; i++)
            if(filed[i].visited == 1)
                ones ++;
        if(ones == n)
            finished = 1;
        else 
            current = ind;
    }
    current = des;
    cout<<"Path : ";
    while(current != -1)
    {
        cout<<current + 1<<" ";
        current = filed[current].previous;
    }
}

int main()
{
    int G[n][n] = {{0, 2, 0, 1, 0, 0, 0}, {0, 0, 0, 4, 10, 0, 0}, {4, 0, 0, 0, 0, 5, 0}, {0, 0, 2, 0, 2, 8, 4}, {0, 0, 0, 0, 0, 0, 6}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0}}, s, d;
    cout<<"Enter Source & Destination : ";
    cin>>s>>d;
    shortest_path(G, s - 1, d - 1);
    return 0;
}