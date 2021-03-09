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
    string s; cin >> s;
    int pos1 = s.find("/");
    ll y = stoll(s.substr(0,pos1));
    int pos2 = s.substr(pos1+1).find("/");
    ll m = stoll(s.substr(pos1+1, pos2));
    ll d = stoll(s.substr(pos1+1).substr(pos2+1));

    auto is_leap = [](ll y) {
        if (y%4==0) {
            if (y%100==0) {
                if (y%400==0) {
                    return true;
                }
                return false;
            }
            return true;
        }
        return false;
    };

    // 探す
    while(1) {
        if(y%m==0 && (y/m)%d==0) {
            printf("%02lld/%02lld/%02lld\n",y,m,d);
            return;
        }

        d++;
        if (m==1||m==3||m==5||m==7||m==8||m==10||m==12) {
            // 31日まで
            if (d==32) {
                d = 1;
                m++;
                if (m==13) {
                    y++;
                    m = 1;
                }
            }
        }
        else if (m==4||m==6||m==9||m==11) {
            // 30日まで
            if (d==31) {
                d = 1;
                m++;
            }
        }
        else { // 2月
            if (is_leap(y)) {
                if (d==30) {
                    d = 1;
                    m++;
                }
            }
            else {
                if (d==29) {
                    d = 1;
                    m++;
                }
            }
        }
    }
}


int main() {
    solve();
    return 0;
}