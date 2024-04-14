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

// 整数nが、2進数で何桁あるのか返す
ll f(ll n) {
    if (n == 0) return 0;
    ll cnt = 0;
    while(n != 0) {
        cnt++;
        n /= 2;
    }
    return cnt-1;
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // すべて同じ値か？
    {
        ll a = A[0];
        bool is_all_same = true;
        for(ll i=1; i<N; i++) {
            if (a == A[i]) continue;
            is_all_same = false;
            break;
        }
        if (is_all_same) {
            cout << 0 << endl;
            return;
        }
    }

    ll mx_a = A[0];
    ll mx_d = f(A[0]);
    bool is_all_same_digit = true;  // 桁数が同じか
    for(ll i=1; i<N; i++) {
        ll d = f(A[i]);
        if (d == mx_d) {
            mx_a = max(mx_a, A[i]);
        }
        else if (d > mx_d) {
            is_all_same_digit = false;
            mx_d = d;
            mx_a = A[i];
        }
        else {
            is_all_same_digit = false;
        }
    }

    ll ans;
    if (is_all_same_digit) {
        // すべての2進数の桁数が同じなら、最大桁に1をxorする
        ans = mx_a ^ (1<<mx_d);
    }
    else {
        // それ以外なら、一番桁が大きいやつを100..00の形にする
        ans = (1<<mx_d);
    }
    cout << ans << endl;
}


// 解説AC
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    auto f = [&](auto f, const vector<ll>& A, ll k) {
        if (k == -1) return 0;

        vector<ll> l, r;
        for(ll a: A) {
            if (a>>k&1) { // kビット目が1ならば
                // r.push_back(a^(1<<k));
                r.push_back(a);
            }
            else {
                // l.push_back(a);
                l.push_back(a^(1<<k));
            }
        }
        if (l.size() == 0) return f(f,r,k-1);
        if (r.size() == 0) return f(f,l,k-1);
        return min(f(f,l,k-1), f(f,r,k-1)) + (1<<k); // 2^kを足す
    };

    cout << f(f,A,30) << endl;
}


void solve3() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    auto f = [&](auto f, const vector<ll>& A, ll k) {
        if (k == -1) return 0;

        { // 全部0または1ならば
            ll v = A[0]>>k&1;
            bool is_same = true;
            for(ll i=1; i<(ll)A.size(); i++) {
                if (A[i]>>k&1 == v) continue;
                is_same = false;
                break;
            }
            if (is_same) {
                if (v == 0) {
                    return f(f, A, k-1);
                }
                else {
                    vector<ll> B;
                    for(ll i=0; i<(ll)A.size(); i++) B.push_back(A[i]^(1<<k));
                    return f(f, B, k-1);
                }
            }
        }

        // 0と1が混ざってるならば
        vector<ll> l, r;
        for(ll a: A) {
            if (a>>k&1) { // kビット目が1ならば
                r.push_back(a);
            }
            else {
                l.push_back(a^(1<<k));
            }
        }
        if (l.size() == 0) return f(f,r,k-1);
        if (r.size() == 0) return f(f,l,k-1);
        return min(f(f,l,k-1), f(f,r,k-1)) + (1<<k); // 2^kを足す
    };

    cout << f(f,A,30) << endl;
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}