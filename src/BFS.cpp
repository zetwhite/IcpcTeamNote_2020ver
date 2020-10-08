typedef struct{
	int self;
	vector<int> node; //인접한 노드들
}Node

Node nodes[N];

void BFS(int start){

	bool *visit = new bool[N];
	queue<Node> queue(N);
	
	//1. start node를 큐에 넣는다.
	queue.push(start);
	
	//2. 큐가 빌 때까지 계속한다.
	while(!queue.empty()){
		// 2-1. 큐에서 node 꺼냄.
		Node cur = queue.back();
		queue.pop();
		
		// 2-2. 큐에 (아직 방문 안 한) 인접한 node들을 넣음.
		for(int i=0; i<cur.node.size(); i++){
			Node nxt = cur.node[i];
			if( visit[ nxt.self ] == false ){
				visit[ nxt.self ] = true;
				queue.push( nxt );
			}
		}
	}
}