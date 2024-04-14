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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    string S, T; cin >> S >> T;
    map<char,ll> mpS, mpT;

    auto is_atcoder = [&](char c) {
        return (c=='a' || c=='t' || c=='c' || c=='o' || c=='d' || c=='e' || c=='r');
    };

    for(ll i=0; i<(ll)S.size(); i++) {
        mpS[S[i]]++;
    }
    ll at_num = 0;
    for(ll i=0; i<(ll)T.size(); i++) {
        if (T[i] != '@') mpS[T[i]]--;
        else at_num++;
    }

    for(auto[key,val]: mpS) {
        if (key == '@') {
            continue;
        }
        else if (!is_atcoder(key)) {
            if (val != 0) {
                cout << "No" << endl;
                return;
            }
        }
        else {
            if (val == 0) {
                continue;
            }
            else if (val > 0) {
                at_num -= val;
            }
            else {
                mpS['@'] -= abs(val);
            }
        }
    }

    if (at_num<0 || mpS['@']<0) {
        cout << "No" << endl;
        return;
    }
    else {
        cout << "Yes" << endl;
        return;
    }
}


int main() {
    solve();
    return 0;
}