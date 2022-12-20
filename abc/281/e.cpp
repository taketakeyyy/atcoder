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

struct DS {
    ll k;
    ll sum;  // 先頭k個の総和
    multiset<ll> lms, rms;  // 左のグループ, 右のグループ

    DS(ll k_=0) {
        k = k_;
        sum = 0;
    }

    void add(ll x) {
        sum += x;
        lms.insert(x);
        if ((ll)lms.size() <= k) return;

        // 左の最大値を右に移動させる
        auto it = lms.end(); it--; // 左の最大値
        rms.insert(*it);
        sum -= *it;
        lms.erase(it);
    }

    void erase(ll x) {
        if (*lms.rbegin() < x) {
            // xは右にあるとき、削除するだけ
            rms.erase(rms.find(x));
        }
        else {
            // xは左にあるとき
            {  // 左からxを削除する
                auto it = lms.find(x);
                sum -= *it;
                lms.erase(it);
            }
            {  // 右の最小値を左に移動させる
                auto it = rms.begin();
                sum += *it;
                lms.insert(*it);
                rms.erase(it);
            }
        }
    }
};

void solve() {
    ll N, M, K; cin >> N >> M >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 最初のM個
    DS ds(K);
    for(ll m=0; m<M; m++) {
        ds.add(A[m]);
    }

    // クエリ処理
    cout << ds.sum << " ";
    for(ll i=0; i<N-M; i++) {
        // しゃくとり法のように追加と削除をする
        ds.add(A[i+M]);
        ds.erase(A[i]);
        cout << ds.sum << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}