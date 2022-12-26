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

// ナイーブ実装
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M+1);
    for(ll i=1; i<M+1; i++) cin >> A[i];

    for(ll i=1; i<=M; i++) {
        vector<ll> B(N+1);
        for(ll bi=1; bi<=N; bi++) B[bi] = bi;

        for(ll k=1; k<=M; k++) {
            if (k==i) continue;
            swap(B[A[k]], B[A[k]+1]);
        }

        // 1を探す
        ll ans = -1;
        for(ll j=1; j<=N; j++) {
            if (B[j]==1) {
                ans = j; break;
            }
        }
        cout << ans << endl;
    }
}


void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M+1);
    for(ll i=1; i<M+1; i++) cin >> A[i];

    for(ll i=1; i<=M; i++) {
        ll ans_i = 1;

        for(ll k=1; k<=M; k++) {
            if (k==i) continue;
            if (A[k]==ans_i) ans_i++;
            else if (A[k]+1==ans_i) ans_i--;
        }

        cout << ans_i << endl;
    }
}

// 解説AC
void solve3() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M);
    for(ll i=0; i<M; i++) {
        cin >> A[i]; A[i]--;
    }

    // S[i] := 上からi本操作したときに1がどこにあるか
    vector<ll> S(M);  // 上からi本やる直前に1がどこに来るか（インデックス）
    ll p = 0;
    for(ll i=0; i<M; i++) {
        S[i] = p;
        if (A[i] == p) p++;
        else if (A[i]+1 == p) p--;
    }

    // 下からのシミュレーションをしながら答えを求めていく
    vector<ll> ans(M);
    vector<ll> B(N);
    for(ll i=0; i<N; i++) B[i] = i;
    for(ll i=M-1; i>=0; i--) {
        ans[i] = B[S[i]];
        swap(B[A[i]], B[A[i]+1]);
    }

    // 出力
    for(ll i=0; i<M; i++) cout << ans[i]+1 << endl;
}

void solve4() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M);
    for(ll i=0; i<M; i++) {
        cin >> A[i]; A[i]--;
    }

    // 上から下へ、1の位置をメモっていくシミュレーション
    vector<ll> pos(M+1);  // 1の位置
    pos[0] = 0;
    for(ll k=0; k<M; k++) {
        if (A[k] == pos[k]) pos[k+1] = pos[k]+1;
        else if (A[k]+1 == pos[k]) pos[k+1] = pos[k]-1;
        else pos[k+1] = pos[k];
    }

    // 下から上へ、シミュレーションしながら答えを埋める
    vector<ll> B(N);
    vector<ll> ans(M);
    for(ll i=0; i<N; i++) B[i]=i;
    for(ll k=M-1; k>=0; k--) {
        ans[k] = B[pos[k]];
        swap(B[A[k]], B[A[k]+1]);
    }

    // 出力
    for(ll i=0; i<M; i++) {
        cout << ans[i]+1 << endl;
    }
}

int main() {
    // solve3();
    solve4();
    return 0;
}