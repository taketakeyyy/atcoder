# -*- coding:utf-8 -*-

# かなりナイーブな解法
# PythonならTLE。PyPyならAC。多倍長整数ってすごい。
def solve():
    N = int(input())
    A = []
    mp = {}
    for i in range(N):
        a = int(input())
        A.append(a)
        if not a in mp:
            mp[a] = 0
        mp[a] += 1

    ans = 0
    for k in range(0, N):
        for j in range(N):
            if A[k]%A[j]!=0: continue
            ai = A[k]//A[j]
            if not ai in mp: continue
            ans += mp[ai]
    print(ans)


if __name__ == "__main__":
    solve()
