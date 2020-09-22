# -*- coding:utf-8 -*-
from collections import defaultdict

def solve():
    N = int(input())
    
    d = defaultdict(int)
    for _ in range(N):
        s = input()
        l_s = list(s)
        l_s.sort()
        s = "".join(l_s)
        d[s] += 1

    ans = 0
    for key, value in d.items():
        # 和の公式
        ans += (((value-1)+1) * (value-1)) / 2
    print(int(ans))

if __name__ == "__main__":
    solve()
