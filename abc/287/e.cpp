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


// Trie木
class Trie {
    private:
        struct Node {
            map<char, Node*> next;
            Node *prev;
            char moji;
            bool is_endnode;  // ある文字列の終端ノード（受理状態）か？
            Node() {
                is_endnode = false;
            }
        };
        Node root;

    public:
        Trie() {
            root = Node();
        }

        // 文字列Sを追加
        // O(|S|)
        void add(string const &S) {
            Node *now_ptr = &root;
            for(ll i=0; i<(ll)S.size(); i++) {
                if (now_ptr->next.count(S[i])) {
                    // すでに文字が存在する場合、その子をたどる
                    now_ptr = now_ptr->next[S[i]];
                    if (i == (ll)S.size()-1) now_ptr->is_endnode = true;
                    continue;
                }
                else {
                    // 文字が存在しない場合、新しく分岐木を作る
                    Node *child_ptr = new Node();
                    child_ptr->moji = S[i];
                    child_ptr->prev = now_ptr;
                    now_ptr->next[S[i]] = child_ptr;
                    if (i == (ll)S.size()-1) child_ptr->is_endnode = true;
                    now_ptr = child_ptr;
                }
            }
        }

        // 文字列SがTrie木に存在するかを返す
        // O(|S|)
        bool search(string const &S) {
            Node *now_ptr = &root;
            for(ll i=0; i<(ll)S.size(); i++) {
                if (!now_ptr->next.count(S[i])) return false;
                now_ptr = now_ptr->next[S[i]];
            }
            if (now_ptr->is_endnode) return true;
            return false;
        }

        // 文字列Sと、Trie木に存在する文字列との最長共通接頭辞（LCP）の長さを返す
        // 文字列S自体がTrie木に存在する場合、それ以外とのLCPを返す
        // O(|S|)
        ll lcp_len_exclude(string const &S) {
            ll res = 0;
            ll depth = 0;
            Node *now_ptr = &root;
            for(ll i=0; i<(ll)S.size(); i++) {
                if (!now_ptr->next.count(S[i])) break;

                now_ptr = now_ptr->next[S[i]];
                depth++;
                if ((ll)now_ptr->next.size() >= 2) res = depth;
                else if (i==(ll)S.size()-1 && now_ptr->next.size()>=1) res = depth;
                else if (i!=(ll)S.size()-1 && now_ptr->is_endnode) res = depth;
            }
            return res;
        }

        // 文字列Sと、Trie木に存在する文字列との最長共通接頭辞（LCP）の長さを返す
        // 文字列S自体がTrie木に存在する場合、S.size()を返す
        // O(|S|)
        ll lcp_len(string const &S) {
            ll depth = 0;
            Node *now_ptr = &root;
            for(ll i=0; i<(ll)S.size(); i++) {
                if (now_ptr->next.count(S[i])) depth++;
                else break;
            }
            return depth;
        }
};

// Trie木
void solve() {
    ll N; cin >> N;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    // 各文字列をTrie木に追加する O(N+sum(|S|))
    Trie trie;
    map<string,ll> S_cnt;  // 重複文字列が存在するかを知りたい
    for(ll i=0; i<N; i++) {
        S_cnt[S[i]]++;
        if (S_cnt[S[i]] >= 2) continue;
        trie.add(S[i]);
    }

    // クエリ処理 O(N+sum(|S|))
    for(ll i=0; i<N; i++) {
        // 重複文字が存在する場合は、S.size()が答え
        // そうでないなら、LCPの長さを計算する
        if (S_cnt[S[i]] >= 2) cout << S[i].size() << endl;
        else cout << trie.lcp_len_exclude(S[i]) << endl;
    }
}


int main() {
    solve();
    return 0;
}