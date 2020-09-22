# -*- coding:utf-8 -*-
"""考え方
・"Scc"という組をできるだけ多く作りたい


"""
def solve():
    sN, cN = list(map(int, input().split()))

    if 2*sN < cN:
        # SSccccc
        # SScccc で二組作れる。
        # 余ったcで、できるだけScc組を作る
        ans = sN
        restC = cN - 2*sN  # 余ったCの数

        # cが4つあれば新たにSccが作れる
        ans += restC//4
    else:
        # SSccc
        # cの数が少ない場合
        ans = cN//2
    print(ans)


if __name__ == "__main__":
    solve()
