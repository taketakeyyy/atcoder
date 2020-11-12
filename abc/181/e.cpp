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
    vector<int> W(N);
    for (int i=0; i<N; i++) cin >> H[i];
    for (int i=0; i<N; i++) cin >> W[i];
    sort(H.begin(), H.end());
    sort(W.begin(), W.end());

    /*
    あらかじめ隣り合う人との差を計算しておき、（diff[i]）その合計も計算しておく(total)
    すると、先生と組むことになる誰かを選んだら、それ以外の身長の差は一瞬で求まる

    例)i = 0 1 2 3 4
       H = 1 2 3 4 7
    diff={0,1,1,1,3,0 }
    total = 6
    i=2の人が先生と組むことになったら、それ以外の人の身長の差は4(=total-diff[2]-diff[3])
    i=4の人が先生と組むことになったら、それ以外の人の身長の差は3(=total-diff[4]-diff[5])
    i  の人が先生と組むことになったら、それ以外の人の身長の差はx(=total-diff[i]-diff[i+1])

    よって、iの人が先生と組むことになるときのそれ以外の人の身長の差は、O(N)で計算できる。

    iの人が先生と組むときの身長差は、二分探索で求めればよい。

    全体の計算量はO(N*logN)
     */
    vector<int>diff(N+2,0);
    int total = 0;
    for (int i=0; i<N-1; i++) {
        diff[i+1] = H[i]-H[i+1];
        total += H[i]-H[i+1];
    }

    vector<int> diffT(N,0);  // 先生との最小の身長差
    for (int i=0; i<N; i++) {
        // ここでiの人と先生の最小な差を二分探索で求める
    }

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}