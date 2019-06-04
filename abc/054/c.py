# -*- coding:utf-8 -*-
import copy

def solve():
    N, M = list(map(int, input().split()))
    A, B = [], []
    edge = {}  # edge[v] := 頂点vの隣接リスト

    """方針
    Nは高々8なので全探索してみる
    """
    for i in range(M):
        a, b = list(map(int, input().split()))
        # 始点は0とする
        if not a-1 in edge:
            edge[a-1] = []
        edge[a-1].append(b-1)
        if not b-1 in edge:
            edge[b-1] = []
        edge[b-1].append(a-1)

    rest_list = [i for i in range(N)]  # まだ到達してない残りの頂点のリスト
    rest_list.remove(0)  # 0が始点なので除外しておく
    now_v = 0  # 現在の頂点

    def dfs(now_v, rest_list):
        if len(rest_list) == 0:
            # 残りの頂点が存在しない（すべての頂点に到達成功した）
            return 1
        ans = 0  # パスの数
        for u in rest_list:
            if not u in edge[now_v]: continue  # 現在の頂点now_vから、次の頂点uに辺が存在しないならスキップ
            tmp_rest_list = copy.deepcopy(rest_list)
            tmp_rest_list.remove(u)
            ans += dfs(u, tmp_rest_list)
        return ans

    ans = dfs(0, rest_list)
    print(ans)


if __name__ == "__main__":
    solve()
