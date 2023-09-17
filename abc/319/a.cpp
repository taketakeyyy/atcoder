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

map<string, ll> mp = {
    {"tourist", 3858},
    {"ksun48", 3679},
    {"Benq", 3658},
    {"Um_nik", 3648},
    {"apiad", 3638},
    {"Stonefeang", 3630},
    {"ecnerwala", 3613},
    {"mnbvmar", 3555},
    {"newbiedmy", 3516},
    {"semiexp", 3481},
};

void solve() {
    string s; cin >> s;
    cout << mp[s] << endl;
}


int main() {
    solve();
    return 0;
}