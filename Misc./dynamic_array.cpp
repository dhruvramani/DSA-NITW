#include <iostream>
using namespace std;

struct s1 
{
	int a;
	char f;	
};
struct s
{
	struct s *a;
	int b;
	struct s **c;
	struct s1 *d[10];	
};

int main()
{
	struct s var;
	int n;
	cout<<"Enter Size : ";
	cin>>n;
	var.c = new s*[n];
	for(int i=0; i<n; i++)
	{
		var.c[i] = new s[n];
		var.c[i]->b=n + i;
		cout<<"C["<<i<<"].b = "<<var.c[i]->b<<endl;
	}
	var.d[0]->a = n;
	cout<<endl<<"D[0]->a = "<<var.d[0]->a<<endl;
	return 0;
}
