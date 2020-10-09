#include <iostream>
#include <map>
#include <utility>
using namespace std;

//map<int, int> disjoint_set; // map<self value, root value>
int *disjoint_set;

void make_set(int set_size){
    disjoint_set = new int[set_size+1];
    for(int s=0; s<set_size+1; s++){
        disjoint_set[s] = -1; // init: no root
    }
}

int find_root(int a){
    int root = a;
    while(disjoint_set[root] != -1){
        root = disjoint_set[root];
    }
    if(disjoint_set[a] != -1) disjoint_set[a] = root; //optimizing
    return root;
}

void union_set(int a, int b){
    int a_root = find_root(a);
    int b_root = find_root(b);
    if(a_root == b_root) return;    // root가 같으면 합칠 필요 없다.
    disjoint_set[b_root] = a_root;  // root가 다르면 b set을 a set에 붙여준다.
}

bool find_set(int a, int b){
    int a_root = find_root(a);
    int b_root = find_root(b);
    if(a_root == b_root) return true;   // a와 b는 같은 set이다.
    return false;                       // a와 b는 disjoint set이다.
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); // 입력이 100,000*3 정도 되는 큰 입력이면, sync_with_stdio 보다 cin.tie()가 더 중요하다고 함!
    cout.tie(0);

    // 두 node a,b의 set을 합치거나 같은 set에 있는지 확인하는 문제.

    int N, M; // 초기 집합의 개수, 연산(Question)의 개수
    cin >> N >> M;

    make_set(N); // disjoint set을 초기화한다.

    for(int m=0; m<M; m++){
        int question, a, b;
        cin >> question >> a >> b;

        switch(question){
        case 0: // union
            union_set(a, b);
            break;
        case 1: //find
            cout << (find_set(a, b) ? "YES" : "NO") << '\n';
            break;
        }
    }
    return 0;
}
