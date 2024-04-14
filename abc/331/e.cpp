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


// multiset<ll> make_ms(vector<ll> &AA, vector<ll> &BB, ll N, ll M, ll L) {
//     multiset<ll> ms;
//     ll total = 0;
//     ll nxt_i;
//     for(ll i=0; i<N; i++) {
//         for(ll j=0; j<M; j++) {
//             total++;
//             ll price = AA[i]+BB[j];
//             ms.insert(price);
//             if (total == L+1) {
//                 nxt_i = i;
//                 goto LABEL_A;
//             }
//         }
//     }

// LABEL_A:
//     ll mn = *ms.begin();
//     for(ll i=nxt_i+1; i<N; i++) {
//         for(ll j=0; j<M; j++) {
//             ll c = AA[i]+BB[j];
//             if (c < mn) break;
//             ms.insert(c);
//         }
//     }

//     return ms;
// }
multiset<ll> make_ms(vector<ll> &AA, vector<ll> &BB, ll N, ll M, ll L) {
    multiset<ll> ms;

    ll n = (L+1)/M;
    ll m = (L+1)%M;
    ll mn = AA[n] + BB[m];
    if (n >= 1) {
        mn = min(mn, AA[n-1]+BB[M-1]);
    }

    for(ll i=0; i<N; i++) {
        for(ll j=0; j<M; j++) {
            ll price = AA[i]+BB[j];
            if (mn > price) break;
            ms.insert(price);
        }
    }

    return ms;
}

void solve() {
    ll N, M, L; cin >> N >> M >> L;
    vector<ll> A(N), B(M);
    vector<pair<ll,ll>> AA(N), BB(M);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<M; i++) cin >> B[i];
    for(ll i=0; i<N; i++) {
        AA[i] = {A[i], i};
    }
    for(ll i=0; i<M; i++) {
        BB[i] = {B[i], i};
    }
    sort(AA.begin(), AA.end());
    reverse(AA.begin(), AA.end());
    sort(BB.begin(), BB.end());
    reverse(BB.begin(), BB.end());

    set<pair<ll,ll>> pairs;
    for(ll q=0; q<L; q++) {
        ll c, d; cin >> c >> d;
        c--; d--;
        pairs.insert({c,d});
    }

    ll ans = -1;
    for(ll i=0; i<N; i++) {// 高々L+1回のansの更新
        auto[a, ai] = AA[i];

        for(ll j=0; j<M; j++) {
            auto[b, bj] = BB[j];

            if (pairs.count({ai,bj})) continue;
            ans = max(ans, a+b);
            break;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}