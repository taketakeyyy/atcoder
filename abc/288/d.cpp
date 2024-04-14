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


void solve() {
    ll N, K; cin >> N >> K;
    // 累積和
    vector<ll> ruiseki(N+1,0);
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i];
        ruiseki[i] = ruiseki[i-1] + A[i];
    }

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll l, r; cin >> l >> r;

        // B作成
        vector<ll> B;
        for(ll i=l; i<=r; i++) {
            B.push_back(A[i]);
        }

        // シミュレーション
        ll is_ok = true;
        for(ll i=0; i<(ll)B.size(); i++) {  // 高々N
            if (i+K-1 >= (ll)B.size()) {
                for(ll j=i; j<(ll)B.size(); j++) {
                    if (B[j] == 0) continue;
                    is_ok = false;
                    break;
                }
                break;
            }
            if (B[i] != 0) {
                ll c = B[i];
                for(ll j=i; j<=i+K-1; j++) {
                    B[j] -= c;
                }
            }
            else {
                continue;
            }
        }
        if (is_ok) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}

void solve2() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N+1,0);
    for(ll i=1; i<N+1; i++) {
        cin >> A[i];
    }

    // 配列AをMOD K グループに分けて、和を求めておく
    vector Gsum(K, vector<ll>(N+1, 0));  //Gsum[k][i] := グループkの、i番目までの累積和
    for(ll i=1; i<N+1; i++) {
        for(ll k=0; k<K; k++) Gsum[k][i] = Gsum[k][i-1];
        Gsum[(i-1)%K][i] += A[i];
    }

    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll l, r; cin >> l >> r;

        // MOD K グループごとの和が同じなら0にできる
        bool is_ok = true;
        ll group_sum = -1;  // グループの和
        for(ll k=0; k<K; k++) {
            ll total = Gsum[k][r] - Gsum[k][l-1];
            if (group_sum == -1) {
                group_sum = total;
            }
            else {
                if (group_sum != total) {
                    is_ok = false;
                    break;
                }
            }
        }

        if (is_ok) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}