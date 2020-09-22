# -*- coding:utf-8 -*-

class UnionFindVerSize():
    def __init__(self, N):
        """ N個のノードのUnion-Find木を作成する """
        # 親の番号を格納する。自分が親だった場合は、自分の番号になり、それがそのグループの番号になる
        self._parent = [n for n in range(0, N)]
        # グループのサイズ（個数）
        self._size = [1] * N

    def find_root(self, x):
        """ xの木の根(xがどのグループか)を求める """
        if self._parent[x] == x: return x
        self._parent[x] = self.find_root(self._parent[x]) # 縮約
        return self._parent[x]

    def unite(self, x, y):
        """ xとyの属する集合を併合する """
        gx = self.find_root(x)
        gy = self.find_root(y)
        if gx == gy: return

        # 小さい方を大きい方に併合させる（木の偏りが減るので）
        if self._size[gx] < self._size[gy]:
            self._parent[gx] = gy
            self._size[gy] += self._size[gx]
        else:
            self._parent[gy] = gx
            self._size[gx] += self._size[gy]

    def get_size(self, x):
        """ xが属するグループのサイズ（個数）を返す """
        return self._size(self.find_root(x))

    def is_same_group(self, x, y):
        """ xとyが同じ集合に属するか否か """
        return self.find_root(x) == self.find_root(y)


def solve():
    """戦略
    □ □ □ □ □ □ □ □ □ □ □ □ □ □ □
    |_| |_| |_|     |_| | |_|_|_|
                    |___|
     1   2   3  4 5   6      7   

    上みたいなものを考えたらわかるが、答えはグループの数(=7)。

    Union-Findを使えばよい。

    """
    N, M = list(map(int, input().split()))
    X, Y, Z = [], [], []
    uf = UnionFindVerSize(N)
    for i in range(M):
        x, y, z = list(map(int, input().split()))
        x, y = x-1, y-1
        uf.unite(x, y)
    
    # 答えは、(グループの数) 
    ans = 0
    for i in range(N):
        if uf.find_root(i) == i:
            ans += 1
    
    print(ans)


if __name__ == "__main__":
    solve()
