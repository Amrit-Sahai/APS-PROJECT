#include<bits/stdc++.h>
using namespace std;

struct node 
{ 
	node* parent;
	node* child; 
	node* left; 
	node* right;
	int key; 
	int degree;
	char mark; 
	char c;
}; 

struct node* mini = NULL; 

int no_of_nodes = 0;

struct node* newNode(int val)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node)); 
	new_node->key = val; 
	new_node->degree = 0; 
	new_node->mark = 'W'; 
	new_node->c = 'N'; 
	new_node->parent = NULL; 
	new_node->child = NULL; 
	new_node->left = new_node; 
	new_node->right = new_node; 
	return new_node;
}

void insertion(int val) 
{ 
	struct node* new_node = newNode(val);

	if (mini != NULL) 
	{ 
		(mini->left)->right = new_node; 
		new_node->right = mini; 
		new_node->left = mini->left; 
		mini->left = new_node; 
		if (new_node->key < mini->key) 
			mini = new_node; 
	} 
	else 
		mini = new_node;  
	
	no_of_nodes++; 
} 

void Fibonnaci_link(struct node* p2, struct node* p1) 
{ 
	(p2->left)->right = p2->right; 
	(p2->right)->left = p2->left; 
	if (p1->right == p1) 
		mini = p1; 
	
	p2->left = p2; 
	p2->right = p2; 
	p2->parent = p1; 
	
	if (p1->child == NULL) 
		p1->child = p2; 
	
	p2->right = p1->child; 
	p2->left = (p1->child)->left; 
	
	((p1->child)->left)->right = p2; 
	(p1->child)->left = p2; 
	
	if (p2->key < (p1->child)->key) 
		p1->child = p2; 
	
	p1->degree++; 
} 

void consolidateTheHeap() 
{ 
	int temp1; 
	float temp2 = (log(no_of_nodes)) / (log(2)); 
	int temp3 = temp2; 
	struct node* arr[temp3]; 
	
	for (int i = 0; i <= temp3; i++) 
		arr[i] = NULL; 
	
	node *p1 = mini; 
	node *p2,*p3; 
	node *ptr4 = p1; 
	
	do 
	{ 
		ptr4 = ptr4->right; 
		temp1 = p1->degree; 
		while (arr[temp1] != NULL) 
		{ 
			p2 = arr[temp1]; 
			
			if (p1->key > p2->key) 
			{ 
				p3 = p1; 
				p1 = p2; 
				p2 = p3; 
			} 
			
			if (p2 == mini) 
				mini = p1; 
			
			Fibonnaci_link(p2, p1); 
			
			if (p1->right == p1) 
				mini = p1; 
			arr[temp1] = NULL; 
			temp1++; 
		} 
		
		arr[temp1] = p1; 
		p1 = p1->right; 
	
	} while (p1 != mini); 
	
	mini = NULL; 
	
	for (int j = 0; j <= temp3; j++) 
	{ 
		if (arr[j] != NULL) 
		{ 
			arr[j]->left = arr[j]; 
			arr[j]->right = arr[j]; 
			if (mini != NULL) 
			{ 
				(mini->left)->right = arr[j]; 
				arr[j]->right = mini; 
				arr[j]->left = mini->left; 
				mini->left = arr[j]; 
				if (arr[j]->key < mini->key) 
					mini = arr[j]; 
			} 
			else 
			{ 
				mini = arr[j]; 
			} 
			if (mini == NULL) 
				mini = arr[j]; 
			else if (arr[j]->key < mini->key) 
				mini = arr[j]; 
		} 
	}

} 

