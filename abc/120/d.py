# -*- coding:utf-8 -*-

class UnionFind():
    def __init__(self, N):
        # 親の番号を格納する。親だった場合は、-(その集合のサイズ)
        self.parent = [-1] * N

    def root(self, A):
        # Aがどのグループに属しているか調べる
        if self.parent[A] < 0:
            return A
        self.parent[A] = self.root(self.parent[A])
        return self.parent[A]

    def size(self, A):
        """ 自分のいるグループの頂点数を調べる """
        return -self.parent[self.root(A)]  # 親を取ってきたい
    
    def connect(self, A, B):
        # AとBを直接つなぐのではなく、root(A)にroot(B)をくっつける
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


if __name__ == "__main__":
    solve()