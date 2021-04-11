#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    vector<string> S(3);
    cin >> S[0];
    cin >> S[1];
    cin >> S[2];
    map<char, ll> mp;  // 文字に対する係数

    // S[0] + S[1] - S[2] = 0 を満たすので、そのように各文字の係数を作っていく
    for(int j=0; j<2; j++) {
        ll base = 1;
        for(int i=S[j].size()-1; i>=0; i--) {
            mp[S[j][i]] += base;
            base *= 10;
        }
    }

    ll base = 1;
    for(int i=S[2].size()-1; i>=0; i--) {
        mp[S[2][i]] -= base;
        base *= 10;
    }

    // 文字種が11文字以上だったら、ありえない
    if (mp.size() >= 11) {
        cout << "UNSOLVABLE" << endl;
        return;
    }

    // 各文字に0~9のどれが入るのか、全探索する
    vector<ll> data(10);
    iota(data.begin(), data.end(), 0);  // 0~9を順に入れる
    map<char, ll> ans;  // どの文字になんの数字が割り当てられたか
    do {  // 高々10!(=3*10^6)ステップ
        ll i = 0;
        ll total = 0;
        for(auto [key, value]: mp) {
            if (data[i]==0) {
                if (S[0][0]==key || S[1][0]==key || S[2][0]==key) {
                    // 文字の最初が0はダメ
                    total = -1;
                    break;
                }
            }
            total += value*data[i];
            i++;
        }

        if (total == 0) {
            // 条件成立!
            // どの文字になんの数字が割り当てられたのか確認する
            i = 0;
            for(auto [key, value]: mp) {
                ans[key] = data[i];
                i++;
            }
            // 答えを出力する
            for(int j=0; j<3; j++) {
                for(int k=0; k<(int)S[j].size(); k++) {
                    cout << ans[S[j][k]];
                }
                cout << endl;
            }
            return;
        }
    } while(next_permutation(data.begin(), data.end()));

    cout << "UNSOLVABLE" << endl;
}


int main() {
    solve();
    return 0;
}