/*============================================================================================
SUBMITTED BY: SWAPNIL SAXENA
ROLL NUMBER: 17103258
BATCH B6
==============================================================================================*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#define AND &&
#define OR ||
#define NOT !
#define MAX 1000

using namespace std;
int n, d; // number of days and nodes
int *dict; // int pointer for node gifts

struct vertex
{
	int id;
	int nbr_val;
	int parent;
	vertex *nbrs[MAX];
	struct vertex *next;
};

class Stack
{
	private:
		int top;
		int arr[MAX];
	public:
		int len(){ return(top+1); }
		int get(int a){ return(arr[a]); }
		void push(int a){top++; arr[top]=a;}
		void show(){for(int i=0; i<(top+1);i++){printf("->%d",arr[i]);}}
		int pop(){arr[top]=0; top--; return(arr[top+1]);}
		int srch(int a){for(int i=0; i<(top+1);i++){if(arr[i] == a){return 1;}}return 0;}
		void reset(){top = (-1);}
		Stack(){top = (-1) ;}
		Stack(Stack &ptr);
}shortest,current;

Stack :: Stack(Stack &ptr)
{
	this->reset();
	for(int i = 0; i<ptr.len(); i++)
	{
		this->push(ptr.get(i));
	}
}

class Queue
{
	private:
		int head;
		int back;
		int arr[MAX];
	public:
		int len(){ return (abs(head-back)); }
		void push(int a){ arr[back] = a;back = (back+1)%MAX;}
		int get(int a){return arr[a];}
		int pop(){ int j = arr[head]; head = ((head+1)%MAX); return j; }
		int srch(int a){for(int i=head, j=0; j<(len());i=((i+1)%MAX),j++){if(arr[i] == a){return 1;}}return 0;}
		int show(){for(int i=head, j=0; j<(len());i=((i+1)%MAX),j++){printf("->%d",arr[i]);}return 0;}
		void reset(){head = 0;back = 0;}
		Queue(){head = 0; back = 0;}
}to_visit,visited;

class Graph
{
	private:
		vertex *head;
		vertex *last;
		int length;
		vertex *insert_vertex(int a);
		vertex *srch_vertex(int a);
	public:
		void insert_edge(int a, int b);
		void show();
		int len(){ return length; }
		int dfs(int a, int b);
		int bfs(int a, int b){to_visit.push(a);bfs_level(a,b);path(a,b);}
		int bfs_level(int a, int b);
		void path(int a, int b);
		Graph();
};

Graph :: Graph()
{
	head = (struct vertex*)calloc(sizeof(struct vertex),1); // dummy  vertex
	last = head;
	length = 0;
}

vertex *Graph :: srch_vertex(int a)
{
	vertex *ptr = head->next;
	while(ptr != NULL)
	{
		if(ptr->id == a)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

vertex *Graph :: insert_vertex(int a)
{
	// returns the node address either if it is created or it exists
	//cout<<"CREATING VERTEX...\nSEARCHING VERTEX...\n";
	vertex *s = srch_vertex(a);
	//cout<<"VERTEX SEARCHED\n";
	if (s == NULL)
	{
		//cout<<"VERTEX DOES NOT EXIST\n";
		last->next = (struct vertex*)calloc(sizeof(struct vertex),1);
		vertex *ptr = last->next;
		last = ptr;
		ptr->id = a;
		ptr->next = NULL;
		length++;
		ptr->nbr_val = 0;
		return ptr;
	}
	else
	{
		//cout<<"VERTEX EXISTS\n";
		return s; // node already exists
	}
}

void Graph :: insert_edge(int a, int b)
{
	//cout<<"\nCREATING EDGE...\n";
	vertex *vertex_s = insert_vertex(a);
	//cout<<"ADDED VERTEX:"<<a<<"\n";
    vertex *vertex_e = insert_vertex(b);
	//cout<<"ADDED VERTEX:"<<b<<"\n";

	// increase neighbours
	vertex_s->nbr_val++;
	vertex_e->nbr_val++;

	//assign neighbours
	(vertex_s->nbrs)[(vertex_s->nbr_val)-1] = vertex_e;
	(vertex_e->nbrs)[(vertex_e->nbr_val)-1] = vertex_s;
}

void Graph :: show()
{
	vertex *ptr = head->next;
	while(ptr != NULL)
	{
		printf("\n-> ID : %d\nNEIGHBOURS : ",ptr->id);
		for(int i = 0; i<ptr->nbr_val ; i++)
		{
			printf("%d, ",(ptr->nbrs)[i]->id);
		}
		printf("\n\n\n");
		ptr = ptr->next;
	}
	printf("\n");
	return;
}

int Graph :: dfs(int a, int b)
{
	//cout << "A = " << a <<", B = " << b << "\n";
	vertex *temp = srch_vertex(a);

	if( (shortest.len()<current.len()) AND (shortest.len() != -1) AND (current.srch(a)) )
	{
		// first condition means that we already have shortest path so current distance is greater than earlier hence no use
		// second condition means that shortest has a valid path
		// third condition tells if the node is visited
		//cout<<"RETURNED 0\n";
		current.pop();
		return 0;
	}

	if(a==b)
	{
		//cout<<"SHORTEST PATH FOUND !!!\n";
		current.push(a);
		//cout<<"CURRENT PATH : ";
		//current.show();
		//cout<<"\n";
		if(((shortest.len()) > (current.len())) OR (shortest.len() == 0))
		{
			// first condition checks that new path is shorter then older one
			// swcond condition checks that shortest stack is not empty
			shortest = current;
		}
		current.pop();
		return 1;

	}
	else
	{
		//cout<<"CURRENTLY IN DFS ELSE CODE\n";
		current.push(a);
		for(int i = 0; i < (temp->nbr_val); i++)
		{
			//cout<<"\nNEIGHBOUR IS "<<i<<"\n";
			if(!current.srch(((temp->nbrs)[i])->id))
			{
				//cout<<"DFS CALLED RECURSIVELY\n";
				// conditios means if node is not visited
				dfs(((temp->nbrs)[i])->id,b);
				// after visiting node
				continue;
			}
			else
			{
				//cout<<"DFS NEIGHBOUR IS VISITED\n";
				//current.show();
				continue;
			}
			current.pop();
		}
		// when all neighbours traversed
		current.pop();
	}
}

int Graph :: bfs_level(int a, int b)
{
	//cout<<"BETWEEN:"<<a<<", "<<b<<"\n";
	//to_visit.show();
	//cout<<"\n";
	if(a==b)
	{
		vertex *address = srch_vertex(b);
		address->parent = a;
		//cout<<"FOUND";
		return 1;
	}
	int s = 0;
	int f = 0;
	visited.push(a);
	while(true)
	{
		//cout<<"IN WHILE LOOP\n";
		f++;
		int y = to_visit.pop();
		//cout<<"POPPED: "<<y<<"\n";
		//cout<"SEARCHING\n";
		vertex *temp = srch_vertex(y);
		//cout<<"SEARCHED\n";
		for(int i =0; i< (temp->nbr_val);i++)
		{
			s =  ((temp->nbrs)[i])->id ;
			//cout<<"NBR:"<<s<<"\n";
			if(s==b)
			{
				vertex *address = srch_vertex(s);
				address->parent = y;
				//cout<<"FOUND\n";
				return 1;
			}
			//cout<<"LENGHT: "<<visited.len()<<"\n";
			//cout<<"SRCH RESULT:"<<visited.srch(s)<<"----\n";
			if ((!visited.srch(s)) AND (!to_visit.srch(s)))
			{
				vertex *address = srch_vertex(s);
				address->parent = y;
				//cout<<"PUSHED: "<<s<<"\n";
				//cout<<"PARENT: "<<address->parent<<"\n";
				to_visit.push(s);
				visited.push(s);
			}
			else
			{
				//cout<<"ALREADY VISITED\n";
			}
		}
		if(f>MAX)
		{
			//cout<<"NOT FOUND\n";
			return 0;
		}
	}
}

void Graph :: path(int a, int b)
{
	//cout<<"PATH B\\W :"<<a<<","<<b<<"\n";
	if(a==b)
	{
		cout<<"->"<<b;
		return;
	}
	int t = srch_vertex(b)->parent;
	path(a,t);
	cout<<"->"<<b;
}

int main()
{
	Graph map;

	map.insert_edge(1,2);
	map.insert_edge(1,3);
	map.insert_edge(1,4);
	map.insert_edge(2,3);
	map.insert_edge(2,5);
	map.insert_edge(3,6);
	map.insert_edge(4,7);
	map.insert_edge(4,8);
	map.insert_edge(5,6);
	map.insert_edge(5,9);
	map.insert_edge(6,10);
	map.insert_edge(6,11);
	map.insert_edge(7,8);
	map.insert_edge(7,11);
	map.insert_edge(7,12);
	map.insert_edge(8,12);
	map.insert_edge(9,13);
	map.insert_edge(10,13);
	map.insert_edge(10,14);
	map.insert_edge(11,14);
	//cout<<"EDGES INSERTED";
	//map.show();
	//cout<<"CALLING BFS";
	map.bfs(1,14);
	cout<<"\nDONE\n";
	map.dfs(1,14);
	shortest.show();

	return 0;
}
