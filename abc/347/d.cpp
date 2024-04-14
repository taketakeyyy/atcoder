#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll A, B, C; cin >> A >> B >> C;
    const ll BITMAX = 61;

    ll restA = A;
    ll restB = B;
    ll useA = 0;
    ll useB = 0;
    ll bitNumC = __builtin_popcountll(C); // Cのビットが立っている個数

    // エッジケース
    if (A+B < bitNumC) {
        cout << -1 << endl;
        return;
    }

    if (restA >= restB) {
        ll diff = (restA-restB);
        bitNumC -= diff;
        restA -= diff;
        useA += diff;
    }
    else {
        ll diff = (restB-restA);
        bitNumC -= diff;
        restB -= diff;
        useB += diff;
    }

    // 偶数じゃないなら無理
    if (bitNumC<0 or bitNumC%2!=0) {
        cout << -1 << endl;
        return;
    }

    // restAとrestBで1個ずつ交互に出す
    ll cnt = bitNumC/2LL;
    restA -= cnt;
    restB -= cnt;
    useA += cnt;
    useB += cnt;
    if (restA<0 or restB<0) {
        cout << -1 << endl;
        return;
    }

    // Cのどこのbitが立つのか調べる
    vector<bool> biton(BITMAX, false);
    for(ll i=0; i<BITMAX; i++) {
        if (C>>i&1LL) {
            biton[i] = true;
        }
    }

    // XとYを作る
    vector<bool> bitonX(BITMAX, false);
    vector<bool> bitonY(BITMAX, false);
    ll restUseA = useA;
    ll X = 0, Y = 0;
    for(ll i=0; i<BITMAX; i++) {
        if (biton[i]) {
            if (restUseA > 0) {
                restUseA--;
                X += (1LL<<i);
                bitonX[i] = true;
            }
            else {
                Y += (1LL<<i);
                bitonY[i] = true;
            }
        }
    }

    // Cのビットが立っていないところに、適当にXとYの両方にビットを立てる
    for(ll i=0; i<BITMAX; i++) {
        if (!biton[i]) {
            if (restA > 0) {
                restA--;
                X += (1LL<<i);
                Y += (1LL<<i);
                bitonX[i] = true;
                bitonY[i] = true;
            }
        }
    }

    // 答え
    const ll LIMIT = 1LL<<60LL;
    if (X >= LIMIT or Y >= LIMIT) { // エッジケース
        // A=60, B=60, C=3 のときなど
        cout << -1 << endl;
    }
    else {
        cout << X << " " << Y << endl;
    }
}


// 解説AC
void solve2() {
    ll a, b, C; cin >> a >> b >> C;

    ll restA = a; // aの残りの値
    ll restB = b; // bの残りの値
    // ll bitNumC = __builtin_popcountll(C); // Cのビットが立っている個数

    // Cのビットが1の箇所では、restA=restBになるようにXとYのビットを立てていく
    ll X = 0;
    ll Y = 0;
    for(ll d=0; d<60; d++) {
        if (C>>d&1) {
            if (restA >= restB) {
                restA--;
                X += (1LL<<d); // 1<<dだとWAなので注意
            }
            else {
                restB--;
                Y += (1LL<<d);
            }
        }
    }
    // コーナーケース注意（restA==restB）
    if ((restA<0 or restB<0) or !(restA==restB)) {
        cout << -1 << endl;
        return;
    }

    // Cのビットが0の箇所では、restA=restB=0になるまで減らし、残った箇所は0
    for(ll d=0; d<60; d++) {
        if (!(C>>d&1)) {
            if (restA > 0) {
                restA--; restB--;
                X += (1LL<<d);
                Y += (1LL<<d);
            }
        }
    }
    // コーナーケース注意（X,Yは2の60乗未満）
    if (restA>0 or restB>0) {
        cout << -1 << endl;
        return;
    }

    // 答え
    cout << X << " " << Y << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}