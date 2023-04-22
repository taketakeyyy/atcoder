#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define intceil(a, b) ((a + (b - 1)) / b)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long, long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x, y); }
void chmin(int& x, int y) { x = min(x, y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = {-1, 0, 1, 0};
vector<ll> vx = {0, 1, 0, -1};

// nC2
ll c2(ll n) { return n * (n - 1) / 2; }

// 解説動画AC
void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        A[i]--;
    }

    vector<ll> cnt(N);  // 分布
    for (ll i = 0; i < N; i++) cnt[A[i]]++;

    ll same = 0;
    for (ll i = 0; i < N; i++) same += c2(cnt[i]);

    // 両端2個減らしたとき、不必要なものだけ削除する（尺取法）
    auto del = [&](ll x) {
        same -= c2(cnt[x]);
        cnt[x]--;
        same += c2(cnt[x]);
    };

    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        // 左端と右端を狭めていく
        ll l = i, r = N - 1 - i;
        if (l >= r) break;
        ans += c2(r - l + 1) - same;
        del(A[l]);
        del(A[r]);
    }

    cout << ans << endl;
}

// 解説AC
// (悪い線の数) = (すべての線の数) - (良い線の数)
void solve2() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        A[i]--;
    }

    // すべての線の本数
    ll ans = 0;
    for (ll i = 2; i <= N; i++) {
        ans += (N - (i - 1)) * (i / 2);
    }

    // 良い線の数を数える
    {
        vector<vector<ll>> pos(N);  // pos[a] := 値aの位置
        for (ll i = 0; i < N; i++) {
            pos[A[i]].push_back(i);
        }

        // min(l+1, N-r) の l+1 が答えになる場合だけ数える
        for (ll l = 0; l < N; l++) {
            ll r = N - l - 1;
            if (l >= r) break;

            ll idx = upper_bound(pos[A[l]].begin(), pos[A[l]].end(), r) -
                     pos[A[l]].begin();
            ll idx2 = upper_bound(pos[A[l]].begin(), pos[A[l]].end(), l) -
                      pos[A[l]].begin();
            ll cnt = idx - idx2;
            ans -= cnt * (l + 1);
        }
    }

    // Aをreverseして再度数える
    {
        reverse(A.begin(), A.end());
        vector<vector<ll>> pos(N);
        for (ll i = 0; i < N; i++) {
            pos[A[i]].push_back(i);
        }

        // min(l+1, N-r) の l+1 が答えになる場合だけ数える
        for (ll l = 0; l < N; l++) {
            ll r = N - l - 2;
            if (l >= r) break;

            ll idx = upper_bound(pos[A[l]].begin(), pos[A[l]].end(), r) -
                     pos[A[l]].begin();
            ll idx2 = upper_bound(pos[A[l]].begin(), pos[A[l]].end(), l) -
                      pos[A[l]].begin();
            ll cnt = idx - idx2;
            ans -= cnt * (l + 1);
        }
    }

    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}