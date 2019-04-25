# -*- coding:utf-8 -*-


def solve():
    MOD = 998244353
    N = int(input())
    A = []
    for i in range(N):
        A.append(int(input()))
    

    def dfs(depth, r, g, b):
        """ 個数を返す """
        if depth == N:
            if min(r,g,b) == 0:
                return 0
            else:
                longest = max(r,g,b)
                other = (r+g+b) - longest
                if longest < other:
                    return 1
                else:
                    return 0
        
        ret1 = dfs(depth+1, r+A[depth], g, b)
        ret2 = dfs(depth+1, r, g+A[depth], b)
        ret3 = dfs(depth+1, r, g, b+A[depth])

        return (ret1+ret2+ret3)%MOD
    
    ans = dfs(0, 0, 0, 0)
    print(ans)

    


if __name__ == "__main__":
    solve()