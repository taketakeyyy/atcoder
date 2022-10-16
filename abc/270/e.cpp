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

// x回周回してもOKか？の二分探索用関数
bool bs(ll x, ll K, ll apple1) {
    return (K - x*apple1 >= 0);
}

// 直近で空になるかごまで周回しながら、最後に二分探索する解法
void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    // Bは、次に0になるのが近いかご
    vector<pair<ll,ll>> B(N);  // (りんごの数, かごのインデックス)
    for(ll i=0; i<N; i++) {
        B[i] = {A[i], i};
    }
    sort(B.begin(), B.end());

    // 1周分のりんごは？
    ll apple1 = 0;
    for(ll i=0; i<N; i++) {
        if (B[i].first > 0) apple1++;
    }

    ll lap = 0;  // 周回した回数
    for(ll i=0; i<N; i++) {
        if (B[i].first == 0) continue;

        // 最大で残りのりんご分だけ周回できる
        ll nxtlap = B[i].first - lap;
        if (K <= apple1*nxtlap) {
            // 何回周回できるか二分探索
            ll l = 0;
            ll r = nxtlap;
            while(r-l != 1) {
                ll mid = (r+l)/2;
                if (bs(mid, K, apple1)) l = mid;
                else r = mid;
            }
            if (bs(r, K, apple1)) nxtlap = r;
            else nxtlap = l;

            K -= apple1*nxtlap;
            lap += nxtlap;

            // 残りは順番に見ていき、答えを作る
            for(ll i=0; i<N; i++) {
                if (K >= 1) {
                    if (A[i]-lap >= 1) {
                        A[i] = A[i]-lap-1;
                        K--;
                    }
                    else {
                        A[i] = 0;
                    }
                }
                else {
                    A[i] = max(A[i]-lap, 0LL);
                }
            }
            break;
        }
        else {
            // 残りのりんご分だけ周回できる
            K -= apple1*nxtlap;
            apple1--;
            lap += nxtlap;
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


// x周後、Kの残りを返す二分探索用関数
ll bs2(ll x, ll K, vector<ll> &A) {
    for(ll i=0; i<(ll)A.size(); i++) {
        K -= min(A[i], x);
    }
    return K;
}

// 高橋がx周するのを二分探索で求める解法
void solve2() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll l = 0;
    ll r = 1e12;
    while(r-l != 1) {
        ll mid = (r+l)/2;
        if (bs2(mid, K, A) >= 0) l = mid;
        else r = mid;
    }
    ll x;  // 結局x周する
    if (bs2(r, K, A) >= 0) x = r;
    else x = l;

    // x周することがわかったので、答えを作る
    K = bs2(x, K, A);
    for(ll i=0; i<N; i++) {
        if (K >= 1) {
            if (A[i]-x >= 1) {
                A[i] = A[i]-x-1;
                K--;
            }
            else {
                A[i] = max(A[i]-x, 0LL);
            }
        }
        else {
            A[i] = max(A[i]-x, 0LL);
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}