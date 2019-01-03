#include <iostream>

using namespace std;

void solve(){
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

int main(){
    solve();
}