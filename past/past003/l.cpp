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


void solve() {
    ll N; cin >> N;
    vector<deque<ll>> T(N);
    for(ll i=0; i<N; i++) {
        ll K; cin >> K;
        for(ll k=0; k<K; k++) {
            ll t; cin >> t;
            T[i].push_back(t);
        }
    }

    vector<set<ll>> Tset(N); // Tset[i] := i番目の棚の、手前2個の消費期限の集合
    vector<set<pair<ll,ll>>> Allset(2); // Allset[0] := すべての棚の、手前1個の(消費期限,棚番号)
                                        // Allset[1] := すべての棚の、手前2個の(消費期限,棚番号)
    for(ll i=0; i<N; i++) {
        Allset[0].insert({T[i][0],i});
        Allset[1].insert({T[i][0],i});
        Tset[i].insert(T[i][0]);
        T[i].pop_front();
        if (T[i].empty() == false) {
            Allset[1].insert({T[i].front(),i});
            Tset[i].insert(T[i][0]);
            T[i].pop_front();
        }
    }

    ll M; cin >> M;
    vector<ll> ans(M);
    for(ll i=0; i<M; i++) {
        ll a; cin >> a;
        if (a == 1) {
            auto itr = Allset[0].end();
            itr--;
            ll expire_date = itr->first;
            ll tana_idx = itr->second;
            Allset[0].erase(itr);
            Allset[1].erase({expire_date, tana_idx});
            Tset[tana_idx].erase(expire_date);
            ans[i] = expire_date;

            // 新しく棚からAllsetに入れる
            Allset[0].insert({*(Tset[tana_idx].begin()),tana_idx});
            if (T[tana_idx].empty() == false) {
                Allset[1].insert({T[tana_idx].front(),tana_idx});
                Tset[tana_idx].insert(T[tana_idx].front());
                T[tana_idx].pop_front();
            }
            continue;
        }
        else {
            auto itr = Allset[1].end();
            itr--;
            ll expire_date = itr->first;
            ll tana_idx = itr->second;
            Allset[1].erase(itr);
            Tset[tana_idx].erase(expire_date);
            ans[i] = expire_date;

            // 新しく棚からAllsetに入れる
            if (Allset[0].contains({expire_date, tana_idx})) {
                Allset[0].erase({expire_date, tana_idx});
                Allset[0].insert({*(Tset[tana_idx].begin()),tana_idx});
                if (T[tana_idx].empty() == false) {
                    Allset[1].insert({T[tana_idx].front(),tana_idx});
                    Tset[tana_idx].insert(T[tana_idx].front());
                    T[tana_idx].pop_front();
                }
            }
            else {
                if (T[tana_idx].empty() == false) {
                    Allset[1].insert({T[tana_idx].front(),tana_idx});
                    Tset[tana_idx].insert(T[tana_idx].front());
                    T[tana_idx].pop_front();
                }
            }
            continue;
        }
    }

    // 答え
    for(ll i=0; i<M; i++) cout << ans[i] << endl;
}


int main() {
    solve();
    return 0;
}