void extraxtMin() 
{ 
	if (mini == NULL) 
		cout << "The heap is empty!\n"; 
	else 
	{ 
		node* temp = mini; 
		node* pntr; 
		pntr = temp; 
		node* x = NULL; 
		
		if (temp->child != NULL) 
		{ 
			x = temp->child; 
			
			do 
			{ 
				pntr = x->right; 
				(mini->left)->right = x; 
				x->right = mini; 
				x->left = mini->left; 
				mini->left = x; 
				
				if (x->key < mini->key) 
					mini = x; 
				x->parent = NULL; 
				x = pntr;

			} while (pntr != temp->child); 
		} 
		
		(temp->left)->right = temp->right; 
		(temp->right)->left = temp->left; 
		mini = temp->right; 
		
		if (temp == temp->right && temp->child == NULL) 
			mini = NULL; 
		else 
		{ 
			mini = temp->right; 
			consolidateTheHeap(); 
		} 
		
		no_of_nodes--; 
	} 
} 
void cutTheLink(struct node* found, struct node* temp) 
{ 
    if (found == found->right) 
        temp->child = NULL; 
  
    (found->left)->right = found->right; 
    (found->right)->left = found->left; 
    if (found == temp->child) 
        temp->child = found->right; 
  
    temp->degree = temp->degree - 1; 
    found->right = found; 
    found->left = found; 
    (mini->left)->right = found; 
    found->right = mini; 
    found->left = mini->left; 
    mini->left = found; 
    found->parent = NULL; 
    found->mark = 'B'; 
}
void cascadeCut(struct node* temp) 
{ 
	node* ptr5 = temp->parent; 
	if (ptr5 != NULL) 
	{ 
		if (temp->mark == 'W') 
		{ 
			temp->mark = 'B'; 
		} 
		else 
		{ 
			if (temp == temp->right) 
				ptr5->child = NULL; 

			(temp->left)->right = temp->right; 
			(temp->right)->left = temp->left; 
			
			if (temp == ptr5->child) 
				ptr5->child = temp->right; 

			ptr5->degree = ptr5->degree - 1; 
			temp->right = temp; 
			temp->left = temp; 
			(mini->left)->right = temp; 
			temp->right = mini; 
			temp->left = mini->left; 
			mini->left = temp; 
			temp->parent = NULL; 
			temp->mark = 'B';  
			cascadeCut(ptr5); 
		} 
	} 
} 

void decreaseKey(struct node* found, int val) 
{ 
	if (mini == NULL) 
		cout << "The Heap is Empty!\n"; 

	if (found == NULL) 
		cout << "Node is not found in the Heap\n"; 

	found->key = val; 

	struct node* temp = found->parent; 
	if (temp != NULL && found->key < temp->key) 
	{ 
		cutTheLink(found, temp); 
		cascadeCut(temp); 
	} 
	if (found->key < mini->key) 
		mini = found; 
} 

void find(struct node* mini, int old_val, int val) 
{ 
	struct node* found = NULL; 
	node* temp5 = mini; 
	temp5->c = 'Y'; 
	node* found_ptr = NULL; 
	
	if (temp5->key == old_val) 
	{ 
		found_ptr = temp5; 
		temp5->c = 'N'; 
		found = found_ptr; 
		decreaseKey(found, val); 
	} 
	
	if (found_ptr == NULL) 
	{ 
		if (temp5->child != NULL) 
			find(temp5->child, old_val, val); 
		
		if ((temp5->right)->c != 'Y') 
			find(temp5->right, old_val, val); 
	} 
	temp5->c = 'N'; 
	found = found_ptr; 
}

void deletion(int val) 
{ 
    if (mini == NULL) 
        cout << "The heap is empty" << endl; 
    else 
    { 
  
        find(mini, val, 0); 
  
        extraxtMin(); 
        cout << "Key is Deleted!\n"; 
    } 
}

void printHeap() 
{ 
	node* ptr = mini; 
	if (ptr == NULL) 
		cout << "The Heap is Empty!\n"; 

	else 
	{ 
		cout << "The root nodes of Heap are: \n"; 
		do 
		{ 
			cout << ptr->key; 
			ptr = ptr->right; 
			if (ptr != mini) 
			{ 
				cout << "-->"; 
			}
			// cout<<endl; 
		} while (ptr != mini && ptr->right != NULL); 
		
		cout << "\nThe no of nodes in Fibonacci Heap : " << no_of_nodes << endl; 
	} 
} 

int main() 
{ 
	cout << "Creating an initial heap" << endl; 
	
	for(int i=1 ; i<=10 ;i++)
		insertion(i); 
	
	printHeap(); 
	

	cout << "Decrease value of 8 to 5" << endl; 
	find(mini, 8, 5); 
	// printHeap(); 

	// cout << "Delete the node" << endl; 
	deletion(10); 
	deletion(2); 
	

	printHeap(); 

	cout << "Extracting min" << endl; 
	extraxtMin(); 
	printHeap(); 

	return 0; 
} 
