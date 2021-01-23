# -*- coding:utf-8 -*-

def solve():
    X, Y, A, B, C = list(map(int, input().split()))
    Ps = list(map(int, input().split()))
    Qs = list(map(int, input().split()))
    Rs = list(map(int, input().split()))
    Ps.sort(), Qs.sort()
    Alls = Ps[A-X:] + Qs[B-Y:] + Rs  # 赤いリンゴはたかだかX個しか食べたら駄目なので、大きいX個のみを抽出する。緑色も同様。
    Alls.sort(reverse=True)
    ans = sum(Alls[0:X+Y])
    print(ans)


if __name__ == "__main__":
    solve()
