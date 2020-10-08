#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b){
    if(a%b==0)
        return b;
    return gcd(b, a%b);
}

//확장유클리드 알고리즘 ax + by = 1인 방정식의 해(x, y)를 반환한다. 
//단, gcd(a, b) == 1 이어야만 한다, 그렇지 않다면 해가 존재하지 않는 것
//또한 반드시 a > b여야한다. 
pair<long long, long long> extend_euclid(long long a, long long b){
    if(b == 1){
        return make_pair(0ll, 1ll);
    }
    long long q = -1*a/b;
    long long r = a%b;
    if(r == 1){
        return make_pair(1ll, q);
    }
    pair<long long, long long> res = extend_euclid(b, r);
    return make_pair(res.second, res.second*q + res.first);
}

int main(){
    //a^(-1) mod n , a의 법n에서의 역원 구하기 
    //nx + ay = 1 에서 y가 a의 법n의 역원이다. 
    long long n, a;
    cin >> n >> a;
    long long mult_inverse;

    //gcd(n, a) != 1 이라면 ax + ny = 1의 해가 없음으로 역원이 존재하지 않는다//베주항등식 참고 
    if(gcd(n, a) != 1)
        mult_inverse = -1;
    else{
        //nx + ay = 1에서 해인 (x, y)반환 
        pair<long long, long long> res = extend_euclid(n, a);
        //pair의 2번째인자인 second, 즉 y가 역원에 해당한다. 
        long long tmp = res.second;
        //법 n에 맞춰서 만약 음수값이거나 n보다 큰 값이면, 0 <= y < n으로 값을 조정한다.  
        while(tmp < 0)
            tmp += n;
        while(tmp > n)
            tmp -= n;
        mult_inverse = tmp;
    }
    cout << mult_inverse << endl;
    return 0;
}
