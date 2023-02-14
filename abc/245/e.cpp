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


// WA解法
// 横幅と縦幅が小さい順で貪欲すると、
// チョコ: (1,100), (2,2)
//     箱: (2,2), (2,100)
// でNoになる（本当はYes）
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N), B(N), C(M), D(M);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];
    for(ll i=0; i<M; i++) cin >> C[i];
    for(ll i=0; i<M; i++) cin >> D[i];

    vector<pair<ll,ll>> chocos(N);
    for(ll i=0; i<N; i++) {
        chocos[i] = {A[i], B[i]};
    }
    vector<pair<ll,ll>> box(M);
    for(ll i=0; i<M; i++) {
        box[i] = {C[i], D[i]};
    }

    // 横幅と縦幅が小さい順で貪欲
    sort(chocos.begin(), chocos.end());
    sort(box.begin(), box.end());
    ll i = 0;  // チョコのインデックス
    for(ll m=0; m<M; m++) {
        auto[a,b] = chocos[i];
        auto[c,d] = box[m];
        if (a<=c && b<=d) {
            i++;
            if (i==N) break;
        }
    }

    if (i == N) cout << "Yes" << endl;
    else cout << "No" << endl;
}


// 解説AC
// チョコと箱を2次元座標上にプロットして、x座標を右から左へ平面操作をすることを考える。
// 箱を見つけたら、「すでに見つけた箱の集合」に入れる。
// チョコを見つけたら、そのチョコは「すでに見つけた箱の集合」のどの箱よりもx座標が小さい（以下）であることが保証されているので、y座標のみ考えれば良い。
// 「すでに見つけた箱の集合」の中から、見つけたチョコのy座標以上で、最も小さいy座標を持つ箱を選ぶのが最適。
// これは「すでに見つけた箱の集合」をmultisetで持てば、二分探索で見つけることができ、削除もできる
void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N), B(N), C(M), D(M);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];
    for(ll i=0; i<M; i++) cin >> C[i];
    for(ll i=0; i<M; i++) cin >> D[i];

    vector<tuple<ll,ll,ll>> alls;// (x座標,種別ID,y座標)
    for(ll i=0; i<N; i++) alls.push_back({A[i], 0, B[i]});// チョコ
    for(ll i=0; i<M; i++) alls.push_back({C[i], 1, D[i]});// 箱
    sort(alls.begin(), alls.end());
    // (x座標,種別ID,y座標) とすることで、ソートしたときに箱が必ず右側に来るようになる

    // 右から左へ平面走査する
    multiset<ll> seen_box;  // すでに見つけた箱のy座標
    for(ll i=(ll)alls.size()-1; i>=0; i--) {
        auto[x, id ,y] = alls[i];
        if (id == 1) {
            seen_box.insert(y);
            continue;
        }

        // チョコを見つけた場合
        auto it = seen_box.lower_bound(y);
        if (it == seen_box.end()) { // 最適な箱が見つからなかった場合
            cout << "No" << endl;
            return;
        }
        seen_box.erase(it);
    }
    cout << "Yes" << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}