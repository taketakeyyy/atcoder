#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
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



struct Container {
public:
    Container* next;
    Container* pre;
    ll val;
    Container(): next(nullptr), pre(nullptr), val(-1) {}
};

void solve() {
    ll N, Q; cin >> N >> Q;
    vector<Container*> table_head(N); // table_head[i] := テーブルiの指している先頭のコンテナのアドレス
    vector<Container*> table_tail(N); // table_tail[i] := テーブルiの指している最後尾のコンテナのアドレス
    vector<Container> dammy(N); // ダミーコンテナ
    vector<Container> C(N); // コンテナ
    map<ll,Container*> Cptr; // Cptr[i] := コンテナiのアドレス
    for(ll i=0; i<N; i++) {
        C[i] = Container();
        C[i].val = i;
        Cptr[i] = &C[i];
    }
    for(ll i=0; i<N; i++) {
        table_head[i] = &dammy[i];
        table_head[i]->next = &C[i];
        C[i].pre = table_head[i];
        table_tail[i] = &C[i];
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll f, t, x; cin >> f >> t >> x;
        f--; t--; x--;

        Container* target = Cptr[x];
        Container* tail_f = table_tail[f];

        target->pre->next = nullptr;
        table_tail[f] = target->pre;

        target->pre = table_tail[t];
        table_tail[t]->next = target;
        table_tail[t] = tail_f;
    }

    // それぞれのコンテナがどの机の上にあるのか？
    vector<ll> ans(N);
    for(ll t=0; t<N; t++) {
        Container *now = table_head[t];
        while(now->next != nullptr) {
            now = now->next;
            ans[now->val] = t;
        }
    }

    // 答え
    for(ll v: ans) cout << v+1 << endl;
}


int main() {
    solve();
    return 0;
}