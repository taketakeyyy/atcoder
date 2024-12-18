#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    vector<ll> ps;
    for(ll i=0; i<5; i++) {
        ll a; cin >> a;
        ps.push_back(a);
    }
    sort(ps.begin(), ps.end());

    string S = "ABCDE";
    vector<pair<ll,string>> person;
    for(ll bit=(1<<5)-1; bit>=0; bit--) {
        ll total = 0;
        string name = "";
        for(ll d=0; d<5; d++) {
            if (bit>>d&1) {
                total += ps[d];
                name += S[d];
            }
        }
        person.push_back({total, name});
    }

    auto comp = [&](pair<ll,string> &p1, pair<ll,string> &p2) -> bool {
        if (p1.first > p2.first) return true;
        if (p1.first < p2.first) return false;
        if (p1.first == p2.first) {
            return p1.second < p2.second;
        }
        return false;
    };

    sort(person.begin(), person.end(), comp);

    for(ll i=0; i<31; i++) {
        auto[p,name] = person[i];
        cout << name << endl;
    }
}


int main() {
    solve();
    return 0;
}