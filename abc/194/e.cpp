#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    rep(i,N) {
        cin >> A[i];
    }
    // 尺取法
    map<ll,ll> mp;
    ll ans = 0;
    for(int i=0; i<M; i++) {
        mp[A[i]]++;
        if (A[i]==ans) {
            while(1) {
                ans++;
                if (!mp.count(ans) || mp[ans]==0) {
                    break;
                }
            }
        }
    }
    for (int i=1; i<N; i++) {
        if (ans == 0) break;
        if (i+M-1==N) break;

        mp[A[i+M-1]]++;
        mp[A[i-1]]--;
        if (mp[A[i-1]]==0 && A[i-1]<ans) {
            ans = A[i-1];
        }
    }
    cout << ans << endl;
}

void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 最初のM個の分布をとる
    map<ll,ll> cnt;  // 各数字の分布
    for(ll i=0; i<M; i++) cnt[A[i]]++;

    // 最初のmexを求める
    ll mex = 0;
    while(cnt.count(mex)) mex++;

    // 尺取法で分布とmexを更新しながら走査する
    for(ll i=1; i+M-1<N; i++) {
        cnt[A[i-1]]--;
        cnt[A[i+M-1]]++;
        if (cnt[A[i-1]] == 0) {
            mex = min(mex, A[i-1]);
        }
    }

    // 出力
    cout << mex << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}