#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    vector<string> S(10);
    for(ll i=0; i<10; i++) {
        cin >> S[i];
    }

    for(ll a=0; a<10; a++) {
        for(ll b=a; b<10; b++) {
            for(ll c=0; c<10; c++) {
                for(ll d=c; d<10; d++) {
                    vector<string> T(10, "..........");
                    for(ll i=a; i<=b; i++) {
                        for(ll j=c; j<=d; j++) {
                            T[i][j] = '#';
                        }
                    }

                    bool is_ok = true;
                    for(ll i=0; i<10; i++) {
                        if (S[i] == T[i]) continue;
                        is_ok = false;
                    }

                    if (is_ok) {
                        cout << a+1 << " " << b+1 << endl;
                        cout << c+1 << " " << d+1 << endl;
                        return;
                    }
                }
            }
        }
    }
}


int main() {
    solve();
    return 0;
}