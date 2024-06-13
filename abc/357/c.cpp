#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<vector<vector<char>>> level(7);
    level[0] = {{'#'}};

    // レベルiのカーペットを作る
    ll pow3 = 1;
    for(ll i=1; i<=N; i++) {
        pow3 *= 3;
        level[i].assign(pow3, vector<char>(pow3, '-'));

        ll pivot = pow3/3;
        for(ll h=0; h<pow3; h++) {
            for(ll w=0; w<pow3; w++) {
                if (pivot<=h and h<pivot*2 and pivot<=w and w<pivot*2) {
                    level[i][h][w] = '.';
                }
                else {
                    level[i][h][w] = level[i-1][h%pivot][w%pivot];
                }
            }
        }
    }

    // 出力
    for(ll h=0; h<(ll)level[N].size(); h++) {
        for(ll w=0; w<(ll)level[N][0].size(); w++) {
            cout << level[N][h][w];
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}