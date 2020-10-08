#include <iostream>
typedef long long ll;
using namespace std; 
 
/*보다 빠른 n^k를 위하여 
    5^12 = (5^6)^2 = ((5^3)^2)^2  = ((5^2 * 5)^2)^2 
    12 / 2 = 6 + 0  square
    6 / 2 = 3 + 0   square
    3 / 2 = 1 + 1   multiply
*/  

ll get_power(int n, int k){
    bool bin[64];
    int i = 0; 
    int power = k;
    while( power > 0 ){
        if(power % 2)
            bin[i] = 1;
        else
            bin[i] = 0; 
        i++; 
        power = power/2;
    }
 
    i = i - 2; 
    ll res = n; 
    while(i >= 0){
        res = res * res; 
        cout << "[" << i << "], res = " << res << "(sqaure)" << endl; 
        if(bin[i]){
            res = res * n; 
            cout << "[" << i << "], res = " << res << "(multiply)" << endl;
        }
        i--;
    }
    return res;
}
 
int main(){
    int a, b; 
    cin >> a >> b; 
    ll num = get_power(a, b);
    cout << a << "^(" << b << ") = " << num << endl; 
    return 0; 
}
