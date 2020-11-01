#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int A, B;
    cin >> A >> B;
    int X = (A+B)/2;
    int Y = A - X;
    cout << X << " " << Y;

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}