# -*- coding:utf-8 -*-
""" 解説
Union Find

・グラフにおいて、「つなぐ処理」はOK。「きりはなす処理」は難しい

すべてが崩落している状態から、 時間を巻き戻すように橋をかけていき不便度を計算していく。

UnionFindで、島aと島bが同じグループに属するということは、いずれかの橋を渡っていけば島aから島bまで到達可能という意味
"""

"""UnionFindの例
1 2 3 4 5 の島を考える

・3と5をつなげる
1 2 3 4
    |
    5

・3と1をつなげる（要素の多いものにつなげる）
2 3 4
  +--
  | |
  5 1

・2と4をつなげる
3    2
+--  |
| |  |
5 1  4

・1と4をつなげる（1のグループの3と、4のグループの2をつなぐ）
    3
--+--
| | |
5 1 2
    |
    4

・ただし、あとで4の親を付け替える
    3
--+----
| | | |
5 1 2 4

"""

class UnionFind():
    def __init__(self, N):
        # 親の番号を格納する。親だった場合は、-(その集合のサイズ)
        # 初期状態は-1で、すべてバラバラの状態
        self.parent = [-1] * N

    def root(self, A):
        # Aがどのグループに属しているか調べる（親の番号を返す）
        if self.parent[A] < 0:
            return A
        self.parent[A] = self.root(self.parent[A])
        return self.parent[A]

    def size(self, A):
        """ 自分のいるグループの頂点数を調べる """
        return -self.parent[self.root(A)]  # 親を取ってきたい
    
    def connect(self, A, B):
        """ AとBをくっつける
        AとBを直接つなぐのではなく、root(A)にroot(B)をくっつける 
        """
        A = self.root(A)
        B = self.root(B)
        if A == B:
            # 既にくっついてるからくっつけない
            return False
        
        # 大きいほう（A）に小さいほう（B）をくっつけたい
        # 大小が逆だったらひっくり返しちゃう
        if self.size(A) < self.size(B):
            A, B = B, A
        
        # Aのサイズを更新する
        self.parent[A] += self.parent[B]
        # Bの親をAに変更する
        self.parent[B] = A

        return True


def solve():
    N, M = list(map(int, input().split(" ")))
    A = []
    B = []

    for i in range(M):
        a, b = list(map(int, input().split()))
        A.append(a-1)
        B.append(b-1)
    
    ans = [0]*M
    ans[M-1] = N*(N-1)/2  # すべて崩落した状態の不便さ
    ufind = UnionFind(N)

    for i in range(M-1, 0, -1):
        if ufind.root(A[i]) != ufind.root(B[i]):
            # 繋がっていなかったのがつながった時
            ans[i-1] = ans[i] - ufind.size(A[i]) * ufind.size(B[i])
            ufind.connect(A[i], B[i])
        else:
            ans[i-1] = ans[i]
    
    for i in range(0, M):
        print(int(ans[i]))



if __name__ == "__main__":
    solve()