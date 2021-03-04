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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    // 学生の点数S[i]を降順にソートすると、k人以下となるような最小のボーダーラインは、
    // * S[k-1]==S[k]のとき、 S[k-1]+1
    // * S[k-1]!=S[k]のとき、 S[k]+1
    // ただし学生が0点のときや、k>S.size()のコーナーケースに注意
    ll N; cin >> N;
    vector<ll>S;
    for(int i=0; i<N; i++) {
        ll s; cin >> s;
        if (s==0) continue;
        S.push_back(s);
    }
    sort(S.begin(), S.end(), greater<ll>());
    ll Q; cin >> Q;
    for(int i=0; i<Q; i++) {
        ll k;
        cin >> k;

        if (S.size()==0) {  // 全員0点だった
            cout << 0 << endl;
            continue;
        }
        if (k>=(ll)S.size()) {  // 全員選抜してもいいなら
            cout << 0 << endl;
            continue;
        }
        if (k==0) {  // 誰も選抜したらダメなら
            cout << S[0]+1 << endl;
            continue;
        }
        if (S[k-1]==S[k]) {
            cout << S[k]+1 << endl;  // 限界の収容人数よりかは空きがでるが、しょうがない
            continue;
        }
        cout << S[k]+1 << endl;
        continue;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}