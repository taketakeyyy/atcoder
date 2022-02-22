#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
#define itoc(x) ((char)(x+48))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


string make_arithmetic_number (string &sx, ll X) {
    ll diff = (sx[1]-'0') - (sx[0]-'0');
    string tmpx = sx;
    bool is_ok = true;
    for(ll d=1; d<sx.size(); d++) {
        ll nx = tmpx[d-1]-'0'+diff;
        if (0 <= nx && nx <= 9) {
            tmpx[d] = itoc(nx);
        }
        else {
            is_ok = false;
            break;
        }
    }

    // 等差数が作れた
    if (is_ok) {
        if (stoll(tmpx) >= X) {
            return tmpx;
        }
    }

    return "";
}

string make_decending_number(string &sx, ll X) {
    // 9876543210 みたいなの作る
    ll diff = (sx[0]-'0') / (sx.size()-1);
    string tmpx = sx;
    bool is_ok = true;
    for(ll i=1; i<sx.size(); i++) {
        ll nx = (tmpx[i-1]-'0') - diff;
        if (0 <= nx && nx <= 9) {
            tmpx[i] = itoc(nx);
        }
        else {
            is_ok = false;
            break;
        }
    }

    if (is_ok) {
        if (stoll(tmpx) >= X) {
            return tmpx;
        }
    }
    return "";
}

string make_acending_number(string &sx, ll X) {
    // 12345 みたいなの作る
    ll diff = 1;
    string tmpx = sx;
    bool is_ok = true;
    for(ll i=1; i<sx.size(); i++) {
        ll nx = (tmpx[i-1]-'0') + diff;
        if (0 <= nx && nx <= 9) {
            tmpx[i] = itoc(nx);
        }
        else {
            is_ok = false;
        }
    }

    if (is_ok) {
        if (stoll(tmpx) >= X) {
            return tmpx;
        }
    }
    return "";
}

string make_same_number(string &sx, ll X) {
    // 11111 みたいなの作る
    string tmpx = sx;
    char ch = tmpx[0];
    for(ll i=1; i<sx.size(); i++) {
        tmpx[i] = ch;
    }

    if (stoll(tmpx) >= X) {
        return tmpx;
    }
    return "";
}


void solve() {
    ll X; cin >> X;

    // X = 152
    // * 最上位桁をDとする
    // * D-1桁 - D桁 をして、同じ桁数で等差数をつくれて、それがX以上の数字ならそれが答え
    // * 作れないなら、D桁に1を足して、
    //   - 等差数を作れるか調べる
    //   - 桁上りに注意

    string sx = to_string(X);
    if (sx.size() == 1) {
        cout << X << endl;
        return;
    }

    ll ans = INF;
    string ans1, ans2, ans3, ans4;
    ans1 = make_arithmetic_number(sx, X);
    ans2 = make_acending_number(sx, X);
    ans3 = make_decending_number(sx, X);
    ans4 = make_same_number(sx, X);
    if (ans1 != "") { ans = stoll(ans1); }
    if (ans2 != "") { ans = min(ans, stoll(ans2)); }
    if (ans3 != "") { ans = min(ans, stoll(ans3)); }
    if (ans4 != "") { ans = min(ans, stoll(ans4)); }
    if (ans != INF) {
        cout << ans << endl;
        return;
    }

    // 作れなかったら、最上位に1を足して、再度試みる
    if (sx[0] == '9') {
        sx[0] = '0';
        // sx.insert(sx.begin(), '1');
        sx = "1" + sx;
    }
    else {
        sx[0] = itoc((sx[0]-'0') + 1);
    }

    ans1 = make_arithmetic_number(sx, X);
    ans2 = make_acending_number(sx, X);
    ans3 = make_decending_number(sx, X);
    ans4 = make_same_number(sx, X);
    if (ans1 != "") { ans = stoll(ans1); }
    if (ans2 != "") { ans = min(ans, stoll(ans2)); }
    if (ans3 != "") { ans = min(ans, stoll(ans3)); }
    if (ans4 != "") { ans = min(ans, stoll(ans4)); }
    if (ans != INF) {
        cout << ans << endl;
        return;
    }
}

void solve2() {
    ll X; cin >> X;

    // 等差数をすべて作る
    vector<ll> tosasu;
    for(ll i=1; i<=9; i++) {
        string s = "";
        s += itoc(i);
        tosasu.push_back(stoll(s));

        for(ll diff=-9; diff<=9; diff++) {
            string ss = s;
            while(1) {
                if (ss.size()==18) break;

                ll nx = (ss[ss.size()-1]-'0') + diff;
                if (0 <= nx && nx <= 9) {
                    ss += itoc(nx);
                    tosasu.push_back(stoll(ss));
                }
                else {
                    break;
                }
            }
        }
    }

    sort(tosasu.begin(), tosasu.end());
    cout << *lower_bound(tosasu.begin(), tosasu.end(), X) << endl;
}

int main() {
    solve2();
    return 0;
}