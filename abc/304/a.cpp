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
    ll N; std::cin >> N;
    vector<pair<string, ll>> person(N);
    // 年齢が一番小さい人を探す
    ll min_i, min_age=INF;
    for(ll i=0; i<N; i++) {
        string name;
        ll a;
        std::cin >> name >> a;
        if (min_age > a) {
            min_age = a;
            min_i = i;
        }
        person[i] = {name, a};
    }

    // 順番に出力する
    ll i = min_i;
    while(1) {
        auto[name, age] = person[i];
        std::cout << name << endl;
        i++; i%=N;
        if (i == min_i) break;
    }
}


int main() {
    solve();
    return 0;
}