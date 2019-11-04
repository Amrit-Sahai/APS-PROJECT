#include<bits/stdc++.h>
using namespace std;
# define SIZE1 100000
class node 
{ 
    public:
	long long data; 
	node *leftchild; 
	node *nextsibling; 
}; 
node *merge(node *a, node *b) 
{ 
	
	if(a==NULL) 
	  return b; 
	if(b==NULL) 
		return a; 
	
	
	if(a->data < b->data) 
	{				 
		if(a->leftchild==NULL)
		   a->leftchild=b;
	    else
		{
			b->nextsibling=a->leftchild;
			a->leftchild=b;
		}
		return a;		 
	} 
	else 
	{ 
        if(b->leftchild==NULL)
			b->leftchild=a;
		else
		{
			a->nextsibling=b->leftchild;
			b->leftchild=a;
		}
		
		return b; 
	} 

	return NULL; 
}
node *insert(node *head, long long key) 
{ 
   node *nw=(node *)malloc(sizeof(node *));
   nw->data=key;
   nw->leftchild=NULL;
   nw->nextsibling=NULL;
	return merge(head,nw); 
} 
int getmin(node *head)
{
		return head->data;
}
node* mergeboth(node *a,node *b)
{
	node *nw=merge(a,b);
	return nw;
}
node* delete1(node *a)
{
	node *node1,*node2,*tempnode,*x,*y; 
    node *left=a->leftchild;
	if(left== NULL || left->nextsibling == NULL) 
		return a; 
	else 
	{ 
		 
		node1 =left; 
		node2= left->nextsibling; 
		tempnode = left->nextsibling->nextsibling; 

		node1->nextsibling = NULL; 
		node2->nextsibling = NULL; 
		x=merge(node1,node2);

		return merge(x,delete1(tempnode)); 
	} 
}
int main() 
{ 
     clock_t t;double time_taken;  
	node *heap1=NULL,*heap2=NULL,*nw;
    long long i=0;long long min1=100000000000000,f=0;
	for(i=0;i<100000;i++)
	{
		//cout<<"hello";
		long long t=rand();
		//cout<<t<<endl;
		if(t==1210)
			f=1;
		heap1=insert(heap1,t);
	}
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	time_taken=time_taken;
    cout<<"TimeTaken"<<" "<<time_taken<<endl;
	//cout<<f;
	//cout<<min1<<endl;
	cout<<getmin(heap1)<<endl;
	heap2=insert(heap2,6);
	heap2=insert(heap2,1);
	heap2=insert(heap2,3);
	heap2=insert(heap2,4);
	//cout<<getmin(heap2)<<endl;
	heap1=mergeboth(heap1,heap2);
	//cout<<getmin(nw)<<endl;
	for(i=0;i<1000000;i++)
		heap1=delete1(heap1);
	cout<<getmin(heap1)<<endl;
	
	//heap1.mergeboth(heap2); 
	
	return 0; 
} 