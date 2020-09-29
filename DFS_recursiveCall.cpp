/*
	Date : 2019 10 04 
	Author : roonm813 
	Subject : ACM-ICPC Team Note - DFS with recursive call 
	Time Complexity : O(V+E)
*/ 

class Node{
public: 
	//add field which you need
	vector<int> neighbors; 
	bool visited; 
	Node():visited(false){}
}; 


void DFS(int here, Node* nodes){
	cout << "DFS visits" << here << endl; 
	for(int i = 0; i < nodes[here].neighbors.size(); i++){
		int next = nodes[here].neighbors.at(i); 
		if(graphs[next].visited == false)
			DFS(next, nodes)
	} 
}

int main(){
	//N = number of Node  
	Node nodes[N + 1]; 
	//initailization edge infomation. 

	//DFS all
	//만약 connected graph가 아닌 경우를 대비해 visited가 아니라면 해당 node를 시작점으로 방문해야함.
	for(int i = 1; i < N + 1; i++){
		if(graphs[N]->visited == false)
			DFS(i, graphs); 
	}
	return 0; 
}