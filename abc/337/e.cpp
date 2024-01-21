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

// 解説AC
// 人がM人いたら、2^M通りの情報を表すことができる。
// 翌日どの人が腹を壊したかの情報Sは、2^M通りありうる。
// なので、M人にうまくジュースを飲ませることで、2^M本までのジュースの中から一意に絞り込められる
void solve() {
    ll N; cin >> N;

    ll M = ceil(log2(N));

    // 数字bitを、長さMの文字列にする
    auto to_string = [&](ll bit) {
        string str;
        for(ll d=0; d<M; d++) {
            if (bit>>d&1) {
                str.push_back('1');
            }
            else {
                str.push_back('0');
            }
        }
        return str;
    };

    // juice[i] := i本目のジュースを表す文字列
    vector<string> juice(N+1);
    {
        ll bit = 0;
        for(ll i=1; i<=N; i++) {
            juice[i] = to_string(bit);
            bit++;
        }
    }

    // friends[i] := i番目の友人に飲ませるジュースのリスト
    vector<vector<ll>> friends(M+1);
    for(ll i=1; i<=N; i++) { // ジュースi
        for(ll j=1; j<=M; j++) { // 友人j
            if (juice[i][j-1]=='1') friends[j].push_back(i);
        }
    }

    // 友人の数を出力する
    cout << M << endl;
    flush(cout);

    // i番目の友人に飲ませるジュース情報を出力する
    for(ll i=1; i<=M; i++) {
        ll K = friends[i].size();
        cout << K << " ";
        for(ll k=0; k<K; k++) {
            cout << friends[i][k] << " ";
        }
        cout << endl;
    }
    flush(cout);

    // ジャッジから、翌日にお腹を壊した人の情報を受け取る
    string S; cin >> S;

    // どのジュースが腐ったジュースか？
    for(ll i=1; i<=N; i++) {
        if (juice[i] == S) {
            cout << i << endl;
            return;
        }
    }
}


int main() {
    solve();
    return 0;
}