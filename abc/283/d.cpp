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


void solve() {
    string S; cin >> S;

    // シミュレーションで解く
    map<char,ll> box;
    map<ll, set<char>> block; ll bi=0;
    for(ll i=0; i<(ll)S.size(); i++) {
        if (S[i] == '(') {
            bi++;
            continue;
        }
        else if (S[i] == ')') {
            // ブロックの中の文字を箱から取り出す
            for(char c: block[bi]) {
                box[c] = 0;  // 引きすぎ注意
                // block[bi-1].insert(c);  //これいる?
            }
            bi--;
            continue;
        }
        else {
            // 英小文字
            if (box[S[i]] != 0) {
                // 失神
                cout << "No" << endl;
                return;
            }
            // 箱に入れる
            box[S[i]]++;
            block[bi].insert(S[i]);
            continue;
        }
    }

    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}