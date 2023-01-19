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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// ダブっているカードを優先的に食べたい
// ダブっているカードを貪欲に食べる
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    set<ll> st;  // ダブってないカード
    map<ll,ll> dbl; // dbl[i] := ダブっているカードiの枚数
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        if (dbl.count(A[i])) {
            dbl[A[i]]++;
        }
        else if (st.count(A[i])) {
            st.erase(A[i]);
            dbl[A[i]] = 2;
        }
        else {
            st.insert(A[i]);
        }
    }

    // ダブっているカードを貪欲に食べる
    while(dbl.size() != 0) {
        auto a = dbl.begin();  // 最小
        auto c = dbl.end(); c--;  // 最大
        if (a == c) {
            if (a->second >= 3) {
                // 3枚以上あるなら、食べてOK
                a->second -= 2;
                if (a->second == 1) {
                    dbl.erase(a);
                    st.insert(a->first);
                    break;
                }
            }
            else {
                // 2枚なら、「ダブってる2枚を食べる」か、「ダブってるカード1枚+ダブっていないカードを食べる」かする。
                // いずれにせよ、ダブってないカードの枚数は変わらない。
                break;
            }
            continue;
        }
        // aとcを食べる
        a->second--; c->second--;
        if (a->second == 1) {
            dbl.erase(a);
            st.insert(a->first);
        }
        if (c->second == 1) {
            dbl.erase(c);
            st.insert(c->first);
        }
    }
    cout << (ll)st.size() << endl;

}


int main() {
    solve();
    return 0;
}