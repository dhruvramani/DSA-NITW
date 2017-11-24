#include<iostream>
using namespace std;
const int d=1;

struct bdnode
{
	
	int data[2*d+1];
	bdnode* ptr[2*d+2];
	int c;
	bdnode()
	{
		c=0;
		for(int i=0;i<2*d+2;i++)
		ptr[i]=NULL;
	}
};

class Queue
{
	public:
	Queue(){
		front=-1;
		rear=-1;
		size=200;
	}
	private:
		int front;
		int rear;
		int size;
		bdnode* element[200];
		
	public:
		int isfull();
		int isempty();
		void enqueue(bdnode* k);
		bdnode* dequeue();
};
int Queue::isfull()
{
	if((rear+1)%size==front)
	 return 1;
	else
	 return 0;
}

int Queue::isempty()
{
	if(front==-1)
	 return 1;
	else
	 return 0;
}

void Queue::enqueue(bdnode* k)
{
	if(isfull())
	  cout<<"Queue is full\n";
	else if(front==-1)
	{
		front=0;
		rear=0;
	}
	else
	{
		rear=(rear+1)%size;
	}
	element[rear]=k;
}

bdnode* Queue::dequeue()
{
	bdnode* t;
	if(isempty())
	  return NULL;
	else
	{
		if(front==rear)
		{
		  t=element[front];
		  front=-1;
		  rear=-1;	
		}
		else
		{
			t=element[front];
			front=(front+1)%size;
		}
		return t;
	}
}

void Level_order(bdnode *B)
{
	if(B==NULL)
	{
		cout<<"TREE IS EMPTY\n";
		return;
	}
	Queue Q;
	bdnode *T,*T1;
	T1=new bdnode;
	T1->data[0]=-1;
	Q.enqueue(B);
	Q.enqueue(T1);
	
	while(!Q.isempty())
	{
		T=Q.dequeue();
		if(T->data[0]==-1)
		{
			cout<<endl;
			if(!Q.isempty())
			Q.enqueue(T1);
		}
		else
		{
			int i;
			for(i=0;i<T->c;i++)
			cout<<T->data[i]<<" ";
			for(i;i<2*d;i++)
			cout<<"_ ";
			cout<<"  ";
			for(i=0;i<=T->c;i++)
			{
			   if(T->ptr[i]!=NULL)
			   Q.enqueue(T->ptr[i]);
			}
		}
	}
}

void Sort(int a[],int size)
{
	int i=0,j=0,temp;
	for(i=0;i<size;i++)
	{
		for(j=0;j<(size-1);j++)
		{
		   if(a[j]>a[j+1])
		   {
			  temp=a[j];
			  a[j]=a[j+1];
			  a[j+1]=temp;
		   }
		}
	}
}

void Insert_and_Sort(bdnode *B,int k)
{
	int i,j;
	B->data[B->c++]=k;
	int t,size=B->c;
	bdnode* tptr;
	for(i=0;i<size;i++)
	{
		for(j=0;j<(size-1);j++)
		{
			if(B->data[j]>B->data[j+1])
			{
				t=B->data[j];
				B->data[j]=B->data[j+1];
				B->data[j+1]=t;
				tptr=B->ptr[j+1];
				B->ptr[j+1]=B->ptr[j+2];
				B->ptr[j+2]=tptr;
			}
		}
	}
}

int check_leafnode(bdnode *B)
{
	if(B->ptr[0]==NULL)
	return 1;
	else
	return 0;
}

void Right_to_left_rotation(bdnode *B,int index)
{
	bdnode *right_node=B->ptr[index+1];
	bdnode *left_subtree=right_node->ptr[0];
	bdnode *left_node=B->ptr[index];
	
	left_node->data[left_node->c++]=B->data[index];   //one element added in left_node
	left_node->ptr[left_node->c]=left_subtree;
	B->data[index]=right_node->data[0];
	
	int i;          //shifting data to left in right_node by 1 place
	for(i=0;i<(right_node->c-1);i++)
	{
		right_node->ptr[i]=right_node->ptr[i+1];
		right_node->data[i]=right_node->data[i+1];
	}
	right_node->ptr[i]=right_node->ptr[i+1];
	right_node->c--;    //one element is removed in right_node
}

