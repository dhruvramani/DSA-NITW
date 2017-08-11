#include <iostream>
using namespace std;

struct s1 
{
	int r;
	char t;
};

union u1
{
	int p;
	int q;
};

struct s2 
{
	struct s2 *k;
	union u1 l;
	int tag;
	struct s1 m;
};

struct s3
{
	int h, i;
};
union u2 
{
	struct s3;
	char j[10];
};
struct s4
{
	struct s4 *e;
	union u2 f;
	int tag;
	struct s2* g;	
};

struct main_struct
{
	int a;
	char b;
	struct s4* c;
	struct main_struct *d;	
};

int main()
{
	struct main_struct a;
	a.c = new(s4);
	a.c->g = new(s2);
	a.c->g->m.r = 5;
	cout<<"R = "<<a.c->g->m.r<<endl;
	a.c->g->tag = 1;
	a.c->g->l.q = 2;
	cout<<"Q = "<<a.c->g->l.q;
	return 0;
}
