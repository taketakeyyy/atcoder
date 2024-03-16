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


// 解説AC(nok0)
// ・(i,j,k)のjに着目する
// ・不変量を考える
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    map<ll,vector<ll>> a2idx; // Aの値のインデックスのリスト
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        a2idx[A[i]].push_back(i);
    }

    // (i,j,k)のjを固定したとき、二分探索でvecの中からjより左の個数と、右の個数を求めて、(i,j,k)の組の個数を求める
    auto count = [&](vector<ll> &vec, ll j) {
        ll left_num = lower_bound(vec.begin(), vec.end(), j) - vec.begin();
        ll right_num = (ll)vec.size() - left_num;
        return left_num * right_num;
    };

    // 不変量を考える。totalはあまり変わらない
    ll total = 0;
    ll ans = 0;
    {// j=1のとき計算
        ll j = 1;
        for(auto[a, vec]: a2idx) {
            total += count(vec, j);
        }

        // A[j]を引く
        ll diff = count(a2idx[A[j]], j);

        ans = total - diff;

        if (A[j] != A[j+1]) {
            total -= count(a2idx[A[j]], j);
            total -= count(a2idx[A[j+1]], j);
        }
        else {
            total -= count(a2idx[A[j]], j);
        }
    }

    for(ll j=2; j<=N-2; j++) {
        if (A[j] != A[j-1]) {
            total += count(a2idx[A[j]], j);
            total += count(a2idx[A[j-1]], j);
        }
        else {
            total += count(a2idx[A[j]], j);
        }
        ll diff = count(a2idx[A[j]], j);
        ans += total - diff;

        if (A[j] != A[j+1]) {
            total -= count(a2idx[A[j]], j);
            total -= count(a2idx[A[j+1]], j);
        }
        else {
            total -= count(a2idx[A[j]], j);
        }
    }
    cout << ans << endl;
}


// 解説動画AC
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // nC3を計算する
    auto nc3 = [&](ll n) {
        return (n*(n-1)*(n-2))/(3*2*1);
    };

    // X*Xの数え上げをする
    // 左から(i,j,k)のkを走査していく
    map<ll,ll> mp; // 各値の分布
    map<ll,ll> sumi; // 各値のiの合計
    ll ans = 0;
    for(ll k=0; k<N; k++) {
        if (k!=0) {
            ans += (k-1)*mp[A[k]] - sumi[A[k]];
        }

        mp[A[k]]++;
        sumi[A[k]] += k;
    }

    // XXXの数え上げをして、答えから引く
    for(auto[key, val]: mp) {
        ans -= nc3(val);
    }

    // 答え
    cout << ans << endl;
}

// 再度解説AC(nok0)
// ・(i,j,k)のjに着目する
// ・不変量を考える
void solve3() {
    ll N; cin >> N;
    vector<ll> A(N);
    map<ll,vector<ll>> a2idx; // Aの値のインデックスのリスト
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        a2idx[A[i]].push_back(i);
    }

    // (i,j,k)のjを固定したとき、二分探索でvecの中からjより左の個数と、右の個数を求めて、(i,j,k)の組の個数を求める
    auto count = [&](vector<ll> &vec, ll j) {
        ll left_num = lower_bound(vec.begin(), vec.end(), j) - vec.begin();
        ll right_num = (ll)vec.size() - left_num;
        return left_num * right_num;
    };

    // 不変量に着目し、足すべき組み合わせの個数が変化したところだけ再計算する
    ll total = 0; // 足すべき組み合わせの個数
    ll ans = 0;
    {// j=1のとき
        ll j = 1;
        for(auto[a, vec]: a2idx) {
            if (A[j]==a) continue;
            total += count(vec, j);
        }
        ans += total;
    }
    {//j=2以降は、変化したところだけ再計算する
        for(ll j=2; j<=N-2; j++) {
            if (A[j-1]!=A[j]) {
                total += count(a2idx[A[j-1]], j);
                total -= count(a2idx[A[j]], j);
            }
            ans += total;
        }
    }
    cout << ans << endl;
}

int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}