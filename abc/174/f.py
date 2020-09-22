# -*- coding:utf-8 -*-
class BIT():
    def __init__(self, N):
        self._N = N
        self._bit = [0 for _ in range(N+1)]

    @property
    def bit(self):
        return self._bit

    def add(self, a, w):
        """v[a]に値wを加算する"""
        x = a
        while x <= self._N:
            self._bit[x] += w
            x += x&-x

    def sum(self, a):
        """区間和v[1]+...+v[a]を返す"""
        ret = 0
        x = a
        while x > 0:
            ret += self._bit[x]
            x -= x&-x
        return ret


def solve():
    """ 解説実装 """
    import sys
    N, Q = list(map(int, sys.stdin.readline().split()))
    Cs = list(map(int, sys.stdin.readline().split()))

    # (s,t)の位置を保持するst_listを作っていく
    s_set = set()  # sの座標をとにかく保持する
    st_list = []
    dic = {}  # (s,t)を保持する辞書
    for i, c in enumerate(Cs):
        if not c in dic:
            dic[c] = (i+1, None)  # tは決まっていないのでNoneとする
            continue
        if dic[c][1] is None:
            # はじめて(s,t)が作成された
            dic[c] = (dic[c][0], i+1)
        else:
            # 既に(s,t)が作成されている場合
            dic[c] = (dic[c][1], i+1)
        st_list.append(dic[c])
        s_set.add(dic[c][0])

    # (l,r)の位置を保持するlr_listを作っていく
    lr_list = []
    for q in range(Q):
        l, r = list(map(int, sys.stdin.readline().split()))
        lr_list.append(((l, r), q))
        s_set.add(l)

    s_list = list(s_set)
    st_list.sort()
    lr_list.sort()
    anss = [-1 for _ in range(Q)]

    # 右から左へ平面走査するとき、座標sの時点で座標t以下の(s,t)が何個あるかを、
    # t_ruiskei[座標t] := 座標t以下の(s,t)の個数
    # で表す
    st_i = len(st_list)-1
    lr_i = len(lr_list)-1
    t_ruiseki = BIT(5*10**5)

    for s in s_list[::-1]:  # 右から左へ走査する
        while st_i >= 0 and st_list[st_i][0] == s:  # ダセェな！
            t_ruiseki.add(st_list[st_i][1], 1)
            st_i -= 1

        # クエリを実行する
        while lr_i >= 0 and lr_list[lr_i][0][0] == s:
            lr, query = lr_list[lr_i]
            l, r = lr
            anss[query] = (r-l+1) - t_ruiseki.sum(r)
            lr_i -= 1

    for q in range(Q):
        print(anss[q])


if __name__ == "__main__":
    solve()
