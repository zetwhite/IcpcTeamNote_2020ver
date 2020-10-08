#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

#define NMAX 100000
typedef long long LL;
typedef pair<LL, LL> Point;

int N;  // num of point
Point point[NMAX+1]; //pair<x, y>
Point convex_hull[NMAX]; //save points in convex hull
int ans = 0; // convex hull count

int ccw(Point &a, Point &b, Point &c){ // 반시계 방향(ccw)를 찾는 알고리즘
    LL cross = a.first*b.second + b.first*c.second + c.first*a.second
                - b.first*a.second - c.first*b.second - a.first*c.second;
    if(cross > 0) return 2;         // ccw
    else if(cross == 0){            // parallel
        return 1;
    }
    else return -1;                 // cw
}
bool cmp(Point& a, Point& b){ // 탐색 시작점을 기준으로, 기울기가 작은 순서대로 정렬하기 위한 비교 함수
    LL agrad = (a.second-point[0].second)*(b.first-point[0].first);
    LL bgrad = (b.second-point[0].second)*(a.first-point[0].first);
    if(agrad > bgrad) return 0;
    else if(agrad == bgrad && a.first > b.first) return 0; // 기울기가 같으면 x값이 작은 순서대로 정렬
    return 1;
}
void convexHull(){
    // 첫 두 점을 convexhull에 넣는다.
    convex_hull[0] = point[0];
    convex_hull[1] = point[1];
    ans = 2;
    // State Space에 있는 point들을 탐색하며 convex hull을 찾는다.
    for(int p=2; p<N+1; p++){
        LL cross = ccw(convex_hull[ans-2], convex_hull[ans-1], point[p]); // cross product
        // ccw인 경우, point를 convex hull에 넣는다.
        if( cross == 2){
            convex_hull[ans] = point[p];
            ans++;
        }
        // parallel인 경우, 이전 point를 삭제, 현재 point를 추가.
        // 문제 조건에서 변에 여러 점이 있는 경우, 양 끝점만 개수에 포함되기 때문.
        else if(cross == 1){
            convex_hull[ans-1] = point[p];
        }
        // cw인 경우, ccw가 될때까지 이전 point들을 convex_hull에서 제외한다.
        else{
            bool add_point_flag = false;
            while(ans > 2){
                ans--;
                cross = ccw(convex_hull[ans-2], convex_hull[ans-1], point[p]);
                if(cross == 2){ // ccw인 경우, 현재 point 추가.
                    convex_hull[ans] = point[p];
                    ans++;
                    add_point_flag = true;
                    break;
                }
                else if(cross == 1){ // parallel인 경우, 이전 point 삭제, 현재 point 추가.
                    convex_hull[ans-1] = point[p];
                    add_point_flag = true;
                    break;
                }
            }
            // 만약 시작점과 convex hull의 두번째 point만 남았는데 여전히 cw인 경우,
            // 두번째 point를 지워주고 현재 point를 넣는다.
            if(!add_point_flag){
                convex_hull[ans-1] = point[p];
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);

    // Example
    cin >> N; // point의 개수
    for(int i=0; i<N; i++){
        cin >> point[i].first >> point[i].second;
        // 편의를 위해 point의 범위 >0 으로 맞춰준다.
        point[i].first += 40001;
        point[i].second += 40001;
    }
    sort(point, point+N);       // x, y 최소값 찾기 --> 탐색 시작점을 찾음.
    sort(point+1, point+N, cmp);// point[0]에 대한 기울기 오름차순
    point[N] = point[0];        // convex hull 계산의 편의를 위해, 시작점을 마지막 원소에 넣어줌.

    convexHull();               // convex hull과 convex hull의 point개수를 구한다.
    cout << ans-1; // 마지막 원소 == 시작점이었음으로, 중복되는 시작점을 빼줌.

    return 0;
}
