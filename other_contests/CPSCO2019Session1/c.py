# -*- coding:utf-8 -*-
import itertools

coins = [1,10,10**2,10**3, 10**4, 10**5, 10**6, 10**7, 10**8, 10**9, 5, 5*10, 5*10**2, 5*10**3, 5*10**4, 5*10**5, 5*10**6, 5*10**7, 5*10**8, 5*10**9]
coins.sort(reverse=True)

def how_many_coins(yen):
    ans = 0
    while yen != 0:
        d1 = yen%10
        if d1 <= 4:
            ans += d1
        else:
            ans += d1-4
        yen //= 10
    return ans


def solve():
    N, K = map(int, input().split())
    As = list(map(int, input().split()))

    # 最小となる答えを探す
    ans = float("inf")
    for combos in itertools.combinations(As, K):
        total_yen = sum(combos)
        ans = min(ans, how_many_coins(total_yen))
    print(ans)


if __name__ == "__main__":
    solve()
