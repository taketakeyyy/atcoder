#include <iostream>

using namespace std;

void solve1(){
    int N;
    cin >> N;

    int ans = 0;
    for(int n=1; n<=N; n++){
        if(n%2 == 0){ continue; }

        // 約数がちょうど8このものを探す
        int yakusu_count = 0;
        for(int i=1; i<=n; i++){
            if(n%i == 0){ yakusu_count++; }
        }

        if(yakusu_count == 8){
            ans++;
        }
    }

    cout << ans << endl;
    return;
}

void solve2() {
    int N; cin >> N;
    int ans = 0;
    for(int n=1; n<=N; n++) {
        if (n%2 == 0) continue;

        // 約数列挙
        int cnt = 0;
        for(int i=1; i*i<=n; i++) {
            if (n%i==0) {
                cnt++;
                if (i != n/i) cnt++;
            }
        }

        if (cnt == 8) ans++;
    }

    // 出力
    cout << ans << endl;
}

int main(){
    // solve1();
    solve2();
}