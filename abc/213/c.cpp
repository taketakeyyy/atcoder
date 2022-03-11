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


bool columnsort(tuple<ll,ll,ll> const &a, tuple<ll,ll,ll> const &b) {
    ll aw, bw;
    tie(ignore, aw, ignore) = a;
    tie(ignore, bw, ignore) = b;
    return aw < bw;
}

bool idsort(tuple<ll,ll,ll> const &a, tuple<ll,ll,ll> const &b) {
    ll aid, bid;
    tie(ignore, ignore, aid) = a;
    tie(ignore, ignore, bid) = b;
    return aid < bid;
}

void solve() {
    ll H, W, N; cin >> H >> W >> N;
    vector<tuple<ll,ll,ll>> cards(N);  //{h, w, i}
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        cards[i] = {a, b, i};
    }

    // まず行を座標圧縮
    sort(cards.begin(), cards.end());
    ll preh = -1;
    ll nh = 0;
    for(ll i=0; i<N; i++) {
        ll h, w, id;
        tie(h, w, id) = cards[i];

        if (h == preh) {
            cards[i] = {nh, w, id};
            continue;
        }
        else {
            nh++;
            cards[i] = {nh, w, id};
            preh = h;
            continue;
        }
    }

    // 次は列を座標圧縮
    sort(cards.begin(), cards.end(), columnsort);
    ll prew = -1;
    ll nw = 0;
    for(ll i=0; i<N; i++) {
        ll h, w, id;
        tie(h, w, id) = cards[i];

        if (w == prew) {
            cards[i] = {h, nw, id};
            continue;
        }
        else {
            nw++;
            cards[i] = {h, nw, id};
            prew = w;
            continue;
        }
    }

    // id順に出力
    sort(cards.begin(), cards.end(), idsort);
    for(ll i=0; i<N; i++) {
        ll h, w, id;
        tie(h, w, id) = cards[i];
        cout << h << " " << w << endl;
    }
}


int main() {
    solve();
    return 0;
}