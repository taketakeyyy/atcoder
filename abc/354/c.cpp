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
    vector<ll> A(N), C(N);
    vector<tuple<ll,ll,ll>> cards(N); // (コスト,強さ,カード番号)
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> C[i];
        cards[i] = {C[i],A[i],i+1};
    }

    // 平面走査
    sort(cards.begin(), cards.end());
    set<ll> st;
    ll pre_a = -INF;
    for(ll i=0; i<N; i++) {
        auto[c,a,id] = cards[i];
        if (a > pre_a) {
            st.insert(id);
            pre_a = a;
        }
    }

    // 答え
    cout << st.size() << endl;
    for(auto id: st) {
        cout << id << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}