#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    ll r1, c1;
    ll r2, c2;
    cin >> r1 >> c1;
    cin >> r2 >> c2;

    ll diff = abs(r2-r1) + abs(c2-c1);

    if (diff == 0LL) {
        cout << 0 << endl;
        return;
    }
    else if (diff <= 3LL) {
        // 1回の3マス以内移動でOK
        cout << 1 << endl;
        return;
    }
    else if (abs(r2-r1) == abs(c2-c1)) {
        // 1回の斜め移動でOK
        cout << 1 << endl;
        return;
    }
    else if (diff <= 6LL) {
        // 2回の3マス以内移動でOK
        cout << 2 << endl;
        return;
    }
    else if (abs(abs(r2-r1)-abs(c2-c1)) <= 3LL) {
        // 1回斜め移動と、3マス以内の移動でOK
        cout << 2 << endl;
        return;
    }
    else if (diff%2 == 0) {
        // 2回の斜め移動でOK
        cout << 2 << endl;
        return;
    }
    else {
        // 本当か？
        cout << 3 << endl;
        return;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}