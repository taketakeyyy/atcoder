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
    string S; cin >> S;
    ll N = S.size();
    vector<ll> ans(N, true);
    deque<pair<char,ll>> done; // 読んだやつ(文字,インデックス)
    for(ll idx=0; idx<(ll)S.size(); idx++) {
        done.push_back({S[idx], idx});

        if (done.size() >= 3) {
            // 3つ取り出して、ABCになっているか確認する
            auto c = done.back(); done.pop_back();
            auto b = done.back(); done.pop_back();
            auto a = done.back(); done.pop_back();

            if (a.first=='A' && b.first=='B' && c.first=='C') {
                ans[a.second] = false;
                ans[b.second] = false;
                ans[c.second] = false;
                continue;
            }
            else {
                // 戻す
                done.push_back(a);
                done.push_back(b);
                done.push_back(c);
                continue;
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        if (ans[i]) cout << S[i];
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}