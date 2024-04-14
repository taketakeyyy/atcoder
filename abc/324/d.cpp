#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// TLE permutation重すぎ
void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    // 平方数列挙
    set<ll> square_set;
    for(ll i=1; i*i<1e14; i++) {
        square_set.insert(i*i);
    }

    ll ans = 0;
    // permutationは 13! = 6e9通りくらい（数字は0~9しかないけどそんくらい？）
    sort(S.begin(), S.end());
    do {
        ll num = stoll(S);
        if (square_set.count(num)) {
            ans++;
        }
    }while (next_permutation(S.begin(), S.end()));
    cout << ans << endl;
}


// 解説AC
void solve2() {
    ll N; cin >> N;
    string S; cin >> S;
    sort(S.begin(), S.end());

    // 平方数列挙
    ll ans = 0;
    for(ll i=0; i*i<(ll)pow(10,N); i++) {
        string T = to_string(i*i);
        T.resize(N, '0'); // 桁数を揃える（新しく増えた要素は'0'で埋める）
        sort(T.begin(), T.end()); // （leading-zeroになる）
        if (S == T) ans++;
    }
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}