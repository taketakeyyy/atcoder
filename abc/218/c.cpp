#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

ll N;

pair<ll,ll> most_left_and_up(vector<string> s) {
    // 最も左の#の位置
    ll left = -1;
    for(ll w=0; w<N; w++) {
        for(ll h=0; h<N; h++) {
            if(s[h][w] == '#') {
                left = w;
                break;
            }
        }

        if (left != -1) break;
    }

    // 最も上の#の位置
    ll up = -1;
    for(ll h=0; h<N; h++) {
        if(s[h][left] == '#') {
            up = h;
            break;
        }
    }

    return {up, left};  // {h, w}
}

vector<string> rotate90(vector<string> const &s) {
    vector<string> res(N);
    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            res[h] += ".";
        }
    }

    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            res[h][w] = s[N-1-w][h];
        }
    }
    return res;
}

ll black_num(vector<string> s) {
    ll res = 0;
    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            if (s[h][w] == '#') {
                res++;
            }
        }
    }
    return res;
}

/* 一致するか検証 */
bool validate(vector<string> const &s, vector<string> const &t) {
    ll left1, up1;
    ll left2, up2;
    tie(up1, left1) = most_left_and_up(s);
    tie(up2, left2) = most_left_and_up(t);

    ll dh = up2-up1;
    ll dw = left2-left1;
    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            if (s[h][w] == '#') {
                if (!(0<=h+dh && h+dh<N)) return false;
                if (!(0<=w+dw && w+dw<N)) return false;
                if (t[h+dh][w+dw] != '#') return false;
            }
        }
    }
    return true;
}

void solve() {
    cin >> N;
    // 90度回転の4通り分、左上を合わせて検証する
    vector<string> S(N);
    vector<string> T(N);
    for(ll h=0; h<N; h++) {
        cin >> S[h];
    }
    for(ll h=0; h<N; h++) {
        cin >> T[h];
    }

    if (black_num(S) != black_num(T)) {
        cout << "No" << endl;
        return;
    }

    // 90度回転して検証する
    for(ll i=0; i<4; i++) {
        if (validate(S, T)) {
            cout << "Yes" << endl;
            return;
        }
        S = rotate90(S);

        // テスト
        // cout << endl;
        // for(ll h=0;h<N;h++) {
        //     for(ll w=0; w<N; w++) {
        //         cout << S[h][w];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    cout << "No" << endl;
    return;
}


int main() {
    solve();
    return 0;
}