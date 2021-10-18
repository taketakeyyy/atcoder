#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve_ac() {
    // 解説通りの実装
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    // 単調性を利用した尺取法
    ll ans = 0;
    map<ll,ll> Map;
    ll cr = 0, cnt = 0;
    for(ll i=0; i<N; i++) {
        while(cr <= N-1) {
            if (Map[A[cr]]==0 && cnt==K) break;
            if (Map[A[cr]]==0) cnt++;
            Map[A[cr]] += 1;
            cr++;
        }
        ans = max(ans, cr-i);
        if (Map[A[i]]==1) cnt--;
        Map[A[i]] -= 1;
    }

    // 出力
    cout << ans << endl;
}

void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    // 単調性を利用した尺取法
    ll ans = 0;
    set<ll> kinds;  // 連続部分列の種類数
    map<ll,ll> kinds_cnt;  // 連続部分列の各種類の出現数
    ll r = 0;  // 右側のインデックス
    for(ll i=0; i<N; i++) {
        while(r<N) {
            if (kinds.count(A[r]) || (!kinds.count(A[r])&&kinds.size()<K)) {
                // K種類を超えない場合
                kinds.insert(A[r]);
                kinds_cnt[A[r]]++;
                ans = max(ans, r-i+1);
                r++;
            }
            else {
                // K種類を超える場合
                kinds_cnt[A[i]]--;
                if (kinds_cnt[A[i]]==0) kinds.erase(A[i]);
                break;
            }
        }
    }

    // 出力
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}