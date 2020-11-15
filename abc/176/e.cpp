#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int H, W, M; cin >> H >> W >> M;
    vector<int> HBomb(H, 0);  // WBomb[i] := i行に爆弾を置いたら破壊できる爆破対象の数
    vector<int> WBomb(W, 0);  // WBomb[i] := i列に爆弾を置いたら破壊できる爆破対象の数
    // vector<vector<int>> grid(H, vector<int>(W, 0));  // 爆破対象があるところは1, それ以外は0  // grid[300000][300000] はでかすぎて確保できないのでRE？
    map<pair<int, int>, bool> bpos;  // 爆破対象がある座標
    for (int i=0; i<M; i++) {
        int h, w;
        cin >> h >> w;
        h--; w--;
        HBomb[h]++; WBomb[w]++;
        bpos[pair<int, int>(h,w)] = true;
    }

    // 最も爆破できるh座標候補を探す
    vector<int> hCands;
    auto it_hmx = max_element(HBomb.begin(), HBomb.end());
    int h_mx = *it_hmx;
    int h = it_hmx-HBomb.begin();
    hCands.push_back(h);
    for (int i=h+1; i<H; i++) {
        if (HBomb[i] == h_mx) hCands.push_back(i);
    }

    // 最も爆破できるw座標候補を探す
    vector<int> wCands;
    auto it_wmx = max_element(WBomb.begin(), WBomb.end());
    int w_mx = *it_wmx;
    int w = it_wmx-WBomb.begin();
    wCands.push_back(w);
    for (int i=w+1; i<W; i++) {
        if (WBomb[i] == w_mx) wCands.push_back(i);
    }

    /***
     * hCandsとwCandsの交点のどれかが答えになる。
     * 交点に爆破対象があると1個重複分少ない爆破になるので、交点に爆破対象がない座標を探す
     * 二重ループだが、爆破対象はM個しかないので、高々M回の走査になる
     **/
    bool is_found = false;  // 交点に爆破対象がない座標が存在するか？
    for (int i : hCands) {
        for (int j: wCands) {
            if (bpos.count(pair<int, int>(i,j))) continue;
            is_found = true;
            break;
        }
        if (is_found) break;
    }

    // 出力
    int ans = h_mx + w_mx;
    if (is_found) {
        cout << ans << endl;
    }
    else {
        cout << ans-1 << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}