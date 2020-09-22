# -*- coding:utf-8 -*-

def solve():
    S = input()

    def dfs(depth, s):
        if depth == len(S):
            # 計算する
            return sum(list(map(int, s.split("+"))))
        
        ret1 = dfs(depth+1, s+"+"+S[depth])
        ret2 = dfs(depth+1, s+S[depth])

        return ret1 + ret2

    ans = dfs(1, S[0])
    print(ans)

if __name__ == "__main__":
    solve()
