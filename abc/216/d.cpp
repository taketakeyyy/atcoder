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


void solve() {
    ll N, M; cin >> N >> M;
    vector<deque<ll>> A(M);
    for(ll i=0; i<M; i++) {
        ll k; cin >> k;
        for(ll j=0; j<k; j++) {
            ll a; cin >> a;
            A[i].push_back(a);
        }
    }

    map<ll,vector<ll>> mp;  // mp[色] := i番目の筒の先頭にある
    for(ll i=0; i<M; i++) {
        ll a = A[i].front();
        mp[a].push_back(i);
    }

    // 同じ色のボールはちょうど2個ずつしか存在しないので、貪欲に取っていけば良い
    deque<ll> deq;
    for(auto [key, vec]: mp) {
        if (vec.size() == 2) {
            deq.push_back(key);
        }
    }

    // 貪欲に取っていく
    ll cnt = 0;  // 取った回数
    while(!deq.empty()) {
        ll a = deq.front();
        deq.pop_front();

        // 取る
        cnt++;
        for(auto i: mp[a]) {
            A[i].pop_front();
            // 筒が空じゃないなら、次のやつをプッシュする
            if (!A[i].empty()) {
                ll na = A[i].front();
                mp[na].push_back(i);
                if (mp[na].size() == 2) {
                    deq.push_back(na);
                }
            }
        }
        mp[a].clear();
    }

    if (cnt == N) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}