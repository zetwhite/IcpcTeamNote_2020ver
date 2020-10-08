#include <iostream> 
#include <vector>
#include <cstring> 
#define MAX 1001
using namespace std; 

int A_size, B_size; //A그룹의 크기, B그룹의 크기 
vector<int> A_adj[MAX]; //A그룹 => B그룹 연결선
int A[MAX];  //A->B, a에 매칭되는 B의 element 번호
int B[MAX]; //B->A , b에 매칭되는 A의 element 번호 

bool goBipartiteMatching(int a, bool* callstack){
    callstack[a] = true; //무한루프 방지를 위해서, 해당 매칭에서 이미 방문한 것은 체크한다. 
    for(int idx = 0; idx < A_adj[a].size(); idx++){ //A와 연결된 B의 모든 원소 방문
        int b = A_adj[a][idx]; 
        //b에 짝이 없다면 바로 매칭 
        if(B[b] == -1){ 
            A[a] = b; 
            B[b] = a;
            return true;  
        }
        //이미 b에 짝이 있다. 하지만 B[b]가 이번 스텝에서 방문되지 않았고, B[b]에 새로운 원소를 찾을 수 있다면 a-b매칭 가능 
        if(callstack[B[b]] == false && goBipartiteMatching(B[b], callstack)){ 
            A[a] = b; 
            B[b] = a; 
            return true; 
        }
    }
    return false; 
}

int main(){
    cin >> A_size; 
    cin >> B_size; 
    A_size++; //A의 원소가 1번부터 n번이라서, index도 1~n을 사용할 수 있게 size하나 증가시킴 
    B_size++; //B의 원소가 1번부터 n번이라서 index도 1~n을 사용할 수 있기 size하나 증가시킴
    int adj_count, tmp;  //adj입력받기 
    for(int i = 1; i < A_size; i++){
        cin >> adj_count; 
        for(int j = 0; j < adj_count; j++){
            cin >> tmp; 
            A_adj[i].push_back(tmp); 
        }
    }
    memset(A, -1, sizeof(int)*(A_size));
    memset(B, -1, sizeof(int)*(B_size)); 

    //A의 i번이 매칭되지 않았다면 매칭시도 
    bool callStack[A_size]; 
    for(int i = 1; i < A_size; i++){
        if(A[i] == -1){
            memset(callStack, false, sizeof(bool)*A_size); 
            goBipartiteMatching(i, callStack); 
        }
    }
    return 0; 
}