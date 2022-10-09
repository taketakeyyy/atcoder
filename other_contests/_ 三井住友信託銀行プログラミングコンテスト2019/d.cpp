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
    ll N; cin >> N;
    string S; cin >> S;

    // 各桁たかだか10通りしかない。枝刈りすれば全探索いける
    set<string> kinds;  // 作れる暗証番号の種類
    set<char> set1;  // 1文字目の集合
    for(ll i=0; i<N; i++) {
        if ((ll)set1.size()==10) break;
        if (set1.count(S[i])) continue;
        set1.insert(S[i]);
        string s1 = {S[i]};

        set<char> set2;  // 2文字目の集合
        for(ll j=i+1; j<N; j++) {
            if ((ll)set2.size()==10) break;
            if (set2.count(S[j])) continue;
            set2.insert(S[j]);
            string s2 = s1 + S[j];

            set<char> set3;  // 3文字目の集合
            for(ll k=j+1; k<N; k++) {
                if ((ll)set3.size() == 10) break;
                if (set3.count(S[k])) continue;
                set3.insert(S[k]);
                string s3 = s2 + S[k];
                kinds.insert(s3);
            }
        }
    }

    // 出力
    cout << (ll)kinds.size() << endl;
}


int main() {
    solve();
    return 0;
}