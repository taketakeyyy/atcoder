# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    Hs = list(map(int, input().split()))

    Hs.sort(reverse=True)

    ans = 0
    for h in Hs:
        if K > 0:
            K -= 1
            continue
        ans += h
    print(ans)


if __name__ == "__main__":
    solve()
