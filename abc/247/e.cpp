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


// 区間[L,R]はY未満で、Y以上X以下の値
// Y未満、Xより大きい値が入っていたらダメ
// 数列をY以上X以下の範囲で区切って、範囲外の数字は捨てる
// 包除原理または尺取法で解ける
// 包除原理で解く
// 「含まない列」は、「含む列」より数えるのが簡単
// (XとYを含む数列) = (全ての数列) - (Xを含まない数列) - (Yを含まない数列) + (XとYを含まない数列)
void solve() {
    ll N, X, Y; cin >> N >> X >> Y;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) { cin >> A[i]; }

    vector<vector<ll>> B;
    vector<ll> v;
    for(ll i=0; i<N; i++) {
        ll a = A[i];
        if (Y<=a && a<=X) {
            v.push_back(a);
        }
        else {
            B.push_back(v);
            v.clear();
        }
    }
    B.push_back(v);

    // 各Y以上X以下の数列について処理
    ll ans = 0;
    for(auto v: B) {
        ll sz = (ll)v.size();
        // 全集合
        ans += sz*(sz+1) / 2;
        { // Xを含まない数列
            ll cnt = 0;
            for(ll i=0; i<sz; i++) {
                ll a = v[i];
                if (a == X) {
                    ans -= cnt*(cnt+1)/2;
                    cnt = 0;
                }
                else {
                    cnt++;
                }
            }
            ans -= cnt*(cnt+1)/2;
        }
        { // Yを含まない数列
            ll cnt = 0;
            for(ll i=0; i<sz; i++) {
                ll a = v[i];
                if (a == Y) {
                    ans -= cnt*(cnt+1)/2;
                    cnt = 0;
                }
                else {
                    cnt++;
                }
            }
            ans -= cnt*(cnt+1)/2;
        }
        { // XとYを含まない数列
            ll cnt = 0;
            for(ll i=0; i<sz; i++) {
                ll a = v[i];
                if (a == Y || a == X) {
                    ans += cnt*(cnt+1)/2;
                    cnt = 0;
                }
                else {
                    cnt++;
                }
            }
            ans += cnt*(cnt+1)/2;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}