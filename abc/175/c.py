# -*- coding:utf-8 -*-

def solve():
    X, K, D = list(map(int, input().split()))
    X = abs(X)

    syo = X//D
    if syo >= K:
        ans = X - D*K
        print(ans)
        return

    # 負の方にも行くならば
    plus = X - D*syo  # 正側の答え
    minus = plus - D  # 負側の答え
    restK = K - syo - 1

    if restK%2 == 0:
        print(abs(minus))
        return
    print(plus)
    return


if __name__ == "__main__":
    solve()
