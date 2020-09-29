/*
	Date : 2019 10 04 
	Author : roonm813 
	Subject : ACM-ICPC Team Note - DFS with while loop. using Stack 
	Time Complexity : O(V+E)
*/ 

/*	which is faster : implement DFS using recursive function calls or using stack? 
	Implementation with stack is slightly faster than with recursive function! but almost same.. 
*/ 
class Node{
public: 
	//add field which you need
	vector<int> neighbors; 
	bool visited; 
	Node():visited(false){}
}; 



void DFS(int start, Node* nodes){
    stack<int> nextVisits; 
    nextVisits.push(start); 
	nodes[start].visited = true; 

    while(!nextVisits.empty()){
        int here = nextVisits.top(); 
        nextVisits.pop(); 

        for(int i = 0; i < nodes[here].neighbors.size(); i++){
            int next = nodes[here].neighbors.at(i); 
            if(nodes[next].visited == false){
                nextVisits.push(next); 
                nodes[next].visited = true; 
            }
        }
    }
}


int main(){
	//N = number of Node  
	Node* nodes[N + 1]; 
	//intialization edge information 

	//DFS all
	//만약 connected graph가 아닌 경우를 대비해 visited가 아니라면 해당 node를 시작점으로 방문해야함.
	for(int i = 1; i < N + 1; i++){
		if(graphs[N]->visited == false)
			DFS(i, graphs); 
	}
	return 0; 
}