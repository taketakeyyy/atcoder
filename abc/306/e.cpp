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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, K, Q; cin >> N >> K >> Q;
    vector<ll> A(N);
    multiset<ll> msK;  // f(A)を計算するための上位K個を保持するデータ構造
    for(ll i=0; i<K; i++) msK.insert(0);
    multiset<ll> msOthers; // 上位K以外を管理
    for(ll i=0; i<N-K; i++) msOthers.insert(0);

    // msKの最小値 < msOthersの最大値 なら入れ替える関数
    auto switch_min_max = [&](ll &ans) {
        if (msOthers.size()==0) { // コーナーケース
            return;
        }

        auto mnit = msK.begin();
        auto mxit = msOthers.end(); mxit--;
        if (*mnit < *mxit) {
            ll mn = *mnit;
            ll mx = *mxit;
            msK.erase(mnit);
            msOthers.erase(mxit);
            msK.insert(mx);
            msOthers.insert(mn);
            ans -= mn; ans += mx;
        }
    };

    vector<ll> answers(Q);
    ll ans = 0; // f(A)の値
    for(ll q=0; q<Q; q++) {
        ll x, y; cin >> x >> y;
        x--;

        // 値の更新
        ll a = A[x];
        A[x] = y;
        if (msK.find(a) != msK.end()) {
            // msK側に削除する値が存在する場合
            msK.erase(msK.find(a));
            msK.insert(y);
            ans-=a; ans+=y;
        }
        else {
            // msOthers側に削除する値が存在する場合
            if (msOthers.size() != 0) { // サイズ0のとき注意
                msOthers.erase(msOthers.find(a));
                msOthers.insert(y);
            }
        }

        // msKの最小値 < msOthersの最大値 なら入れ替える
        switch_min_max(ans);

        answers[q] = ans;
    }

    // 出力
    for(ll q=0; q<Q; q++) cout << answers[q] << endl;
}

int main() {
    solve();
    return 0;
}