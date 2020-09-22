# -*- coding:utf-8 -*-
from collections import deque

def solve():
    n = int(input())
    A = input().split()

    """方針
    A = 0 6 7 6 7 0
    i | b
    ---------------
    1 | 0
    2 | 0 6 (本当は逆で6 0)
    3 | 7 0 6
    4 | 7 0 6 6 (本当は逆で 6 6 0 7)
    5 | 7 7 0 6 6
    6 | 7 7 0 6 6 0 (本当は逆で0 6 6 0 7 7) 

    ・iが偶数のとき、bの後ろにA[i]を追加する
    ・iが奇数のとき、bの前にA[i]を追加する

    上の操作をn回すべてしたあとに、

    ・nが偶数なら答えを反転する
    ・nが奇数なら答えはそのまま

    ただし、A[i]は2桁以上の数字の可能性も考慮すること

    あとPythonは、list.insert()はとても遅いので（TLEしたので）、代わりにcollections.dequeを使用する

    ・collections.deque
    https://docs.python.org/ja/3/library/collections.html#collections.deque

    dequeとは、「両端における append や pop を高速に行えるリスト風のコンテナ」
    """

    # 1 2 3 -> 3 1 2
    b = deque()
    for i in range(1, n+1):
        if i%2 == 0:
            b.append(A[i-1])
        else:
            b.appendleft(A[i-1])

    if n%2 == 0:
        ans = ""
        for i in range(n-1, -1, -1):
            ans += b[i] + " "
        print(ans[:-1])
    else:
        ans = " ".join(b)
        print(ans)


if __name__ == "__main__":
    solve()
