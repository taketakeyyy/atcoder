# -*- coding:utf-8 -*-

def solve():
    H = int(input())

    memo = {}
    def dfs(h):
        if h in memo:
            return memo[h]
        if h == 1:
            memo[1] = 1
            return 1

        ret1 = dfs(h//2)
        ret2 = dfs(h//2)
        memo[h] = ret1 + ret2 + 1
        return memo[h]

    ans = dfs(H)
    print(ans)


if __name__ == "__main__":
    solve()
