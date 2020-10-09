#include <iostream>

using namespace std;

typedef long long LL;
typedef struct{
    LL x, y;
}Point;

class Line{
private:
    Point s, e;
public:
    Line(int x1, int y1, int x2, int y2){
      s = {x1, y1};
      e = {x2, y2};
    }
    LL getAreaOfTwoTriangles(Line &ano){
        // self 선분의 각각의 끝점(s, e)에서
        // ano 선분의 양 끝점(s, e)으로 선분을 연결해서 나오는 삼각형 2개의 넓이 합을 구함
        LL x = this->s.x;
        LL y = this->s.y;
        LL cross_s = ano.s.x*y + x*ano.e.y + ano.e.x*ano.s.y
                   - x*ano.s.y - ano.e.x*y - ano.s.x*ano.e.y;
        x = this->e.x;
        y = this->e.y;
        LL cross_e = ano.s.x*y + x*ano.e.y + ano.e.x*ano.s.y
                   - x*ano.s.y - ano.e.x*y - ano.s.x*ano.e.y;
        cross_s = cross_s < 0 ? -cross_s : cross_s;
        cross_e = cross_e < 0 ? -cross_e : cross_e;
        return cross_s + cross_e; // 실수형을 피하기위해 /2를 안해서 넓이의 2배인 것에 주의
    }
};

bool checkLineCross(Line &a, Line &b){
    // 1. ano 선분의 각각의 끝점에서 self 선분의 양 끝점으로 선분을 연결했을 때 나오는 삼각형 2개의 넓이 합을 구함
    // 2. self 선분의 각각의 끝점에서 ano의 선분의 양 끝점으로 선분을 연결해서 나오는 삼각형 2개의 넓이 합을 구함
    // 3. 두 합이 같으면 cross
    // 4. 아니면 not cross
    LL a_area = a.getAreaOfTwoTriangles(b);
    LL b_area = b.getAreaOfTwoTriangles(a);
    return a_area == b_area;
}

int main(){
    // Example
    Line l1(1,1,5,5);
    Line l2(1,5,5,1);
    cout << (checkLineCross(l1, l2) ? "cross" : "not cross") << '\n';

    Line l3(1,1,5,5);
    Line l4(6,10,10,6);
    cout << (checkLineCross(l3, l4) ? "cross" : "not cross") << '\n';

    return 0;
}
