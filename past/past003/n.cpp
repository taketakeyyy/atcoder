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
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) A[i] = i;

    // swap操作をする
    auto do_swap = [&](ll i, set<ll> &Tset) -> void {
        swap(A[i],A[i+1]);
        if (A[i]<A[i+1]) Tset.erase(i);
        else if (A[i]>A[i+1]) Tset.insert(i);
        if (i-1>=0 and A[i-1]>A[i]) Tset.insert(i-1);
        else if (i-1>=0 and A[i-1]<A[i]) Tset.erase(i-1);
        if (i+2<N and A[i+1]>A[i+2]) Tset.insert(i+1);
        else if (i+2<N and A[i+1]<A[i+2]) Tset.erase(i+1);
    };

    set<ll> Tset; // A[i] > A[i+1] となっているiの集合
    for(ll q=0; q<Q; q++) {
        ll t, x, y; cin >> t >> x >> y;
        x--; y--;
        if (t == 1) {
            // swap
            do_swap(x, Tset);
        }
        else {
            // [x,y]の区間をソートする
            while(1) {
                auto itr = Tset.lower_bound(x);
                if (itr == Tset.end()) break;
                ll target = *itr;
                if (target<x or target>=y) break;
                do_swap(target, Tset);
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << A[i]+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}