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


vector<pair<char,ll>> RL(string S) {
    vector<pair<char,ll>> res;
    char now = S[0];
    ll cnt = 1;
    for(ll i=1; i<S.size(); i++) {
        if (now == S[i]) {
            cnt++;
            continue;
        }
        else {
            res.push_back({now, cnt});
            now = S[i];
            cnt = 1;
        }
    }
    res.push_back({now, cnt});
    return res;
}

void solve() {
    string S, T; cin >> S >> T;
    // ランレングス
    auto S2 = RL(S);
    auto T2 = RL(T);

    if ((ll)S2.size() != (ll)T2.size()) {
        cout << "No" << endl;
        return;
    }

    bool is_ok = true;
    for(ll i=0; i<S2.size(); i++) {
        if (S2[i].first == T2[i].first) {
            if (S2[i].second==1 && T2[i].second==1) { continue; }
            if ((S2[i].second!=1) && (S2[i].second <= T2[i].second)) { continue; }
        }
        is_ok = false;
        break;
    }

    if (is_ok) {
        cout << "Yes" <<endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}