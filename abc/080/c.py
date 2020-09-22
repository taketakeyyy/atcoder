# -*- coding:utf-8 -*-

def zehnpaard():
    from itertools import product

    n = int(input())
    fs = [[int(x) for x in input().split()] for _ in range(n)]
    ps = [[int(x) for x in input().split()] for _ in range(n)]

    xs = product((0, 1), repeat=10)
    next(xs)
    print(max(sum(p[sum(a==b==1 for a, b in zip(f, x))] for f, p in zip(fs, ps)) for x in xs))

def solver():
    import itertools
    N = int(input())

    # implements
    Fs = [list(map(int, input().split())) for n in range(N)]
    Ps = [list(map(int, input().split())) for n in range(N)]

    # joisino姉がお店を開く全組み合わせ
    Xs = itertools.product([0,1], repeat=10)
    next(Xs) # すべて0を除く

    ans = (-10**7)*N  # 最小値をセットしておく
    for x in Xs:
        profit = 0
        for n in range(N):
            c = 0
            for a, b in zip(x, Fs[n]):
                if a==b==1:
                    c += 1
            profit += Ps[n][c]
        ans = max(ans, profit)
    print(ans)


if __name__ == "__main__":
    solver()
