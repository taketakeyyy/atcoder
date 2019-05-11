# -*- coding:utf-8 -*-
"""解説
Union-Find

i番目の辺(ai, bi)を除く全ての辺を使ってUnion-Find木を作る。

その後、ai と bi がつながっているかを判定する。つながっていないならば、ai,biの辺は橋である。

この操作をすべてのiにおいて全探索する。

【計算量】
たぶんO(M(N+M))

Union-Findによるあるノード(a, b)が同じグループかどうか（今回では、同じグループ＝繋がっている）
の判定は高速でできる。

"""
class UnionFind():
    def __init__(self, N):
        """ N個のノードのUnion-Find木を作成する """
        # 親の番号を格納する。自分が親だった場合は、自分の番号になり、それがそのグループの番号になる
        self.parent = [n for n in range(0, N)]
        # グループの深さ
        self.depth = [1] * N

    def find(self, x):
        """ 木の根(どのグループか)を求める """
        if self.parent[x] == x: return x
        self.parent[x] = self.find(self.parent[x]) # 縮約
        return self.parent[x]

    def unite(self, x, y):
        """ xとyの属する集合を併合する """
        gx = self.find(x)
        gy = self.find(y)
        if gx == gy: return

        # 小さい方を大きい方に併合させる（木の偏りが減るので）
        if self.depth[gx] < self.depth[gy]:
            self.parent[gx] = gy
        else:
            self.parent[gy] = gx
            if self.depth[gx] == self.depth[gy]: self.depth[gx] += 1

    def is_same_group(self, x, y):
        """ xとyが同じ集合に属するか否か """
        return self.find(x) == self.find(y)


def solve():
    N, M = list(map(int, input().split()))
    edges = []

    for i in range(M):
        a, b = list(map(int, input().split()))
        edges.append([a-1, b-1])

    # 各辺について、その辺が存在しない時、aとbが連結になるかをUnion-Findで判定する
    ans = 0
    for i in range(M):
        uf = UnionFind(N)
        for j, edge in enumerate(edges):
            if i == j: continue
            
            a, b = edge
            uf.unite(a, b)
        
        # i番目の辺を除くすべての辺をつないだあとで、i番目の辺(a, b)がつながるかを判定する
        # つながらないならば、そのi番目の辺は橋である
        a, b = edges[i]
        if not uf.is_same_group(a, b): ans += 1
    
    print(ans)
    

if __name__ == "__main__":
    solve()
