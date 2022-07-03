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
const ll R = 1e4;  // 半径R
const ll rr = 1e4-1e3;  // 少し小さい半径rr



/* 分数 */
template<typename T>
struct frac {
    private:
    public:
        T a;  // 分子
        T b;  // 分母
        frac(T a=0, T b=1) {
            this->a = a; this->b = b;
            // 分母が0のときは、無限大扱いにしたい
            if (this->b == 0) {
                this->a = 1;
                return;
            }
            // マイナスは分子につける
            if (b < 0) { this->a=-this->a; this->b=-this->b; }
            // 約分しておく
            T g = gcd<T>(this->a, this->b);
            this->a /= g;
            this->b /= g;
        }
        bool operator<(const frac &other) const {
            return this->a*other.b < other.a*this->b;
        }
        bool operator<=(const frac &other) const {
            return this->a*other.b <= other.a*this->b;
        }
        bool operator>(const frac &other) const {
            return this->a*other.b > other.a*this->b;
        }
        bool operator>=(const frac &other) const {
            return this->a*other.b >= other.a*this->b;
        }
        bool operator==(const frac &other) const {
            return (this->a == other.a) && (this->b == other.b);
        }
        frac operator*(const frac &other) const {
            T na = this->a*other.a;
            T nb = this->b*other.b;
            return frac(na, nb);
        }
        frac operator/(const frac &other) const {
            T na = this->a*other.b;
            T nb = this->b*other.a;
            return frac(na, nb);
        }
        frac operator+(const frac &other) const {
            T l = lcm(this->b, other.b);
            T na1 = this->a*(l/this->b);
            T na2 = other.a*(l/other.b);
            T na = na1 + na2;
            T nb = l;
            return frac(na, nb);
        }
        frac operator-(const frac &other) const {
            T l = lcm(b, other.b);
            T na1 = this->a*(l/this->b);
            T na2 = other.a*(l/other.b);
            T na = na1 - na2;
            T nb = l;
            return frac(na, nb);
        }
        void print() const {
            cout << this->a << "/" << this->b << endl;
        }
};

/**
 * @brief now_g < y/x < nxt_g となる 適当なx,yを見つける
 *
 * @param now_g
 * @param nxt_g
 * @return pair<ll>
 */
pair<ll,ll> best_xy(frac<ll> now_g, frac<ll> nxt_g) {
    if (frac<ll>(0,1) < now_g) {
        // 傾きが＋ならば
        ll x = now_g.b;
        ll y = now_g.a;
        if (x*x+(y+1)*(y+1) < R*R) {
            return {x, y+1};
        }
        else {
            return {x-1, y};
        }
    }
    else {
        // 傾きが-ならば
        ll x = now_g.b;
        ll y = now_g.a;
        if (x*x+(y-1)*(y-1) < R*R) {
            return {x, y-1};
        }
        else {
            return {x-1, y};
        }
    }
}

pair<vector<pair<ll,ll>>, ll> how_to_cut(vector<ll> &piece, vector<ll> &A, vector<pair<double,ll>> &henkaku1, vector<pair<double,ll>> &henkaku2, ll K, vector<frac<ll>> &katamuki) {
    // どう切ればいいのか？
    vector<pair<ll,ll>> ans;
    ll ans_num = 0;
    ans.push_back({1,0}); // とりま水平線に直線を引く
    ll cut = 1;  // カット回数
    ll pre_idx1 = 0;  // 前回のインデックス
    ll pre_idx2 = 0;  // 前回のインデックス
    ll idx = 0;  // 現在のインデックス
    for(ll j=0; j<piece.size(); j++) {
        ll i = piece[j];// いちごがi個のピースにしたい

        while(A[i] >= 0) {
            if (cut >= K) { break; }
            auto[now_theta, now_id] = henkaku1[idx];
            auto now_g = katamuki[now_id];
            auto[nxt_theta, nxt_id] = henkaku1[idx+1];
            auto nxt_g = katamuki[nxt_id];

            // now_g < y/x < nxt_g となる y,xを求めたい
            auto[x, y] = best_xy(now_g, nxt_g);
            ans.push_back({x,y});
            A[i]--; ans_num++;
            cut++;
            idx += i;

            // 第3,4象限のケーキのピースのいちごを数える
            double cut_theta1 = atan2(y, x);
            double cut_theta2 = cut_theta1 + M_PI;
            auto lb = lower_bound(henkaku2.begin(), henkaku2.end(), make_pair(cut_theta2, 0LL)) - henkaku2.begin();
            ll n2 = lb - pre_idx2;
            if (n2 >= 1 && n2 <= 9) {
                A[n2]--; ans_num++;
            }
            pre_idx2 = lb;
        }
    }

    return {ans, ans_num};
}

void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(10+1);  // 各100人以下。合計はたかだか1000人
    for(ll i=1; i<=10; i++) {
        cin >> A[i];
    }

    // 各いちごの偏角を求める
    vector<pair<ll,ll>> berry(N);  // berry[i] := いちごiの座標
    vector<pair<double,ll>> henkaku1;  // いちごの{偏角, id} で、偏角[0, pi]の範囲
    vector<pair<double,ll>> henkaku2;  // いちごの{偏角, id} で、偏角(pi, 2pi)の範囲
    vector<frac<ll>> katamuki(N);  // いちごiの傾き
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        berry[i] = {x, y};

        // 傾き求める
        katamuki[i] = frac<ll>(y, x);

        // 偏角求める
        double theta = atan2(y, x);
        if (theta < 0) {
            theta += 2*M_PI;  // [0, 2pi) の範囲にする
        }
        if (theta <= M_PI) {
            henkaku1.push_back({theta, i});
        }
        else {
            henkaku2.push_back({theta, i});
        }
    }
    // 偏角ソート
    sort(henkaku1.begin(), henkaku1.end());
    sort(henkaku2.begin(), henkaku2.end());

    // いろんな順番で試す
    vector<ll> piece1 = {1,2,3,4,5,6,7,8,9};
    vector<ll> piece2 = {2,4,5,6,7,8,9,1,3};
    vector<ll> piece3 = {6,7,8,9,1,2,3,4,5};
    ll ans_num = 0;
    vector<pair<ll,ll>> ans;
    auto [ans1, ans_num1] = how_to_cut(piece1, A, henkaku1, henkaku2, K, katamuki);
    ans = ans1;
    ans_num = ans_num1;

    auto [ans2, ans_num2] = how_to_cut(piece2, A, henkaku1, henkaku2, K, katamuki);
    if (ans_num2 > ans_num) {
        ans = ans2;
        ans_num = ans_num2;
    }
    auto [ans3, ans_num3] = how_to_cut(piece3, A, henkaku1, henkaku2, K, katamuki);
    if (ans_num3 > ans_num) {
        ans = ans3;
        ans_num = ans_num3;
    }

    // 出力
    ll KMAX = min(K, (ll)ans.size());
    cout << KMAX << '\n';
    for(ll k=0; k<KMAX; k++) {
        cout << "0 0 " << ans[k].first << " " << ans[k].second << '\n';
    }
}


int main() {
    solve();
    return 0;
}