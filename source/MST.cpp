#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
 
using namespace std;
 
typedef struct kruskal {
    int from;
    int to;
    int val;
}KS;
 
vector<KS> edge;
 
int parent[10002];
int res;
bool chk;
 
bool comp(KS d1, KS d2)
{
    return d1.val < d2.val;
}
 
// 파인드
int find(int u)
{
    if (u == parent[u])
        return u;
 
    return parent[u] = find(parent[u]);
}
 
// 유니온
void merge(int u, int v)
{
    chk = false;
    u = find(u);
    v = find(v);
 
    // 사이클 존재 여부 확인 코드
    if (u == v)
        return;
 
    parent[u] = v;
    chk = true;
}
 
int main()
{
    int V, E;
 
    scanf("%d %d", &V, &E);
 
    // 부모를 자기 자신으로 초기화
    for (int i = 1; i <= V; i++)
        parent[i] = i;
 
    // 그래프 형성
    for (int i = 0; i < E; i++)
    {
        KS ks;
        scanf("%d %d %d", &ks.from, &ks.to, &ks.val);
        edge.push_back(ks);
    }
 
    // 크루스칼 알고리즘에 의해 간선을 오름차순 정렬
    sort(edge.begin(), edge.end(), comp);
 
    // 간선 union, 사이클이 존재하지 않도록
    for (int i = 0; i < E; i++)
    {
        merge(edge[i].from, edge[i].to);
        
        if(chk)
            res += edge[i].val;
    }
 
    printf("%d", res);
 
    return 0;
}


출처: https://www.crocus.co.kr/733 [Crocus]
