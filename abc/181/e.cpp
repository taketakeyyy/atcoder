#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N, M;
    cin >> N >> M;
    vector<int> H(N);
    vector<int> W(M);
    for (int i=0; i<N; i++) cin >> H[i];
    for (int i=0; i<M; i++) cin >> W[i];
    sort(H.begin(), H.end());
    sort(W.begin(), W.end());

    /*
    i=0から順に、先生と組む場合の身長差を計算をする
    i=1のときは、しゃくとり法を使えば先生と組む以外の人たちの身長差は一瞬で計算できるO(1)
    先生がどの身長になればよいかは、二分探索で求めればO(logN)
    よって、この計算量はO(NlogN)でいけそう
    */
    vector<int> diffT(N,0);  // 生徒iと、先生との最小の身長差
    for (int i=0; i<N; i++) {
        auto it = lower_bound(W.begin(), W.end(), H[i]);
        if (it == W.begin()) {
            diffT[i] = W[0]-H[i];
        }
        else if (it == W.end()) {
            diffT[i] = H[i]-W.back();
        }
        else {
            diffT[i] = min(abs(H[i]-*it), abs(H[i]-*(it-1)));
        }
    }

    // i=0の生徒が先生とペアになるとき
    int total = 0;
    for (int i=1; 2*i<N; i++) {
        total += H[2*i]-H[2*i-1];
    }
    int ans = total + diffT[0];

    // i=1~N-1の生徒が先生とペアになるときを、しゃくとり法で求める
    for (int i=1; i<N; i++) {
        if (i%2==1) {
            total -= H[i+1] - H[i];
            total += H[i+1] - H[i-1];
            ans = min(ans, total+diffT[i]);
        }
        else {
            total -= H[i] - H[i-2];
            total += H[i-1] - H[i-2];
            ans = min(ans, total+diffT[i]);
        }
    }

    // 出力
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}