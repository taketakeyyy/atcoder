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


void solve() {
    // 配列Aを、登場順に番号を振り分け直すやり方
    // 配列Bもそれに合わせて番号を振り直す
    ll N; cin >> N;
    vector<ll> A(N), B(N);
    map<ll,ll> mp;
    ll id = 1;
    // dpA[i] := i番目までの集合のサイズ
    set<ll> setA;
    vector<ll> dpA(N);
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (mp[a] == 0) {
            mp[a] = id;
            id++;
        }
        A[i] = mp[a];
        setA.insert(mp[a]);
        dpA[i] = setA.size();
    }
    // dpB[i] := i番目までの(集合のサイズ, 最大値)
    set<ll> setB;
    vector<pair<ll,ll>> dpB(N);
    for(ll i=0; i<N; i++) {
        ll b; cin >> b;
        if (mp[b] == 0) {
            mp[b] = id;
            id++;
        }
        B[i] = mp[b];
        setB.insert(mp[b]);
        dpB[i] = {setB.size(), *(--setB.end())};
    }

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll x, y; cin >> x >> y; x--; y--;
        if ((dpA[x] == dpB[y].first) && (dpA[x] == dpB[y].second)) {
            // 集合のサイズが等しく、最大値も等しかったらYes
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}

void solve2() {
    // Zobrist Hashing を使って解く
    // 参考：https://qiita.com/u2dayo/items/5c021016d11f125e3c0b#e%E5%95%8F%E9%A1%8Cprefix-equality
    // メルセンヌ・ツイスター
    random_device seed_gen;
    mt19937 engine(seed_gen());
    uniform_int_distribution<> dist(1, INT_MAX);  // 一様分布（離散）

    ll N; cin >> N;
    vector<ll> A(N), B(N);
    map<ll,ll> hash;
    set<ll> setA;
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (setA.count(a)) {
            A[i] = 0;
        }
        else {
            if (hash[a] == 0) {
                ll r = dist(engine);
                hash[a] = r;
            }
            setA.insert(a);
            A[i] = a;
        }
    }
    set<ll> setB;
    for(ll i=0; i<N; i++) {
        ll b; cin >> b;
        if (setB.count(b)) {
            B[i] = 0;
        }
        else {
            if (hash[b] == 0) {
                ll r = dist(engine);
                hash[b] = r;
            }
            setB.insert(b);
            B[i] = b;
        }
    }

    // 配列A,Bをハッシュ値に置き換える
    for(ll i=0; i<N; i++) {
        if (A[i] != 0) {
            A[i] = hash[A[i]];
        }
        if (B[i] != 0) {
            B[i] = hash[B[i]];
        }
    }

    // 配列A,Bそれぞれ累積xorをとる。
    // 累積xorが一致 ⇒ 集合が一致する
    vector<ll> ruisekiA(N), ruisekiB(N);
    ruisekiA[0] = A[0];
    ruisekiB[0] = B[0];
    for(ll i=1; i<N; i++) {
        ruisekiA[i] = ruisekiA[i-1] ^ A[i];
        ruisekiB[i] = ruisekiB[i-1] ^ B[i];
    }

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll x, y; cin >> x >> y; x--; y--;
        if (ruisekiA[x] == ruisekiB[y]) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}