void Left_to_right_rotation(bdnode *B,int index)
{
	bdnode *left_node=B->ptr[index];
	bdnode *right_subtree=left_node->ptr[left_node->c];
	bdnode *right_node=B->ptr[index+1];
	
	int i;    //shifting data and pointers to right by 1 place
	for(i=right_node->c;i>=1;i--)
	{
		right_node->ptr[i+1]=right_node->ptr[i];
		right_node->data[i]=right_node->data[i-1];
	}
	right_node->ptr[1]=right_node->ptr[0];
	right_node->c++;      //one element incresed in right_node
	
	right_node->data[0]=B->data[index];
	right_node->ptr[0]=right_subtree;
	B->data[index]=left_node->data[left_node->c-1];
	left_node->c--;     //one element decresed in left node
}

void Node_splite(bdnode *T,bdnode* &N,int &median)
{
	int i;
	median=T->data[d];
	for(i=d+1;i<2*d+1;i++)    //copying data and pointers into new node
	{
		N->ptr[N->c]=T->ptr[i];
		N->data[N->c++]=T->data[i];
	}
	N->ptr[N->c]=T->ptr[i];
	T->c=d;    //Now no of element are d
}

void Overflow(bdnode *B,int added_into)
{
	/*checking for key redistrubution*/
	int success=0;
	if(added_into==0)
	{
		if(B->ptr[1]->c<2*d)
		{
			Left_to_right_rotation(B,added_into);  //rotation takes place about added_into indexed data
			success=1;
		}
	}
	else if(added_into==B->c)
	{
		if(B->ptr[B->c-1]->c<2*d)
		{
			Right_to_left_rotation(B,added_into-1); //rotation takes place about (added_into-1) indexed data
			success=1;
		}
	}
	else if(B->c>added_into && B->ptr[added_into+1]->c<2*d)
	{
		Left_to_right_rotation(B,added_into);
		success=1;
	}
	else if(B->ptr[added_into-1]->c<2*d)
	{
		Right_to_left_rotation(B,added_into-1);
		success=1;
	}
	if(success==0)       //if key redis. not possible then node spliting
	{
		bdnode *T=B->ptr[added_into];
		bdnode *N=new bdnode;
		int median;
		Node_splite(T,N,median);  //splting node N is new node median is separator
		B->ptr[B->c+1]=N;
		Insert_and_Sort(B,median);
	}
}
void Add(bdnode* &B,int k)
{
	int i;
	if(B==NULL)
	{
		B=new bdnode;
		B->data[B->c++]=k;
		return;
	}
	if(check_leafnode(B))
	{
		B->data[B->c++]=k;  //Simply insert and sort into leafnode
		Sort(B->data,B->c);
	}
	else
	{	
		int added_into=0;
		for(i=0;i<B->c;i++)
		{
			if(k<B->data[i])
			{
			    added_into=i;
				Add(B->ptr[i],k);
				break;
			}
		}
		if(i==B->c)
		{
			added_into=B->c;
			Add(B->ptr[B->c],k);
		}
		if(B->ptr[added_into]->c>2*d)   //checking for Overflow
		{
			Overflow(B,added_into);
		}
	}
}
int Find_index(bdnode *B,int k)
{
	int i;
	for(i=0;i<B->c;i++)
	{
		if(B->data[i]==k)
		break;
	}
	if(i==B->c)
	return -1;
	else
	return i;
}
int Preceder(bdnode *B)
{
	if(check_leafnode(B))
	return B->data[B->c-1];
	else
	return Preceder(B->ptr[B->c]);
}
void Merge_Nodes(bdnode *B,int index)
{
	int median=B->data[index];
	bdnode *left_node=B->ptr[index];
	bdnode *right_node=B->ptr[index+1];
	
	left_node->data[left_node->c++]=median;
	left_node->ptr[left_node->c]=right_node->ptr[0];
	
	for(int i=0;i<right_node->c;i++)   //copying data and pointer into left_node
	{
		left_node->data[left_node->c++]=right_node->data[i];
		left_node->ptr[left_node->c]=right_node->ptr[i+1];
	}
	right_node->c=0;                   //right_node is now empty;
	B->ptr[index+1]=NULL;
	delete right_node;
}
void Underflow(bdnode *B,int remove_into)
{
	/*checking for key redistrubution*/
	int success=0;  //it denode success in Key_redisbution
	if(remove_into==0)
	{
		if(B->ptr[1]->c>d)
		{
			Right_to_left_rotation(B,0);
			success=1;
		}
	}
	else if(remove_into==B->c)
	{
		if(B->ptr[remove_into-1]->c>d)
		{
			Left_to_right_rotation(B,remove_into-1);
			success=1;
		}
	}
	else if(B->ptr[remove_into+1]->c>d)
	{
		Right_to_left_rotation(B,remove_into);
		success=1;
	}
	else if(B->ptr[remove_into-1]->c>d)
	{
		Left_to_right_rotation(B,remove_into);
		success=1;
	}
	/*If success==0 then we have to merge nodes*/
	if(success==0)
	{
		int i;
		int index;
		if(remove_into==B->c)
		{
			index=remove_into-1;
			Merge_Nodes(B,index); //Merge about data of index=(remove_into-1)
		}
		else
		{
			index=remove_into;
			Merge_Nodes(B,index); //Merge about data of index=(remove_into)
		}
		for(i=index;i<(B->c-1);i++)   //shifting data and pointers to right
		{
			B->data[i]=B->data[i+1];
			B->ptr[i+1]=B->ptr[i+2];
		}
		B->c--;   //one element is decreased in parent
	}
}
void del(bdnode *&B,int k)
{
	int i,found;
	found=Find_index(B,k);
	if(check_leafnode(B))
	{
		if(found==-1)
		{
			cout<<"KEY NOT PRESENT\n";
		}
		else
		{
			for(i=found+1;i<B->c;i++)
			B->data[i-1]=B->data[i];
			B->c--;           //element is deleted
		}
		return;  //if leafnode terminate here
	}
	if(found!=-1)  //Key found is in internal node
	{
		int pre=Preceder(B->ptr[found]);  //copy preceder to data and delete it
		B->data[found]=pre;
		del(B->ptr[found],pre);
		int remove_into=found;
		if(B->ptr[remove_into]->c<d)  //check for underflow in subtree in which preceder is removed
		{
			Underflow(B,remove_into);
		}
	}
	else
	{
		int remove_into;
		for(i=0;i<B->c;i++)
		{
			if(k<B->data[i])
			break;
		}
		remove_into=i;    //pointer in tree deletion
		
		del(B->ptr[remove_into],k);
		
		if(B->ptr[remove_into]->c<d)   //Condition of Underflow
		{
			Underflow(B,remove_into);
		}
	}
}

int main()
{
	bdnode *B=NULL;
	int k;
	cout<<"Enter data for the tree\n";
	//for(int i=1;i<=100;i++)
	do
	{
	   cout<<"Enter -1 to stop\n";
	   cin>>k;
	   if(k==-1)
	   break;
	   Add(B,k);
	   if(B->c>2*d)
	   {
	   	  bdnode *N=new bdnode;
	   	  int median;
	   	  Node_splite(B,N,median);
	   	  bdnode *P=new bdnode;
	   	  P->ptr[0]=B;
	   	  P->data[P->c++]=median;
	   	  P->ptr[P->c]=N;
	   	  B=P;
	   }
	   Level_order(B);
	}
	while(k!=-1);
	//Level_order(B);
	cout<<"Enter the element you want to delete\n";
	do
	{
		cout<<"Enter -1 to stop\n";
		cin>>k;
		if(k==-1)
		break;
		del(B,k);
		if(B->c==0)
		{
			bdnode *temp=B;
			B=B->ptr[0];
			temp->ptr[0]=NULL;
			delete temp;
		}
		Level_order(B);
	}
	while(k!=-1);
	return 0;
}
	
