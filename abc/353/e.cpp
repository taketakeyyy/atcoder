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


/**
 * @brief Trie木
 *
 * @tparam T
 *
 * @usage
 * // Trie木に文字列を追加
 * trie.add("FIREMAN");
 * trie.add("FIREARM");
 * trie.add("FIREWORK");
 *
 * // Trie木に "FIRE" の文字列は存在するか？
 * string s = "FIRE";
 * cout << (trie.search(s) ? "Yes" : "No") << endl;
 * // No
 *
 * // LCP（最長共通接頭辞）になら "FIRE" は存在する
 * int len = trie.lcp_len(s);
 * cout << s.substr(0,len) << endl;
 * // FIRE
 *
 * // Trie木中の"FIREMAN"を除外した"FIREMAN"とのLCPは？
 * string s2 = "FIREMAN";
 * int len2 = trie.lcp_len_exclude(s2);
 * cout << len2 << endl;
 * cout << s2.substr(0,len2) << endl;
 * // 4
 * // FIRE
 */
template <typename T>
class Trie {
    private:
        // Trie木用のノード
        struct Node {
            map<char, Node*> next; // next[ch] := 現在のノードの次の文字がchの場合、次のノードを返す
            Node *prev = nullptr; // 現在のノードの前のノードを格納
            char moji;
            bool is_endnode = false;  // ある文字列の終端ノード（受理状態）か？
            T cnt = 0; // このノードを終端とする文字列の個数
            Node() {}
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
            for(T i=0; i<(T)S.size(); i++) {
                if (now_ptr->next.count(S[i])) {
                    // すでに文字が存在する場合、その子をたどる
                    now_ptr = now_ptr->next[S[i]];
                    if (i == (T)S.size()-1) {
                        now_ptr->is_endnode = true;
                        now_ptr->cnt++;
                    }
                    continue;
                }
                else {
                    // 文字が存在しない場合、新しく分岐木を作る
                    Node *child_ptr = new Node();
                    child_ptr->moji = S[i];
                    child_ptr->prev = now_ptr;
                    now_ptr->next[S[i]] = child_ptr;
                    if (i == (T)S.size()-1) {
                        child_ptr->is_endnode = true;
                        child_ptr->cnt++;
                    }
                    now_ptr = child_ptr;
                }
            }
        }

        // この問題の答えを返す
        T solver() {
            // DFSでノードを探索し、帰りがけにnC2を計算する
            auto dfs = [&](auto dfs, const Node &now_node) -> pair<ll,ll> { // (数え上げたい個数, ここを通る文字列の個数)
                // 終了条件
                if ((ll)now_node.next.size() == 0) {
                    ll res = (now_node.cnt*(now_node.cnt-1LL))/2LL; // (i,j)の組の個数（数え上げたい個数）
                    return {res, now_node.cnt};
                }

                // 次の探索
                ll total_cnt = now_node.cnt;
                ll total_res = 0;
                for(auto[ch, nxt_node]: now_node.next) {
                    auto[res, cnt] = dfs(dfs, *nxt_node);
                    total_cnt += cnt;
                    total_res += res;
                }

                // 帰りがけにnC2を足し合わせる
                if (now_node.prev != nullptr) { // rootノードでないならば
                    total_res += (total_cnt*(total_cnt-1LL))/2LL;
                }
                return {total_res, total_cnt};
            };
            auto[res, cnt] = dfs(dfs, root);
            return res;
        }
};


void solve() {
    ll N; cin >> N;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    Trie<ll> trie; // トライ木
    for(ll i=0; i<N; i++) {
        trie.add(S[i]);
    }

    // ソルバーで解く
    ll ans = trie.solver();
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}