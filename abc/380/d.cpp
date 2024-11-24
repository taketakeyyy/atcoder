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
    string S; cin >> S;
    ll N = S.size();
    ll Q; cin >> Q;
    vector<ll> K(Q);
    for(ll q=0; q<Q; q++) cin >> K[q];

    // S[i]の長さ
    vector<ll> Ns;
    {
        ll n = N;
        while(1) {
            if (n > 2e18+10) break;
            Ns.push_back(n);
            n *= 2;
        }
    }

    vector<char> ans;
    for(ll q=0; q<Q; q++) {
        ll k = K[q];
        k--;

        ll ni = lower_bound(Ns.begin(), Ns.end(), k+1) - Ns.begin();
        if (ni == 0) {
            ans.push_back(S[k]);
        }
        else {
            ni--;
            ll flip = 0;
            while(1) {
                if (ni == -1) break;
                if (k < N) break;
                k = k % Ns[ni];
                flip ^= 1;
                ni = lower_bound(Ns.begin(), Ns.end(), k+1) - Ns.begin();
                ni--;
            }

            if (flip) {
                if (S[k] >= 'a') ans.push_back(S[k]-32);
                else ans.push_back(S[k]+32);
            }
            else {
                ans.push_back(S[k]);
            }
        }
    }

    // 出力
    for(char v: ans) {
        cout << v << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}