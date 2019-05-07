# -*- coding:utf-8 -*-

def solve():
    N, A, B, C = list(map(int, input().split()))
    L = []
    for i in range(N):
        L.append(int(input()))

    INF = 10**10

    def dfs(depth, a, b, c):
        """ 各竹を、
        ・Aの合成魔法に使う
        ・Bの合成魔法に使う
        ・Cの合成魔法に使う
        ・使わない

        a:= 現在のAの長さ
        b:= 現在のBの長さ
        c:= 現在のCの長さ

        返り値は、MP
        """
        if depth == N:
            if min(a, b, c) > 0:
                return abs(a-A)+abs(b-B)+abs(c-C) - 30 # 必ず1つは選ばないといけないが、1つ選んだときは合成魔法のMPは必要ないので30引く
            else:
                return INF
        
        ans1 = dfs(depth+1, a, b, c)
        ans2 = dfs(depth+1, a+L[depth], b, c) + 10
        ans3 = dfs(depth+1, a, b+L[depth], c) + 10
        ans4 = dfs(depth+1, a, b, c+L[depth]) + 10

        return min(ans1, ans2, ans3, ans4)

    ans = dfs(0, 0, 0, 0)
    print(ans)

if __name__ == "__main__":
    solve()
