#include<bits/stdc++.h> 
#include<time.h>
using namespace std; 
  
class Node 
{ 
	public:
    long long data, degree; 
    Node *child;
    Node *sibling;
    Node *parent; 
}; 
Node* getMin(list<Node*> h) 
{ 
    list<Node*>::iterator it = h.begin(); 
    Node *temp = *it; 
    while (it != h.end()) 
    { 
        if ((*it)->data < temp->data) 
            temp = *it; 
        it++; 
    } 
    return temp; 
} 
Node* mergeTrees(Node *b1,Node *b2) 
{ 
    if (b1->data > b2->data) 
        swap(b1, b2); 
 
    b2->parent = b1; 
    b2->sibling = b1->child; 
    b1->child = b2; 
    b1->degree++; 
  
    return b1; 
} 
list<Node*> unionb(list<Node*> node1,list<Node*> node2) 
{ 
   
    list<Node*>::iterator a1 = node1.begin(); 
    list<Node*>::iterator b1 = node2.begin(); 
	 list<Node*> n; 
    while (a1!=node1.end() && b1!=node2.end()) 
    { 

        if((*a1)->degree <= (*b1)->degree) 
        { 
            n.push_back(*a1); 
            a1++; 
        } 

        else
        { 
            n.push_back(*b1); 
            b1++; 
        } 
    } 
  
    while (a1!=node1.end()) 
    { 
        n.push_back(*a1); 
        a1++; 
    } 

    while (b1!=node2.end()) 
    { 
        n.push_back(*b1); 
        b1++; 
    } 
    return n; 
} 
list<Node*> rebuild(list<Node*> root) 
{ 
    if (root.size() <= 1) 
        return root; 
    list<Node*> new_heap; 
    list<Node*>::iterator a,b,c; 
    a = b = c = root.begin(); 
  
    if (root.size() == 2) 
    { 
        b = a; 
        b++; 
        c = root.end(); 
    } 
    else
    { 
        b++; 
        c=b; 
        c++; 
    } 
    while (a !=root.end()) 
    { 
       
        if (b == root.end()) 
            a++; 
  
        
        else if ((*a)->degree < (*b)->degree) 
        { 
            a++; 
            b++; 
            if(c!=root.end()) 
                c++; 
        } 
  
       
        else if (c!=root.end() && (*a)->degree == (*b)->degree && (*a)->degree == (*c)->degree) 
        { 
            a++; 
            b++; 
            c++; 
        } 
  
        else if ((*a)->degree == (*b)->degree) 
        { 
            Node *temp; 
            *a = mergeTrees(*a,*b); 
            b = root.erase(b); 
            if(c != root.end()) 
                c++; 
        } 
    } 
    return root; 
} 
  
list<Node*> removemin(Node *root) 
{ 
    list<Node*> heap; 
    Node *temp=root->child; 
    Node *lft; 
  
   
    while (temp) 
    { 
        lft= temp; 
        temp = temp->sibling; 
        lft->sibling = NULL; 
        heap.push_front(lft); 
    } 
    return heap; 
} 
list<Node*> extractMin(list<Node*> root1) 
{ 
    list<Node*> new_heap,lnew; 
    Node *temp; 
  
   
    temp = getMin(root1); 
    list<Node*>::iterator a; 
    a= root1.begin(); 
    while (a != root1.end()) 
    { 
        if (*a != temp) 
        { 
            
            new_heap.push_back(*a); 
        } 
        a++; 
    } 
    lnew=removemin(temp); 
    new_heap = unionb(new_heap,lnew); 
    new_heap =rebuild(new_heap); 
    return new_heap; 
} 
list<Node*> insert1(list<Node*>h,long long key) 
{ 
    Node *tnew= new Node; 
    tnew->data = key; 
    tnew->degree = 0; 
    tnew->child = tnew->parent = tnew->sibling = NULL; 
    list<Node*> temp; 
    temp.push_back(tnew); 
    h = unionb(h,temp); 
    
    if (h.size() <= 1) 
        return h; 
    list<Node*> new_heap; 
    list<Node*>::iterator a,b,c; 
    a =h.begin();
    b =h.begin();
    c =h.begin();
    if (h.size() == 2) 
    { 
        b = a; 
        b++; 
        c = h.end(); 
    } 
    else
    { 
        b++; 
        c=b; 
        c++; 
    } 
    while (a != h.end()) 
    { 
       
        if (b == h.end()) 
            a++; 
  
        else if ((*a)->degree < (*b)->degree) 
        { 
            a++; 
            b++; 
            if(c!=h.end()) 
                c++; 
        } 
  
        else if( c!=h.end()&&(*a)->degree==(*b)->degree&&(*a)->degree==(*c)->degree ) 
        { 
            a++; 
            b++; 
            c++; 
        } 

        else if ( (*a)->degree == (*b)->degree ) 
        { 
            Node *temp; 
            *a = mergeTrees(*a,*b); 
            b = h.erase(b); 
            if(c != h.end()) 
                c++; 
        } 
    } 
    return h; 
}

void displayTree(Node *h) 
{ 
    while (h) 
    { 
        cout << h->data << " "; 
        displayTree(h->child); 
        h = h->sibling; 
    } 
} 
void displayHeap(list<Node*> h) 
{ 
    
    list<Node*> ::iterator a; 
    a=h.begin(); 
    while (a!= h.end()) 
    { 

        
        Node* head=*a;
        while (head) 
        { 
            cout <<head->data<<" " ;
            
            displayTree(head->child); 
            head = head->sibling; 
        } 

        cout<<endl;
        a++; 
    } 
} 
int main()
{
    long long keys;
    list<Node*> bh; 
   
     
    clock_t t;double time_taken;
 
	long long i=1000000;
    long long k=0;
	t = clock();
	for(k=0;k<i;k++)
	{
		//cout<<"HELLO\n";
		//long long keys=rand();
		keys=i;
		bh=insert1(bh,keys);
	}
	time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout<<"TimeTaken"<<" "<<time_taken<<endl;
	/*cout << "\nBinomial Heap after insertion:\n"; 
    displayHeap(bh); 
	Node *temp = getMin(bh); 
    cout << "\nMinimum element in Binomial Heap : "<< temp->data << "\n"; 
		 bh=extractMin(bh); 
    cout << "Heap after deletion of minimum element\n"; 
    displayHeap(bh);*/ 
	return 0;
}