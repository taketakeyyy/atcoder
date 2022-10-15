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
    ll N, M; cin >> N >> M;
    vector<vector<ll>> d(M);
    for(ll i=1; i<=N; i++) {
        ll a; cin >> a;
        a += i;
        // 0 <= a+i_x < N が成り立つiを列挙したい
        ll l = (0 <= a) ? 0 : intceil(-a, i);
        ll r = (N <= a) ? 0 : intceil(-(a-N), i);
        r = min(r, M);

        for(ll j=l; j<r; j++) {
            d[j].push_back(a+i*j);
        }
    }

    for(ll mi=0; mi<M; mi++) {
        auto &b = d[mi];
        ll sz = b.size();
        vector<bool> e(sz+1);  // 存在するか
        for(ll i: b) e[i] = true;
        ll ans = 0;
        while(e[ans]) ans++;
        cout << ans << endl;
    }
}

/*
5 6
-2 -2 -5 -7 -15
*/
void solve2() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> opSet(M+1);  // opSet[i] := i回目の操作後の存在する[0,N]までの整数

    for(ll i=1; i<=N; i++) {
        ll a; cin >> a;
        a += i;

        // 0 <= a <= N となる範囲[li, ri]を探す
        ll li, ri;
        if (a>=0 && a<=N) {
            li = 1;
            ri = li + (N-a)/i;
        }
        else if (a < 0){
            li = 1 + intceil(-a, i);
            ll s = a + (li-1) * i;
            ri = li + (N-s)/i;
        }
        else {
            continue;
        }
        ri = min(ri, M);

        for(ll j=li; j<=ri; j++) {
            opSet[j].insert(a+i*(j-1));
        }
    }

    // 出力 O(NM)な感じだがopSet[mi]はスカスカ
    for(ll mi=1; mi<=M; mi++) {
        for(ll mex=0; mex<=N; mex++) {
            if (!opSet[mi].count(mex)) {
                cout << mex << endl;
                break;
            }
        }
    }
}


void solve3() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> opSet(M+1);  // opSet[i] := i回目の操作後の存在する[0,N]までの整数

    for(ll i=1; i<=N; i++) {
        ll a; cin >> a;

        // はじめて 0 <= a <= N となる操作回数の開始地点を探す
        ll sj;
        if ((a+i)>=0 && (a+i)<=N) {
            sj = 1;
        }
        else if ((a+i) < 0){
            sj = 1 + intceil(-(a+i), i);
        }
        else {
            continue;
        }

        // j回目の操作後の整数をopSetに入れていく
        a += sj*i;
        for(ll j=sj; j<=M; j++) {
            if (a > N) break;
            opSet[j].insert(a);
            a += i;
        }
    }

    // 出力 O(NM)な感じだがopSet[mi]はスカスカ
    for(ll mi=1; mi<=M; mi++) {
        for(ll mex=0; mex<=N; mex++) {
            if (!opSet[mi].count(mex)) {
                cout << mex << endl;
                break;
            }
        }
    }
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}