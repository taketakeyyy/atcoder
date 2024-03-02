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
    ll N, T; cin >> N >> T;
    vector<ll> A(T), B(T);
    vector<ll> score(N, 0); // 各選手の点数
    unordered_map<ll,ll> mp; // 各点数の人数
    mp[0] = N;
    for(ll t=0; t<T; t++) {
        ll a, b; cin >> a >> b;
        a--;
        mp[score[a]]--;
        if (mp[score[a]]==0) {
            mp.erase(score[a]);
        }
        score[a] += b;
        mp[score[a]]++;

        // 種類数出力
        cout << mp.size() << endl;
    }

}


int main() {
    solve();
    return 0;
}