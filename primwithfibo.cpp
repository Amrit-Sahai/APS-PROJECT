#include<math.h>
#include<bits/stdc++.h>
#include <time.h>
# define INF 10000000
# define buff 255
using namespace std;
typedef pair<int, int> pair1;
int value1=0;
int num=1000;
class node
{
			public:
		    int degree;
			char C;
			int n;
	        int id;
			char check1;
			node* parent;
			node* child;
			node* left;
			node* right;
			
};




node* nodecreate(int,int);
int fibheap_link(node*,node*,node*);
node* make_fib();
node* insertfib(node*,node*);
node* fibunion(node*,node*);
node* fib_min_extract(node*);
int consolidate(node*);
node*temp5=make_fib();
node* search_node(node*,int);
int fibdecrease_key(node*,int,int);
int fibdelete_key(node*,int);
int cut(node*,node*,node*);
int cascade_cut(node*,node*);
int givennode(node*);

class Graph
{
    int V;
    list< pair<int, int> > *adj;
 
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void primMST();
    
    
};

Graph::Graph(int n)
{
    V= n;
    adj = new list<pair1> [n];
}
 
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

 void test2()
{
	clock_t t;double time_taken;
	int V = 100;
    Graph g(V);

    g.addEdge(0,1,-1);
 
	std::fstream myfile("test2.txt", std::ios_base::in);
    
    int a,b,c;
    while (myfile >> a)
    {
		myfile >> b;
		myfile >> c;
		
		g.addEdge(a,b,c);
        
    } 
     t = clock();
     g.primMST();
     t = clock() ;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout<<"TimeTaken"<<" "<<time_taken<<endl;
	}

void checkfile(string arr)
{
	ifstream fin;
	fin.open(arr);
	int arr1[buff];
	int i,c=0;
	for(i=0;i<num;i++)
	{
		c=0;
		ofstream fout;
	    fout.open(to_string(i));
		int temp=buff;
		while(temp--)
		{
			int a;
			fin>>arr1[c];
			c++;
			
		}
		
		sort(arr1,arr1+c);
		int k=0;;
		 while(k<c)
		 {
			fout<<arr1[k]<<"\n";
			k++;
		 }
		 fout.close();
	
	}	
		
		
	
}
 void Graph::primMST()
{
 
  
	vector<bool> currmst(V, false);
    vector<int> key(V, INF);
    vector<int> parent(V, -1);
    int src = 0;
    node* p;
   
	p=nodecreate(0,src);
	temp5=insertfib(temp5,p);
  
    
    key[src] = 0;
   
    
    node *q1=temp5;
    while(q1!=NULL)
   
    {
        
     q1=fib_min_extract(temp5);
        if(q1==NULL)break;
        int u=q1->id;
        
 
        currmst[u] = true;
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
            if (currmst[v] == false && key[v] > weight)
            {

                key[v] = weight;
               
                p=nodecreate(key[v],v);
				temp5=insertfib(temp5,p);
                
                
                
                parent[v] = u;
            }
        }
    }
 
    for (int i = 1; i < V; ++i)
	{
        
		cout<<parent[i]<<"- "<<i<<endl;
	}
}
node* make_fib()
  {
    node* np;
    np=NULL;
    return np;
  }
  
node* nodecreate(int k, int ide)
  {
    node* x=new node;
    x->n=k;
    x->id=ide;
    return x;
  }
  
node* insertfib(node* root,node* x)
  {
    x->degree=0;
    x->parent=NULL;
    x->child=NULL;
    x->left=x;
    x->right=x;
    x->check1='F';
    x->C='N';
    if(root!=NULL)
      {
	(root->left)->right=x;
	x->right=root;
	x->left=root->left;
	root->left=x;
	if(x->n<root->n)
	  root=x;
      }
    else
      {
	root=x;
      }
    value1=value1+1; 
    
    return root;
  }
  
int fibheap_link(node* root1,node* y,node* z)
  { 
    (y->left)->right=y->right;
    (y->right)->left=y->left;
    if(z->right==z)
      root1=z;
     y->left=y;
     y->right=y;
    y->parent=z;
    if(z->child==NULL)
      z->child=y;
    y->right=z->child;
    y->left=(z->child)->left;
    ((z->child)->left)->right=y;
    (z->child)->left=y;
    if(y->n<(z->child)->n)
      z->child=y;
    z->degree++;
    
  }

node* fibunion(node* root1,node* root2)
  {
    node* np;
    node*temp5=make_fib();
    temp5=root1;
    (temp5->left)->right=root2;
    (root2->left)->right=temp5;
    np=temp5->left;
    temp5->left=root2->left;
    root2->left=np;
    return temp5;
  }

