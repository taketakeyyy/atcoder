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


bool comp(const pair<ll,ll> &p1, const pair<ll,ll> &p2) {
    if (p1.first == p2.first) {
        return (p1.second < p2.second);
    }
    return p1.first > p2.first;
}

void solve() {
    ll N, X, Y, Z; cin >> N >> X >> Y >> Z;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) { cin >> A[i]; }
    for(ll i=0; i<N; i++) { cin >> B[i]; }

    vector<pair<ll,ll>> Math(N);  // 数学の点数が高い順
    vector<pair<ll,ll>> Eng(N);  // 英語の点数が高い順
    vector<pair<ll,ll>> Sum(N);  // 合計点が高い順
    for(ll i=0; i<N; i++) {
        ll a = A[i];
        ll b = B[i];
        Math[i] = {a, i};
        Eng[i] = {b, i};
        Sum[i] = {a+b, i};
    }
    // 点数が高い順にソート
    sort(Math.begin(), Math.end(), comp);
    sort(Eng.begin(), Eng.end(), comp);
    sort(Sum.begin(), Sum.end(), comp);

    // 合格者を決めていく
    vector<ll> Ans;
    set<ll> done;  // すでに合格したものの受験番号
    ll cnt = 0;  // 定員

    // X
    cnt = 0;
    for(ll i=0; i<N; i++) {
        if (cnt == X) { break; }
        ll id = Math[i].second;
        done.insert(id);
        Ans.push_back(id);
        cnt++;
    }
    // Y
    cnt = 0;
    for(ll i=0; i<N; i++) {
        if (cnt == Y) { break; }
        ll id = Eng[i].second;
        if (done.count(id)) { continue; }
        done.insert(id);
        Ans.push_back(id);
        cnt++;
    }
    // Z
    cnt = 0;
    for(ll i=0; i<N; i++) {
        if (cnt == Z) { break; }
        ll id = Sum[i].second;
        if (done.count(id)) { continue; }
        done.insert(id);
        Ans.push_back(id);
        cnt++;
    }

    // 受験番号を小さい順に出力
    sort(Ans.begin(), Ans.end());
    for(ll i=0; i<Ans.size(); i++) {
        cout << Ans[i]+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}