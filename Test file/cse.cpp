#include<iostream>


using namespace std;


#define ll long long int

class node{
public:
	int data;
	node* next;

	node(int d)
	{
		data =d;
		next=NULL;
	}


};


void insertathead(node*&head,int data)
{
	node* n= new node(data);
	n->next=head;
	head=n;
}


void insertattail(node*&head,int data)
{
	if(head==NULL)
	{
		head=new node(data);
		return;
	}
	node*tail=head;
	while(tail->next !=NULL)
	{
		tail=tail->next;
	}
	tail->next =new node(data);
	return;
}



//For finding length
int len(node*head)
{
	int l=0;
	while(head!=NULL)
	{
		head=head->next;
		l++;
	}
	return l;
}



void insertatmiddle(node*&head,int data,int p)
{
	if(head==NULL	||	p==0)
	{
		insertathead(head,data);
	}
	else if(p>len(head))
	{
		insertattail(head,data);
	}
	else
	{
		int jump=1;
		node* temp=head;
		while(jump<=p-1)
		{
			temp=temp->next;
			jump+=1;
		}

		node*n=new node(data);
		n->next=temp->next;
		temp->next=n;
	}
}


void deleteathead(node*&head)
{
	if(head==NULL)
	{
		return;
	}
	node* temp=head;
	head=head->next;
	delete temp;
	return;
}


void deleteattail(node*&head)
{
	node* prev=NULL;
	node* temp=head;
	while(temp->next!=NULL)
	{
		prev=temp;
		temp=temp->next;
	}
	delete temp;
	prev->next=NULL;
	return;
}

bool searchrec(node*head,int key)
{
	if(head==NULL)
	{
		return false;
	}
	if(head->data==key)
	{
		return true;
	}
	else
		return(searchrec(head->next,key));

}


void print(node*head)
{
	while(head!=NULL)
	{
		cout<<head->data<<" <- ";
		head=head->next;
	}
}

void build(node*&head, int t)
{
	while(t--)
	{
		ll data;
		cin>>data;
		insertattail(head,data);
	}
}

void reverse(node*&head)
{
	node*p=NULL;
	node*c=head;
	node*n;
	while(n!=NULL)
	{
		//Save the next node
		n=c->next;

		//Make the current node point to prev
		c->next=p;

		//Just update prev and current
		p=c;
		c=n;
	}
	head=p;
}

node* recureverse(node*&head)
{

	//Base case
	if(head->next==NULL || head==NULL)
	{
		return head;
	}
	//Recursive case
	node*smallhead=recureverse(head->next);
	node*c =head;
	c->next->next=c;
	c->next=NULL;
	return smallhead;


}

node* midpoint(node*head)
{
	if(head==NULL	||	head->next==NULL)
	{
		return head;
	}
	// Slow will start from begining while fast will start
	// from begining+1
	node* slow=head;
	node* fast=head->next;
	while(fast->next!=NULL	&&	fast!=NULL)
	{
		fast=fast->next->next;
		slow=slow->next;
	}
	return slow;
}


node* merge(node*a, node*b)
{
	if(a==NULL)
	{
		return b;
	}
	else if(b==NULL)
	{
		return a;
	} 
	node * c;
	if(a->data > b->data)
	{
		c=b;
		c->next = merge(a, b->next);
	}
	else
	{
		c=a;
		c->next = merge(a->next ,b);
	}
	return c;
}


node* merge_sort(node*head)
{
	//base case
	if(head==NULL	||		head->next==NULL)
	{
		return head;
	}
	//1. Divide from mid
	
	node*mid=midpoint(head);

	node*a=head;
	node*b=mid->next;
	mid->next=NULL;
	//2. Sort the smaller
	a=	merge_sort(a);
	b=	merge_sort(b);
	//3. Merge them
	node*c=merge(a,b);
	return c;

}


//Floyd's Cycle
bool detectcycle(node*head)
{
	node*fast=head;
	node*slow=head;

	while(fast!=NULL 	||		fast->next!=NULL)
	{
		fast=fast->next->next;
		slow=slow->next;

		if(fast==slow)
			return true;
	}
	return false;
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); 
#endif
	node*head=NULL;
	ll t,p;
	cin>>t;
	
	
	build(head,t);

	print(head);
	cout<<endl;



	cin>>p;

	node*head2=NULL;

	build(head2,p);

	head=merge_sort(head);

	print(head);



return 0;
}	