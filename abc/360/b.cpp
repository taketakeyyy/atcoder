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
    string S, T; cin >> S >> T;
    ll N = S.size();

    for(ll w=1; w<N; w++) {
        // Sをw文字ごとに区切る
        vector<string> divided;
        ll cnt = 0;
        string s = "";
        for(ll i=0; i<N; i++) {
            s.push_back(S[i]);
            cnt++;
            if (cnt == w) {
                divided.push_back(s);
                s.clear();
                cnt = 0;
            }
        }
        if (!s.empty()) divided.push_back(s);

        for(ll c=0; c<w; c++) {
            string t = "";
            for(auto s: divided) {
                if (c >= s.size()) continue;
                t.push_back(s[c]);
            }

            if (T == t) {
                cout << "Yes" << endl;
                return;
            }
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}