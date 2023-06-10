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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll W, H; std::cin >> W >> H;
    ll N; cin >> N;
    vector<pair<ll,ll>> strawberrys(N);
    for(ll i=0; i<N; i++) {
        ll p, q; cin >> p >> q;
        strawberrys[i] = {p,q};
    }
    ll A; cin >> A;
    vector<ll> As(A);
    for(ll i=0; i<A; i++) cin >> As[i];
    ll B; cin >> B;
    vector<ll> Bs(B);
    for(ll i=0; i<B; i++) cin >> Bs[i];

    // 0とH,Wを入れたほうが二分探索する上で便利
    As.push_back(0);
    Bs.push_back(0);
    As.push_back(W);
    Bs.push_back(H);
    sort(As.begin(), As.end());
    sort(Bs.begin(), Bs.end());

    // 各いちごについて、どの縦線と横線に所属するか二分探索する
    map<pair<ll,ll>,ll> cake_mp; // ある区間のピースのいちごの個数
    for(ll i=0; i<N; i++) {
        auto[p, q] = strawberrys[i];
        ll idxA = lower_bound(As.begin(), As.end(), p) - As.begin();
        ll idxB = lower_bound(Bs.begin(), Bs.end(), q) - Bs.begin();
        cake_mp[{idxA, idxB}]++;
    }

    // 最小値を探す
    ll mn_ans = INF;
    if (cake_mp.size() < (A+1)*(B+1)) {
        // いちごが乗ってないピースが存在する場合
        mn_ans = 0;
    }
    else if (cake_mp.size() == (A+1)*(B+1)) {
        // 各ピースに少なくとも1個いちごがある場合、全探索
        for(auto[key, val]: cake_mp) {
            mn_ans = min(mn_ans, val);
        }
    }

    // 最大値を探す
    ll mx_ans = 0;
    for(auto[key, val]: cake_mp) {
        mx_ans = max(mx_ans, val);
    }

    // 出力
    cout << mn_ans << " " << mx_ans << endl;
}


int main() {
    solve();
    return 0;
}