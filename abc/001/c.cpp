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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 浮動小数点数誤差が怖いのですべて整数で処理する
void solve() {
    ll deg, dis; cin >> deg >> dis;

    // 風向を決める
    string DEG;
    deg *= 10; // 10倍して整数で比較できるようにする
    if (1125<=deg && deg<3375) DEG = "NNE";
    else if (3375<=deg && deg<5625) DEG = "NE";
    else if (5625<=deg && deg<7875) DEG = "ENE";
    else if (7875<=deg && deg<10125) DEG = "E";
    else if (10125<=deg && deg<12375) DEG = "ESE";
    else if (12375<=deg && deg<14625) DEG = "SE";
    else if (14625<=deg && deg<16875) DEG = "SSE";
    else if (16875<=deg && deg<19125) DEG = "S";
    else if (19125<=deg && deg<21375) DEG = "SSW";
    else if (21375<=deg && deg<23625) DEG = "SW";
    else if (23625<=deg && deg<25875) DEG = "WSW";
    else if (25875<=deg && deg<28125) DEG = "W";
    else if (28125<=deg && deg<30375) DEG = "WNW";
    else if (30375<=deg && deg<32625) DEG = "NW";
    else if (32625<=deg && deg<34875) DEG = "NNW";
    else DEG = "N";

    // 風力を決める
    ll DIS;
    if (0<=dis && dis<15) {DIS = 0; DEG="C";}
    else if (15<=dis && dis<93) DIS = 1;
    else if (93<=dis && dis<201) DIS = 2;
    else if (201<=dis && dis<327) DIS = 3;
    else if (327<=dis && dis<477) DIS = 4;
    else if (477<=dis && dis<645) DIS = 5;
    else if (645<=dis && dis<831) DIS = 6;
    else if (831<=dis && dis<1029) DIS = 7;
    else if (1029<=dis && dis<1245) DIS = 8;
    else if (1245<=dis && dis<1467) DIS = 9;
    else if (1467<=dis && dis<1707) DIS = 10;
    else if (1707<=dis && dis<1959) DIS = 11;
    else if (1959<=dis) DIS = 12;

    // 出力
    cout << DEG << " " << DIS << endl;
}


int main() {
    solve();
    return 0;
}