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

// 解説AC
// 【観察1】
// 偶数回目の操作は「詰み」なので、「AC」じゃなくて適当な文字列「Z」でもいい。
//
// 【観察2】
// AAAARCCCCC という文字列に操作をするとき、最大でmin(Aの個数, Cの個数)回操作が可能。
//
// 【観察3】
// ARCAARCCCARRC という長い文字列でどう考えたらいいのか？というと、Rを中心に考えると良い。
//  ↑   ↑    ↑↑
// で、Rの左右にある「A」「C」のうち、小さい方をメモする。
// ARCAARCCCARRC
//  1   2    00
// これにより、数列に置き換えることができる（0は無視）。この数列をXとする。
// X = [1, 2]
// するとこの問題は、以下のように言い換えられる。
// この数列Xにする操作は、
// ・奇数回目のとき、ある要素の値を-1する。0になったらその要素を削除する
// ・偶数回目のとき、ある要素を削除する
//
// X = [1,3,3,3,3] とする。
// どの順番で操作をすればいいのか？
// ・大きい値の要素は奇数回目の操作をする。
// ・小さい値の要素は偶数回目の操作をする。
// というのが良さそう。
// なので、ソートして、奇数回目の操作は後ろ、偶数回目の操作は前からする。ということをすると……
// （1回目）X = [1,3,3,3,2]
// （2回目）X = [ ,3,3,3,2]
// （3回目）X = [ ,3,3,3,1]
// ...とやってしまうので、間違ってしまう。
// やりたいことは、奇数回目は最大値に操作をし、偶数回目は最小値に操作をする。
// 最大値と最小値を更新しながら操作するといえば、平衡二分探索木（multiset）である。
// プライオリティキューでもできるらしい？
//
// 【もう少し観察すると】
// X = [○,○,○,○,○] とする。
// 要素の値の数の合計がS、要素の個数がN個のとき、実は操作回数は、min(S,2N)になる。らしい。
// 【操作回数が2Nになるパターン】
// ○の要素が全部2以上の場合、偶数回目で必ず1個の要素が消えるので、最大操作回数は2Nになる。
// 【操作回数がSになるパターン】
// ○の要素が少なくとも1個が1の場合、...
//
void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    // 新しい配列Xを作る
    vector<ll> X;
    for(ll i=0; i<N; i++) {
        if (S[i] == 'R') {
            ll l=i, r=i;
            ll x = 0;
            while(1) {
                l--; r++;
                if (l<0 || r>=N) break;
                if (S[l]=='A' && S[r]=='C') {
                    x++; continue;
                }
                break;
            }
            if (x == 0) continue;
            X.push_back(x);
            i = r-1;
        }
    }

    // multisetで処理
    multiset<ll> ms;
    for(ll x: X) {
        ms.insert(x);
    }

    // 操作をシミュレーション
    ll ans = 0;
    ll turn = 1;
    while(!ms.empty()) {
        ans++;
        if (turn%2 == 1) {
            // 奇数回目の操作は、最大値を-1し、0になったら削除
            auto it = ms.end(); it--;  // 最大値
            if ((*it)-1 > 0) ms.insert((*it)-1);
            ms.erase(it);
        }
        else {
            // 偶数回目の操作は、最小値を削除する
            ms.erase(ms.begin());
        }
        turn ^= 1;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}