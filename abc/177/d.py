# -*- coding:utf-8 -*-

def solve():
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
            """ xとyの属するグループを併合する """
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
            return self._size[self.find_root(x)]

        def is_same_group(self, x, y):
            """ xとyが同じ集合に属するか否か """
            return self.find_root(x) == self.find_root(y)

        def calc_group_num(self):
            """ グループ数を計算して返す """
            N = len(self._parent)
            ans = 0
            for i in range(N):
                if self.find_root(i) == i:
                    ans += 1
            return ans

    N, M = list(map(int, input().split()))
    uf = UnionFindVerSize(N)
    for _ in range(M):
        a, b = list(map(int, input().split()))
        uf.unite(a-1, b-1)

    # 求める答えは、最大グループ数の人数に等しい。
    ans = 0
    for i in range(N):
        ans = max(ans, uf.get_size(i))

    print(ans)


if __name__ == "__main__":
    solve()
