#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

class SegmentTreeRMQ {
    /* Renge Minimum Query */

    public:
        int max_num;  // セグ木のノードの最大値
        int n;  // セグ木の葉の数
        vector<int> nodes;  // セグ木のノード
        SegmentTreeRMQ(vector<int> lst, int max_num=INT_MAX) {
            /***
             * Args:
             *  lst(vector<int>) 元の配列
             *  max_num(int): セグ木の各ノードの初期値
             ***/
            this->max_num = max_num;
            int i = 1; int total = 1;
            while (1) {
                if (lst.size() <= i) break;
                i *= 2;
                total += i;
            }
            this->n = i;
            this->nodes.resize(total, this->max_num);
            for (int i=0; i<lst.size(); i++) {
                this->update(i, lst[i]);
            }
        }

        void update(int i, int x) {
            /* 元の配列 lst[i] に対応するセグ木のノード値をxに変更し、セグ木全体を更新する */
            int ni = this->_lst2node(i);
            this->nodes[ni] = x;
            while (ni > 0) {
                ni = (ni-1)/2;
                int l = ni*2+1; int r = ni*2+2;
                this->nodes[ni] = min(this->nodes[l], this->nodes[r]);
            }
        }

        int _lst2node(int i) {
            /* 元の配列 lst[i] は、セグ木の i+(葉の数)-1 番目のノード */
            return i+this->n-1;
        }

        int query(int a, int b) {
            /* 区間 [a,b) のクエリに応答する */
            return this->_find(a, b, 0, 0, this->n);
        }

        int _find(int a, int b, int k, int l, int r) {
            /* 区間 [a,b) のクエリに対して、担当区間 [l,r) のノード k が応答する */
            if (r<=a || b<=l) {
                // 区間がかぶらない場合
                return this->max_num;
            }
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                return this->nodes[k];
            }
            // それ以外
            int ret1 = this->_find(a, b, 2*k+1, l, (l+r)/2);  // 左の子に聞く
            int ret2 = this->_find(a, b, 2*k+2, (l+r)/2, r);  // 右の子に聞く
            return min(ret1, ret2);
        }
};

void solve(){
    int N;
    cin >> N;
    vector<int> As(N);
    for (int i=0; i<N; i++) cin >> As[i];

    int ans = 0;
    for (int l=0; l<N; l++) {
        int mn = As[l];
        ans = max(ans, mn);
        for (int r=l+1; r<N; r++) {
            mn = min(mn, As[r]);
            ans = max(ans, mn*(r-l+1));
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}