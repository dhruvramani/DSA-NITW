#include <iostream>
using namespace std;

#define size 4
void init_array(int a[])
{
	for(int i=0; i<size; i++)
		a[i] = -1;
}

int* vertices(int a[][size])
{
	int max_count=1;
	static int max_length[size];
	init_array(max_length);
	for(int i=0; i<size; i++)
	{
		int list[size], fully_connected[size], count=0, count2=1;
		init_array(list); 	init_array(fully_connected);
		fully_connected[0]=i;
		for(int j=0; j<size; j++)
			if(a[i][j] == 1)
				list[count++] = j;

		for(int k=0; k<count; k++)
			for(int j=0; j<size; j++)
				if(a[list[k]][j] == 1 && a[i][j] == 1 && j != i)
						fully_connected[count2++] = list[k];

		if(count2 > max_count)
		{
			max_count = count2;
			for(int k=0, j=0; k<size; k++)
				if(fully_connected[k] != -1)
					max_length[j++] = fully_connected[k];
		}
	}
	return max_length;
}

int main()
{
	int matrix[][size] ={{0, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 0}, {1, 1, 0, 0}}; 
	int *connected = vertices(matrix);
	for(int j=0; j < size; j++)
		if(connected[j] != -1)
			cout<<char('a' + connected[j])<<",";
	return 0;
}
