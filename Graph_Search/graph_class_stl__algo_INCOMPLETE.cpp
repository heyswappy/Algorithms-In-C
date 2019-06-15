#include<bits/stdc++.h>
using namespace std;

template class<class T1, class T2>
class PriorityQ{
    public:
    vector<T1> key;
    vector<T2> data;
    int last;
    PriorityQ(){last = -1;}
    void perUp(int a);
    void perDown(int a);
    void insert(int a, int b);
    int pop();
};

void PriorityQ :: perUp(int ind){
    int p = (ind-1)/2;
    if(ind<0) return;
    if(p<0) return;
    if (key[p] > key[ind]){
        T1 t = key[p];
        key[p] = key[ind];
        key[ind] = t;
        T2 s = data[p];
        data[p] = data[ind];
        data[ind] = s;
    }
    return;
}

void PriorityQ :: perDown(int ind){
    int max=-1;
    int c1,c2;
    c1 = ind*2;
    c2 = c1+1;
    if((c1<last)&&(key[c1]>key[ind])){
        max = c1;
    }
    if((c2<last)&&(key[c2]>key[ind])){
        max = c2;
    }
    if(max!=-1){
       return perDown(max);
    }
    return;
}

void PriorityQ :: insert(T1 k, T2 d){
    last++;
    key[last] = k;
    data[last] = d;
    perUp(last);
    return;
}

T2 PriorityQ :: pop(){
    T2 t = data[0];
    int a,b;
    if(last<0){
        return -1;
    }
    key[0] = key[last];
    data[0] = data[last];
    last--;
    perDown(0);
    return t;
}

class Graph;
class Node;
class NbrNode{
	int id; // extra information so that readily accesible
	int parent; // store extra information
	int wt; // weight of  the edge
	Node *node; // structure pointer to actual node
	NbrNode(int a, int b, Node *c, int p);
	bool operator < (NbrNode &b);
	friend class Node;
	friend class Graph;
};
NbrNode :: NbrNode(int a, int b, Node *c, int p){
	id = a;
	wt = b;
	node = c;
	parent = p;
	return;
}
bool NbrNode :: operator < (NbrNode &b){
        if(this->wt > b.wt) return true;
        return false;
}

class Node{
	int id; // id of a node
	int nbr; // number of neighbours
	int visit; // visited
	Node *parent; // shortest distance to this node is through parent node
	int dist; // distance from source
	int shortest_edge;
	map<int,NbrNode> nbrList; // map of neighbours
	Node(int a);
	void changeNbr(Node *a, int b);
	void show();
	friend class NbrNode;
	friend class Graph;
};
Node :: Node(int a){
	id = a;
	nbr = 0;
	visit = 0;
	parent = NULL;
	dist = 0;
	shortest_edge = 0;
}
void Node :: changeNbr(Node *r, int w){
	nbrList[r->id] = NbrNode(r->id, w, r, this->id);
	return;
}
void Node :: show(){
	cout<<"KEY: "<<id<<"\n";
	map<int,NbrNode> :: iterator itr = nbrList.begin();
	while(itr != nbrList.end()){
		cout<<"\tNBR: "<<itr->first<<" WEIGHT: "<<(itr->second).wt<<"\n";
		itr++;
	}
	return;
}

