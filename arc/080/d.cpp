#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    ll H, W, N; cin >> H >> W >> N;
    vector<ll> As(N);
    for(ll i=0; i<N; i++) cin >> As[i];

    // 座標(0,0)から、渦を巻くように塗っていけばいいのでは？
    vector<vector<ll>>ans(H, vector<ll>(W, -1));
    ll k = 0;
    ll cnt = 0, total_cnt = 0;
    ll h=0, w=0;
    ll direct = 0;  // 0:右, 1:下, 2左, 3:上
    while (1) {
        ans[h][w] = k+1;
        cnt++; total_cnt++;

        if (total_cnt == H*W) break;

        if (cnt == As[k]) {
            k++; cnt=0;
        }

        // 次のマスへ移動する
        if (direct==0) {
            // 右へ移動中
            if (w+1==W || ans[h][w+1]!=-1) {
                direct++;
                h++;
            }
            else {
                w++;
            }
        }
        else if (direct==1) {
            // 下へ移動中
            if (h+1==H || ans[h+1][w]!=-1) {
                direct++;
                w--;
            }
            else {
                h++;
            }
        }
        else if (direct==2) {
            // 左へ移動中
            if (w-1==-1 || ans[h][w-1]!=-1) {
                direct++;
                h--;
            }
            else {
                w--;
            }
        }
        else {
            // 上へ移動中
            if (h-1==-1 || ans[h-1][w]!=-1) {
                direct = 0;
                w++;
            }
            else {
                h--;
            }
        }
    }

    // 出力
    for(ll h=0; h<H; h++) {
        for (ll w=0; w<W; w++) {
            cout << ans[h][w];
            if (w!=W-1) cout << " ";
        }
        cout << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}