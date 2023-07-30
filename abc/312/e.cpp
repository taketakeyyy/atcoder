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


// 解説AC
void solve() {
    ll N; cin >> N;
    // group[x][y][z] := 小立方体(x,y,z)が属するグループ番号
    vector group(100, vector<vector<ll>>(100, vector<ll>(100, -1)));
    for(ll i=0; i<N; i++) {
        ll x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        for(ll x=x1; x<x2; x++) {
            for(ll y=y1; y<y2; y++) {
                for(ll z=z1; z<z2; z++) {
                    group[x][y][z] = i;
                }
            }
        }
    }

    auto is_inside = [&](ll x, ll y, ll z) -> bool {
        return (x>=0 && x<100 && y>=0 && y<100 && z>=0 && z<100);
    };

    // 各小立方体に隣接する6個の小立方体が、どのグループに属するかを調べる
    const vector<ll> vx = {-1, 1, 0, 0, 0, 0};
    const vector<ll> vy = {0, 0, -1, 1, 0, 0};
    const vector<ll> vz = {0, 0, 0, 0, -1, 1};
    vector<set<ll>> ans(N); // ans[i] := グループiに隣接しているグループの集合
    for(ll x=0; x<100; x++) {
        for(ll y=0; y<100; y++) {
            for(ll z=0; z<100; z++) {
                if (group[x][y][z] == -1) continue;

                // 小立方体(x,y,z)に隣接する6つの小立方体がどのグループに属するか調べる
                for(ll vi=0; vi<6; vi++) {
                    ll nx = x + vx[vi];
                    ll ny = y + vy[vi];
                    ll nz = z + vz[vi];
                    if (!is_inside(nx,ny,nz)) continue;
                    if (group[nx][ny][nz] == -1) continue;
                    if (group[nx][ny][nz] == group[x][y][z]) continue;
                    ans[group[x][y][z]].insert(group[nx][ny][nz]);
                }
            }
        }
    }

    // 答え
    for(ll i=0; i<N; i++) {
        cout << ans[i].size() << endl;
    }
}


int main() {
    solve();
    return 0;
}