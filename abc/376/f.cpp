#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
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

ll MOD;
/** 自動でMODをとるModInt型
 *
 * Usage
 *   // 基本的な使い方
 *   mint a, b;
 *   a = 100;
 *   b = a + MOD;
 *   // istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる
 *   cout << b << endl;  // 100
 *   // 明示的にlong long型を出力するときは.xを参照する
 *   cout << b.x << endl;  // 100
 *
 * References
 *  https://youtu.be/L8grWxBlIZ4?t=9858
 *  https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
 *  https://youtu.be/8uowVvQ_-Mo?t=1329 : division
 */
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
    bool operator<=(const mint a) const { return mint(*this) <= a; }
    bool operator<(const mint a) const { return mint(*this) < a; }
    bool operator>=(const mint a) const { return mint(*this) >= a; }
    bool operator>(const mint a) const { return mint(*this) > a; }
    bool operator==(const mint a) const { return mint(*this) == a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


/**
 * @brief pair用ハッシュ
 *
 * @example
 *  // ハッシュ作成
 *  pair<int,int> p = {1,2};
 *  HashPair hp = HashPair();
 *  int hash1 = hp(p);
 *
 *  // unordered_mapのキーにpair<int,int>を指定する
 *  unordered_map<pair<int,int>, int, HashPair> mp;
 */
struct HashPair {
    static size_t m_hash_random; // 実行時のランダム要素を入れることで、ハッシュ衝突のhackを避ける

    template<class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        size_t seed = 0;
        seed ^= hash1 + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= hash2 + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= m_hash_random + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};
size_t HashPair::m_hash_random = (size_t)random_device()();

void solve() {
    ll N, Q; cin >> N >> Q;
    MOD = N;

    // AからBへ行くコスト（左回り）
    auto calc_cost_left = [&] (ll A, ll B) {
        ll res = A-B;
        if (res >= 0) return res;
        res = A + (N-B);
        return res;
    };

    // AからBへ行くコスト（右回り）
    auto calc_cost_right = [&] (ll A, ll B) {
        ll res = B-A;
        if (res >= 0) return res;
        res = N-A + B;
        return res;
    };

    // 時計左回りに移動させる
    auto opt_left = [&](ll H, ll T, unordered_map<pair<ll,ll>,ll,HashPair> &dp, unordered_map<pair<ll,ll>,ll,HashPair> &newdp) -> void {
        for(auto[key, cost]: dp) {
            auto[l, r] = key;

            ll mH = l; // moveHand
            ll aH = r; // anotherHand
            if (H == 'R') {
                swap(mH,aH);
            }

            ll ncost;
            ll nmH;
            ll naH;
            if ((T==aH) or (T<aH and aH<mH) or (aH<mH and mH<T) or (mH<T and T<aH)) {
                // 移動途中でもう一方の手に衝突する場合
                mint aT = T; aT -= 1;
                ncost = cost + calc_cost_left(aH, aT.x) + calc_cost_left(mH, T);
                naH = aT.x;
                nmH = T;
            }
            else {
                // 移動途中でもう一方の手に衝突しない場合
                ncost = cost + calc_cost_left(mH, T);
                naH = aH;
                nmH = T;
            }

            ll nl = nmH;
            ll nr = naH;
            if (H == 'R') {
                swap(nl,nr);
            }
            if (newdp.contains({nl,nr}) == false) newdp[{nl,nr}] = ncost;
            else chmin(newdp[{nl,nr}], ncost);
        }
    };

    // 時計右回りに移動させる
    auto opt_right = [&](ll H, ll T, unordered_map<pair<ll,ll>,ll,HashPair> &dp, unordered_map<pair<ll,ll>,ll,HashPair> &newdp) -> void {
        for(auto[key, cost]: dp) {
            auto[l, r] = key;

            ll mH = l; // moveHand
            ll aH = r; // anotherHand
            if (H == 'R') {
                swap(mH,aH);
            }

            ll ncost;
            ll nmH;
            ll naH;
            if ((T==aH) or (mH<aH and aH<T) or (aH<T and T<mH) or (T<mH and mH<aH)){
                // 移動途中でもう一方の手に衝突する場合
                mint aT = T; aT+=1;
                ncost = cost + calc_cost_right(aH, aT.x) + calc_cost_right(mH, T);
                naH = aT.x;
                nmH = T;
            }
            else {
                // 移動途中でもう一方の手に衝突しない場合
                ncost = cost + calc_cost_right(mH, T);
                naH = aH;
                nmH = T;
            }

            ll nl = nmH;
            ll nr = naH;
            if (H == 'R') {
                swap(nl,nr);
            }
            if (newdp.contains({nl,nr}) == false) newdp[{nl,nr}] = ncost;
            else chmin(newdp[{nl,nr}], ncost);
        }
    };

    // dp[i][(l,r)] := 現在i回目の操作で、(l,r)にいるときの、最小コスト
    unordered_map<pair<ll,ll>,ll,HashPair> dp;
    dp[{0,1}] = 0;
    for(ll q=0; q<Q; q++) {
        char h; cin >> h;
        ll t; cin >> t;
        t--;

        unordered_map<pair<ll,ll>,ll,HashPair> newdp;
        opt_left(h,t,dp,newdp);
        opt_right(h,t,dp,newdp);
        swap(newdp,dp);
    }

    // 答え
    ll ans = INF;
    for(auto[key, val]: dp) {
        chmin(ans, val);
    }
    cout << ans << endl;
}


// cyclic shift（循環シフト）を使って、場合分けを減らす
void solve2() {
    ll N, Q; cin >> N >> Q;

    // dp[i] := 動かす手とは異なるもう一方の手がiにいるときの、最小コスト
    vector<ll> dp(N, INF);
    char preH = 'L'; // 前回動かした手
    ll preT = 0; // 前回動かした手がいる場所
    dp[1] = 0; // もう一方の手は1にいるからね
    for(ll q=0; q<Q; q++) {
        char h; cin >> h;
        ll t; cin >> t;
        t--;

        // 最後にいた場所が0になるようにrotate
        rotate(dp.begin(), dp.begin()+preT, dp.end());
        t = (t-preT+N)%N;
        vector<ll> newdp(N, INF);

        for(ll side=0; side<2; side++) { // 最初は時計回り、次は反時計回り
            for(ll i=0; i<N; i++) {
                if (dp[i] == INF) continue;
                if (h == preH) {
                    if (i <= t) { // 手同士が衝突する
                        chmin(newdp[(t+1)%N], dp[i]+(t+(t+1)-i));
                    }
                    else { // 手同士が衝突しない
                        chmin(newdp[i], dp[i]+t);
                    }
                }
                else {
                    if (i <= t) { // 手同士が衝突しない
                        chmin(newdp[0], dp[i]+(t-i));
                    }
                    else { // 手同士が衝突する
                        chmin(newdp[(t+1)%N], dp[i]+((N-i+t)+(t+1)));
                    }
                }
            }

            // 反時計回りにする
            reverse(newdp.begin()+1, newdp.end());
            reverse(dp.begin()+1, dp.end());
            t = (N-t)%N;
        }
        swap(newdp, dp);
        rotate(dp.begin(), dp.begin()+(N-preT), dp.end());
        preH = h;
        preT = (preT+t)%N;
    }

    // 答え
    ll ans = INF;
    for(ll i=0; i<N; i++) chmin(ans, dp[i]);
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}