node* fib_min_extract(node* root1)
  {
    node* p;node* ptr;
    node* z=root1;
    p=z;
    ptr=z;
    if(z==NULL)
    {
		
     return z;
	}
    node* x;
    node* np;
    x=NULL;
    if(z->child!=NULL)
	x=z->child;
    if(x!=NULL)
      {
	ptr=x;
	do
	  {
	    np=x->right;
	  (root1->left)->right=x;
	  x->right=root1;
	  x->left=root1->left;
	  root1->left=x;
	  if(x->n<root1->n)
	    root1=x;
	  x->parent=NULL;
	  x=np;
	  }while(np!=ptr);
      }  
    (z->left)->right=z->right;
    (z->right)->left=z->left;
     root1=z->right;
    if(z==z->right&&z->child==NULL)
    {
      temp5=NULL;
    }
    
    else
      {
	root1=z->right;
	consolidate(root1);
      }
    value1=value1-1;
    return p;
  }
  
int consolidate(node* root1)
  {
    int d;
    float f=(log(value1))/(log(2));
    int D=f;
    node* A[D];
    for(int i=0;i<=D;i++)
	A[i]=NULL;
    node* x=root1;
    node* y;
    node* np;
    node* pt=x;
    do
      {
	pt=pt->right;
	d=x->degree;
	while(A[d]!=NULL)
	  {
	    y=A[d];
	    if(x->n>y->n)
	      {
		np=x;
		x=y;
		y=np;
		
	      }
	    if(y==root1)
	      root1=x;
	    fibheap_link(root1,y,x);  
	    if(x->right==x)
	      root1=x;
	    A[d]=NULL;
	    d=d+1;
	      
	  }
	
	A[d]=x;
	x=x->right;
      }while(x!=root1);
    temp5=NULL;
   for(int j=0;j<=D;j++)
    {
      if(A[j]!=NULL)
	{
	  A[j]->left=A[j];
	  A[j]->right=A[j];
	  if(temp5!=NULL)
	{
	(temp5->left)->right=A[j];
	A[j]->right=temp5;
	A[j]->left=temp5->left;
	temp5->left=A[j];
	if(A[j]->n<temp5->n)
	  temp5=A[j];
	}
    else
	{
	temp5=A[j];
	}
	  if(temp5==NULL)
	    temp5=A[j];
	  else if(A[j]->n<temp5->n)
	    temp5=A[j];
	}
    }
  }
  
  
int fibdecrease_key(node*root1,int x,int k)
  {
    node* y;
    if(root1==NULL)
      {
	cout<<"\n no node";
	return 0;
      }
    node* ptr=search_node(root1,x);
    if(ptr==NULL)
      {
	cout<<"\nNode not Found";
	return 1;
      }
    if(ptr->n<k)
      {
	cout<<"\nGiven key is greater than value";
	return 0;
      }
    ptr->n=k;
    y=ptr->parent;
    if(y!=NULL&&ptr->n<y->n)
      {
	cut(root1,ptr,y);
	cascade_cut(root1,y);
      }
   if(ptr->n<temp5->n)
     temp5=ptr;
   return 0;
  }
  
int cut(node* root1,node* x,node* y)
  {
    if(x==x->right)
      y->child=NULL;
    (x->left)->right=x->right;
    (x->right)->left=x->left;
    if(x==y->child)
      y->child=x->right;
    y->degree=y->degree-1;
    x->right=x;
    x->left=x;
    (root1->left)->right=x;
    x->right=root1;
    x->left=root1->left;
    root1->left=x;
    x->parent=NULL;
    x->check1='F';
  }
  
node* search_node(node* H,int k)
{
    node* x=H;
    x->C='Y';
    node* p=NULL;
    if(x->n==k)
      {
	p=x;
	x->C='N';
	return p;
      }
    if(x->child!=NULL&&p==NULL)
      {
      p=search_node(x->child,k);
      }
    if((x->right)->C!='Y'&&p==NULL)
      {
      p=search_node(x->right,k);
      }
    x->C='N';  
    return p; 
 }
int cascade_cut(node* root1,node* y)
  {
    node* z=y->parent;
    if(z!=NULL)
      {
	if(y->check1=='F')
	    {
	      y->check1='T';
	    }
	else
	  {
	    cut(root1,y,z);
	    cascade_cut(root1,z);
	  }
	      
      }
  }
  
  
void test1()
{
	clock_t t;double time_taken;
	//cout<<"hello";
	int V = 9;
    Graph g(V);
	
    g.addEdge(0,1,-1);
   
	fstream myfile("test1.txt", ios_base::in);
    
    int a,b,c;
    while (myfile >> a)
    {
		//cout<<"hii";
		myfile >> b;
		myfile >> c;
		
		g.addEdge(a,b,c);
        
    } 
	  
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout<<"TimeTaken"<<" "<<time_taken<<endl;
}
	

 int main()
{
	int t;
	cout<<"\n press 1 for input = 10 or press 2 for input = 1000\n";
	cin>>t;
	if(t==1)
      test1();
    else if(t==2)
	   test2();
    else
		cout<<"ERROR";
	return 0;
}
