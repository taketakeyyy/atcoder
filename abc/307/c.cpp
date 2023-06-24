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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll HA, WA; cin >> HA >> WA;
    vector<string> A(HA);
    for(ll i=0; i<HA; i++) {
        cin >> A[i];
    }
    ll HB, WB; cin >> HB >> WB;
    vector<string> B(HB);
    for(ll i=0; i<HB; i++) {
        cin >> B[i];
    }
    ll HX, WX; cin >> HX >> WX;
    vector<string> X(HX);
    for(ll i=0; i<HX; i++) {
        cin >> X[i];
    }

    // シートを必要なところまで小さくする
    auto minimize = [&](vector<string> &D) {
        ll H = D.size();
        ll W = D[0].size();
        ll mnh=INF, mnw=INF, mxh=-1, mxw=-1;
        // mnh
        bool is_end = false;
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (D[h][w] == '#') {
                    mnh = h;
                    is_end = true;
                    break;
                }
            }
            if (is_end) break;
        }

        // mnw
        is_end = false;
        for(ll w=0; w<W; w++) {
            for(ll h=0; h<H; h++) {
                if (D[h][w] == '#') {
                    mnw = w;
                    is_end = true;
                    break;
                }
            }
            if (is_end) break;
        }

        // mxh
        is_end = false;
        for(ll h=H-1; h>=0; h--) {
            for(ll w=0; w<W; w++) {
                if (D[h][w] == '#') {
                    mxh = h;
                    is_end = true;
                    break;
                }
            }
            if (is_end) break;
        }

        // mxw
        is_end = false;
        for(ll w=W-1; w>=0; w--) {
            for(ll h=0; h<H; h++) {
                if (D[h][w] == '#') {
                    mxw = w;
                    is_end = true;
                    break;
                }
            }
            if (is_end) break;
        }

        // 小さいシートEを作る
        vector<vector<char>> E(mxh-mnh+1, vector<char>(mxw-mnw+1, '.'));
        ll he=0, we=0;
        for(ll h=mnh; h<=mxh; h++) {
            we = 0;
            for(ll w=mnw; w<=mxw; w++) {
                E[he][we] = D[h][w];
                we++;
            }
            he++;
        }
        return E;
    };
    auto AA = minimize(A);
    HA = AA.size();
    WA = AA[0].size();
    auto BB = minimize(B);
    HB = BB.size();
    WB = BB[0].size();

    vector<vector<char>> White(HX, vector<char>(WX, '.'));

    for(ll ha=0; ha<HX; ha++) {
        if (ha+HA-1 >= HX) break;

        for(ll wa=0; wa<WX; wa++) {
            if (wa+WA-1 >= WX) break;

            for(ll hb=0; hb<HX; hb++) {
                if (hb+HB-1 >= HX) break;

                for(ll wb=0; wb<WX; wb++) {
                    if (wb+WB-1 >= WX) break;
                    auto Y = White;
                    // Aを貼る
                    for(ll h1=0; h1<HA; h1++) {
                        for(ll w1=0; w1<WA; w1++) {
                            if (AA[h1][w1] == '#') {
                                Y[h1+ha][w1+wa] = AA[h1][w1];
                            }
                        }
                    }

                    // Bを貼る
                    for(ll h1=0; h1<HB; h1++) {
                        for(ll w1=0; w1<WB; w1++) {
                            if (BB[h1][w1] == '#') {
                                Y[h1+hb][w1+wb] = BB[h1][w1];
                            }
                        }
                    }

                    // Xを検証
                    bool is_ok = true;
                    for(ll h=0; h<HX; h++) {
                        for(ll w=0; w<WX; w++) {
                            if (Y[h][w] != X[h][w]) is_ok = false;
                        }
                    }
                    if (is_ok) {
                        cout << "Yes" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}