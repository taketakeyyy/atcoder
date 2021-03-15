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


void solve() {
    ll N; cin >> N;
    vector<ll>D(N);
    rep(i,N) cin >> D[i];

    if (N==1) {
        cout << D[0] << endl;
        return;
    }

    map<ll,ll>mp;
    vector<ll>time;  // 確定している時刻
    set<ll> time_set;
    time.push_back(0);  // 高橋
    mp[0]++;
    for(int i=0; i<N; i++) {
        mp[D[i]]++;
        if (D[i]==12) {
            time.push_back(12);
        }
        if (mp[D[i]]==2) {
            time.push_back(D[i]);
            time.push_back(24-D[i]);
            if (D[i]==0 || D[i]==12) {
                // 0時と12時は2人いたら差は0で確定
                cout << 0 << endl;
                return;
            }
        }
        if (mp[D[i]]==3) {
            // 3人D[i]がいたら、差は0で確定
            cout << 0 << endl;
            return;
        }
    }

    vector<ll> unsettle;  // 未確定の時刻たち
    for(int i=0; i<N; i++) {
        if (mp[D[i]]!=1) continue;
        if (D[i]==0 || D[i]==12) continue;
        unsettle.push_back(D[i]);
    }

    // 未確定の時刻は全探索する
    ll ans = 0;
    for(int bit=0; bit<1<<(int)unsettle.size(); bit++) {
        vector<ll> new_time = time;
        for(int d=0; d<(int)unsettle.size(); d++) {
            if (bit>>d&1) {
                new_time.push_back(unsettle[d]);
            }
            else {
                new_time.push_back(24-unsettle[d]);
            }
        }
        sort(new_time.begin(), new_time.end());

        ll ret = 24 - new_time[new_time.size()-1];  // 高橋との差を忘れずに
        for(int i=1; i<(int)new_time.size(); i++) {
            ret = min(ret, new_time[i]-new_time[i-1]);
        }
        ans = max(ans, ret);
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}