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

const ll MAX_K = 10000; // 最大可能移動回数
vector<tuple<ll,ll,ll,ll>> ans;  // 出力用の答え

ll evaluate(vector<vector<ll>> &pyramid) {
    return 0;
}

// (x1,y1) (x2,y2)の隣接するボールを入れ替える操作
void swap_move(ll x1, ll y1, ll x2, ll y2, map<ll,pair<ll,ll>> &num2coords, map<pair<ll,ll>,ll> &coords2num) {
    ll num1 = coords2num[{x1,y1}];
    ll num2 = coords2num[{x2,y2}];
    coords2num[{x1,y1}] = num2;
    coords2num[{x2,y2}] = num1;
    num2coords[num1] = {x2,y2};
    num2coords[num2] = {x1,y1};
    ans.push_back({x1,y1,x2,y2});
}

// (x1,y1)のボールは、(d-1,ty)を目指し下っていく操作
void swap_down_move(ll x1, ll y1, ll tx, ll ty, map<ll,pair<ll,ll>> &num2coords, map<pair<ll,ll>,ll> &coords2num) {
    while(1) {
        if ((ll)ans.size() == MAX_K) return;
        if (x1 == tx) return;
        ll nx = x1 + 1;
        ll ny = y1;
        if (ty > y1) {
            ny = y1+1;
        }
        else if (ty < y1){
            ny = y1-1;
        }
        swap_move(x1, y1, nx, ny, num2coords, coords2num);
        x1 = nx;
        y1 = ny;
    }
}

void solver() {
    // 入力
    map<ll,pair<ll,ll>> num2coords; // 数字から座標へのマップ
    map<pair<ll,ll>,ll> coords2num; // 座標から数字へのマップ
    vector<ll> A; // 数字が大きい順に並べた配列
    constexpr const ll N = 30;
    vector pyramid(30, vector<ll>());
    for(ll i=0; i<30; i++) {
        for(ll j=0; j<i+1; j++) {
            ll b; cin >> b;
            pyramid[i].push_back(b);
            num2coords[b] = {i,j};
            coords2num[{i,j}] = b;
            A.push_back(b);
        }
    }

    // 大きい順に並べる
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());

    // 注目段をd(>=1)とする。今からd段に数字を持っていきたい。
    // 配列Aから上位d個取り出して、深さが深い順にソートする。
    {
        ll d = N;  // 段
        ll di = N*(N+1)/2-1;
        while(d >= 1) {
            if ((ll)ans.size() == MAX_K) break;

            priority_queue<tuple<ll,ll,ll>> B; // (x,y,数字)
            for(ll i=di; i>di-d; i--) {
                B.push({num2coords[A[i]].first, num2coords[A[i]].second, A[i]});
            }
            di = di-d;

            vector<bool> filled(d, false);

            // Bにある数字を順にd段に持っていく
            while(!B.empty()) {
                if ((ll)ans.size() == MAX_K) break;

                auto[x,y,num] = B.top(); B.pop();
                x = num2coords[num].first;
                y = num2coords[num].second;

                // 行ける範囲
                ll ly = y, ry = y+(d-1-x);
                // 目指す位置
                ll ty = -1;
                for(ll i=ly; i<=ry; i++) {
                    if (filled[i]) continue;
                    ty = i;
                    break;
                }

                if (ty == -1) {
                    // 行ける範囲は全部埋まっているので、d段の数字を移動させて行けるところを作る
                    ll miny = ly;
                    while(1) {
                        miny--;
                        if (miny < 0) break;
                        if (!filled[miny]) break;
                    }
                    ll maxy = ry;
                    while(1) {
                        maxy++;
                        if (maxy == d) break;
                        if (!filled[maxy]) break;
                    }
                    if (miny == -1) ty = maxy;
                    else if (maxy == d) ty = miny;
                    else if (abs(miny-ly) <= abs(maxy-ry)) ty = miny;
                    else ty = maxy;

                    // 行き場所が決まったので、そこに移動させるためにswapさせる
                    if (ty > ry) {
                        filled[ty] = true;
                        // まず、(d-1, ty)のボールを(d-1, ry)に移動させる
                        while(1) {
                            ll ny = ty-1;
                            swap_move(d-1, ty, d-1, ny, num2coords, coords2num);
                            ty = ny;
                            if (ty == ry) break;
                        }
                        // 次に、(x,y)のボールは(d-1,ry)を目指す
                        swap_down_move(x, y, d-1, ry, num2coords, coords2num);
                    }
                    else {
                        filled[ty] = true;
                        // まず、(d-1, ty)のボールを(d-1, ly)に移動させる
                        while(1) {
                            ll ny = ty+1;
                            swap_move(d-1, ty, d-1, ny, num2coords, coords2num);
                            ty = ny;
                            if (ty == ly) break;
                        }
                        // 次に、(x,y)のボールは(d-1,ly)を目指す
                        swap_down_move(x, y, d-1, ly, num2coords, coords2num);
                    }
                }
                else {
                    // 目指す位置が存在するので、そのまま下って移動する
                    filled[ty] = true;
                    swap_down_move(x, y, d-1, ty, num2coords, coords2num);
                }
            }

            d--;
        }
    }

    // 出力
    cout << ans.size() << endl;
    for(auto[x1,y1,x2,y2]: ans) {
        cout << x1 << " " << y1 << " " << x2 << " " <<  y2 << endl;
    }
}

void solve() {
    solver();
}


int main() {
    solve();
    return 0;
}