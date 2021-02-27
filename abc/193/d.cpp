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

ll K;
string S, T;
bool battle(map<ll,ll>mp1, map<ll,ll>mp2, ll i, ll j) {
    ll taka=0, aoki=0;
    mp1[i]++; mp2[j]++;
    for(ll i=1; i<=9; i++) {
        if (mp1[i]==0) {
            taka += i;
        }
        else {
            taka += i*(ll)pow(10, mp1[i]);
        }
    }
    for(ll i=1; i<=9; i++) {
        if (mp2[i]==0) {
            aoki += i;
        }
        else {
            aoki += i*(ll)pow(10, mp2[i]);
        }
    }

    if (taka > aoki) {
        return true;
    }
    else {
        return false;
    }
}


void solve(){
    cin >> K;
    cin >> S; cin >> T;
    map<ll,ll> mp1, mp2;
    for(char c: S) {
        if (c=='#') continue;
        mp1[c-'0']++;
    }
    for(char c: T) {
        if (c=='#') continue;
        mp2[c-'0']++;
    }

    ll bunbo = 0;
    ll win = 0;
    double ans = 0;
    for(ll i=1; i<=9; i++) {
        if (mp1[i]+mp2[i]>=K) {
            // もうiのカードがない
            continue;
        }
        for (ll j=1; j<=9; j++) {
            if (i==j) {
                if (mp1[i]+mp2[j]+1>=K) {
                    // もうjのカードがない
                    continue;
                }
                // まだjのカードが有る
                bunbo++;
                if(battle(mp1, mp2, i, j)) {
                    // (残りのiの枚数)/(9K-8) * (残りのjの枚数)/(9K-9) あってる？？？？？確率？？？？
                    ans += ((double)(K-mp1[i]-mp2[i])/(9*K-8)) * ((double)(K-mp1[j]-mp2[j]-1)/(9*K-9));
                }
            }
            else {
                if (mp1[j]+mp2[j]>=K) {
                    // もうjのカードがない
                    continue;
                }
                // まだjのカードが有る
                bunbo++;
                if (battle(mp1, mp2, i, j)) {
                    ans += ((double)(K-mp1[i]-mp2[i])/(9*K-8)) * ((double)(K-mp1[j]-mp2[j])/(9*K-9));
                }
            }
        }
    }

    // double ans = (double)win/bunbo;
    printf("%.7lf\n", ans);
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}