# -*- coding:utf-8 -*-

class UnionFind():
    def __init__(self, N):
        self.parent = [-1 for i in range(N)]  # 親のときは負の値をとり、-(そのグループのサイズ)
    
    def find(self, x):
        """ xがどのグループに属するかを返す """
        if self.parent[x] < 0: return x
        
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def unite(self, x, y):
        """ xとyのグループを併合する """
        gx = self.find(x)
        gy = self.find(y)

        if gx == gy: return
        
        if self.size(gx) < self.size(gy):
            self.parent[gy] -= self.size(gx)
            self.parent[gx] = gy
        else:
            self.parent[gx] -= self.size(gy)
            self.parent[gy] = gx
    
    def size(self, x):
        """ xが属するグループのサイズ """
        gx = self.find(x)
        return -self.parent[gx]

    def is_same_group(self, x, y):
        """ xとyが同じグループに属するかを調べる """
        return self.find(x) == self.find(y)


def solve():
    """ 方針
    ・「つなげる処理は簡単。切り離す処理は難しい」

    すべてが崩落している状態から、 時間を巻き戻すように橋をかけていき不便度を計算していく。

    UnionFindで、島aと島bが同じグループに属するということは、いずれかの橋を渡っていけば島aから島bまで到達可能という意味
    """
    N, M = list(map(int, input().split()))
    A, B = [], []
    for m in range(M):
        a, b = list(map(int, input().split()))
        A.append(a-1)
        B.append(b-1)

    uf = UnionFind(N)
    ans = [(N-1)*N/2] * (M) # すべてが崩落した状態を初期状態とする

    for i in range(M-1, 0, -1):
        if not uf.is_same_group(A[i], B[i]):
            # 同じグループではないので、つながっていない
            # ので、つなげる
            ans[i-1] = ans[i] - uf.size(A[i]) * uf.size(B[i])
            uf.unite(A[i], B[i])
        else:
            ans[i-1] = ans[i]
    
    for i in range(M):
        print(int(ans[i]))


if __name__ == "__main__":
    solve()