class Graph{
	private:
		map<int,Node> nodeTable;
		// functions
		Node* srchVertex(int a);
		bool dfsCore(Node &a, Node &b, stack<int> &path, set<int> &visited, set<int> &safety);
		bool bfsCore(Node &a, Node &b, map<int,int> parentTable);
		bool djikstra(Node &a, Node &b, map<int,int> parentTable);
		int colorCoreBound(Node &a, map<int,int> &colorTable);
		int colorCore(Node &a, map<int,int> &colorTable);
	public:
		Graph();
		Node* insertVertex(int a);
		void insertEdge(int a, int b, int wt);
		void insertBiEdge(int a, int b, int wt);
		void show();
		vector<int> dfs(int a, int b);
		vector<int> bfs(int a, int b);
		vector<int> djk(int a, int b);
		Graph prim();
		Graph kruskal();
		map<int,int> color(int a);
};
Graph :: Graph(){
}
Node* Graph :: srchVertex(int a){
	map<int,Node> :: iterator itr = nodeTable.find(a);
	if(itr != nodeTable.end()) return &(itr->second);
	return NULL;
}
Node* Graph :: insertVertex(int a){
	// returns the node address if it does not exist
	map<int,Node> :: iterator itr = nodeTable.find(a);
	if (itr != nodeTable.end()) return NULL;
	//else
	nodeTable[a] = Node(a);
	return &(nodeTable[a]);
}
void Graph :: insertEdge(int src, int dst, int wt){
	Node &a = nodeTable[src];
	Node &b = nodeTable[dst];
	a.changeNbr(&b,wt);
	return;
}
void Graph :: insertBiEdge(int src, int dst, int wt){
	Node &a = nodeTable[src];
	Node &b = nodeTable[dst];
	a.changeNbr(&b,wt);
	b.changeNbr(&a,wt);
	return;
}
void Graph :: show(){
	map<int,Node> :: iterator it = nodeTable.begin();
	while(it!=nodeTable.end()){
		cout<<"KEY: "<<it->first;
		it++;
	}
}
vector<int> Graph :: dfs(int a, int b){
	stack<int> path;
	set<int> visited;
	set<int> safety;
	Node &A = nodeTable[a];
	Node &B = nodeTable[a];
	dfsCore(A, B, path, visited, safety);
	vector<int> ans;
	ans.resize(path.size());
	int i = path.size()-1;
	while(i>-1){
		ans[i] = path.top();
		path.pop();
		i--;
	}
	return ans;
}
bool Graph :: dfsCore(Node &a, Node &b, stack<int> &path, set<int> &visited, set<int> &safety){
	if(a.id == b.id){
		return true;
	}
	map<int,NbrNode> :: iterator it = a.nbrList.begin();
	while(it != a.nbrList.end()){
		if((safety.find((it->second).id) != safety.end()) && (visited.find((it->second).id) != visited.end())){
			safety.insert((it->second).id);
			path.push((it->second).id);
			if(dfsCore(*((it->second).node), b, path, visited, safety)) return true;
			path.pop();
			safety.erase((it->second).id);
		}
	}
	visited.insert(a.id);
	return false;
}
vector<int> Graph :: bfs(int a, int b){
	map<int,int> parentTable;
	Node &A = nodeTable[a];
	Node &B = nodeTable[a];
	bfsCore(A, B, parentTable);
	vector<int> ans;
	int cur = b;
	while(b!=a){
		ans.push_back(parentTable[b]);
		b = parentTable[b];
	}
	int i = 0;
	int j = ans.size();
	int t = -1;
	while(i<j){
		t = ans[i];
		ans[i] = ans[j];
		ans[j] = t;
	}
	return ans;
}
bool Graph :: bfsCore(Node &a, Node &b, map<int,int> parentTable){
	queue<int> toVisit;
	set<int> visited;
	toVisit.push(a.id);
	Node &node = b;
	while(toVisit.size()!=0){
		node = toVisit.front();
		toVisit.pop();
		map<int,NbrNode> :: iterator itr = node.nbrList.begin();
		while(itr != node.nbrList.end()){
			if(visited.find((itr->second).id) != visited.end()){
				if((itr->second).id == b.id){
					parentTable[(itr->second).id] = node.id;
					return true;
				}
				toVisit.push((itr->second).id);
				parentTable[(itr->second).id] = node.id;
			}
			itr++;
		}
		visited.insert(node.id);
	}
	return false;
}
vector<int> Graph :: djk(int a, int b){
	map<int,int> parentTable;
	Node *A = &(nodeTable[a]);
	Node *B = &(nodeTable[b]);
	int i, j, t;
	vector<int> ans;
	djikstra(*A, *B, parentTable);
	while(b!=a){
		ans.push_back(parentTable[b]);
		b = parentTable[b];
	}
	// reverse
	for(i=0,j=ans.size(); i<j; i++,j++){
		t = ans[i];
		ans[i] = ans[j];
		ans[j] = t;
	}
	return ans;
}
bool Graph :: djikstra(Node &a, Node &b, map<int,int> parentTable){
	priority_queue <Node&> toVisit;
	toVisit.push(a);
	map<int,int> distTable;
	distTable[a.id] = 0;
	Node &node = b;
	while(toVisit.size()!=0){
		node = toVisit.top();
		toVisit.pop();
		map<int,NbrNode> :: iterator itr = node.nbrList.begin();
		while(itr != node.nbrList.end()){
			if((distTable[node.id]+((itr->second).wt)) < distTable[(itr->second).id]){
				distTable[(itr->second).id] = distTable[node.id]+((itr->second).wt);
				parentTable[(itr->second).id] = node.id;
				toVisit.insert(nodeTable[(itr->second).id])
			}
			itr++;
		}
	}
	return false;
}
Graph Graph :: kruskal(){
	int i = 0;
	int edgeCount = nodeTable.size() - 1 ;
	set<int> visited;
	priority_queue <NbrNode&> globalHeap;
	map<int,Node> :: iterator itr1 = nodeTable.begin();
	while(itr1 != nodeTable.end()){
		map<int,NbrNode> :: iterator itr2 = ((itr1->second).nbrList).begin();
		while(itr2 != (itr1->nbrList).end()){
			globalHeap.insert(itr2->second);
		}
	}
	Graph MST;
	NbrNode &ref = globalHeap.top();
	while(i<edgeCount){
		NbrNode &ref = globalHeap.top();
		globalHeap.pop();
		if((visited.find(ref.id) == visited.end())||(visited.find(ref.parent) == visited.end())){
			MST.insertVertex(ref.parent);
			MST.insertVertex(ref.id);
			MST.insertBiEdge(ref.parent, ref.id, ref.wt);
			visited.insert(ref.parent);
			visited.insert(ref.id);
			i++;
		}
	}
	return MST;
}
/*vector<int> Graph :: ps(int a, int b){
	map<int,int> parentTable;
	Node &A = nodeTable[a];
	Node &B = nodeTable[a];
	int a, b, i, j, t;
	vector<int,int> ans;
	djikstra(A, B, parentTable);
	a = A.id;
	b = B.id;
	while(b!=a){
		ans.insert(parentTable[b]);
		b = parentTable[b];
	}
	// reverse
	for(i=0,j=ans.size; i<j; i++,j++){
		t = ans[i];
		ans[i] = ans[j];
		ans[j] = t;
	}
	return ans;
}
bool Graph :: prim(Node &a, Node &b, map<int,Node&> parentTable){
	priority_queue <NbrNode&, vector<NbrNode&>, compareNodeForPQ> toVisit;
	queue<int> toVisit;
	toVisit.push(a);
	distTable[a.id] = 0;
	Node &node = b;
	while(toVisit.size()!=0){
		node = toVisit.top();
		toVisit.pop();
		set<int,Node> iterator :: it = node.nbrList.begin();
		while(it != node.nbrList.end()){
			if((distTable[node.id]+(it->wt)) < distTable[it->id]){
				distTable[it->id] = distTable[node.id]+(it->wt);
				parentTable[it->id] = node.id;
				toVisit.insert()
			}
			it++;
		}
	}
	return false;
}*/
map<int,int> Graph :: color(int a){
	map<int,int> colorTable;
	map<int,Node> :: iterator itr = nodeTable.begin();
	while(itr != nodeTable.end()){
		colorTable[(itr->first).id] = 0;
		itr++;
	}
	Node &A = nodeTable[a];
	int ans = colorCore(A, colorTable);
	colorTable[-1] = ans;
	return colorTable;
}
int Graph :: colorCoreBound(Node &a, map<int,int> &colorTable){
	vector<int> nbrColor;
	int i, ans;
	map<int,NbrNode> :: iterator itr = a.nbrList.begin();
	while(itr != a.nbrList.end()){
		nbrColor.push_back(colorTable[(itr->second).id]);
	}
	sort(nbrColor.begin(), nbrColor.end());
	ans = 0;
	for(i=1; i<nbrColor.size(); i++){
		if((nbrColor[i]-1 != nbrColor[i-1])&&(nbrColor[i] != nbrColor[i-1])){
			ans = nbrColor[i] - 1;
		}
	}
	if(ans == 0) ans = 1;
	return ans;
}
int Graph :: colorCore(Node &a, map<int,int> &colorTable){
	int m = 0;
	while(!colorTable[a.id]){
		colorTable[a.id] = colorCoreBound(a, colorTable);
	}
	map<int,NbrNode> :: iterator itr = a.nbrList.begin();
	while(itr != a.nbrList.end()){
		m = max(m,nodeTable[colorCore((itr->second).id], colorTable));
	}
	return m;
}/*
void salesmanCore(){
	//
}
int maxFlowCore(Node &src, Node &dest);*/

int main(){
	Graph obj = Graph();
	obj.insertVertex(1);
	obj.insertVertex(2);
	obj.insertVertex(3);
	obj.insertEdge(1,2,4);
	obj.insertEdge(2,3,5);
	obj.insertEdge(3,1,6);
	obj.show();
	return 0;
}
