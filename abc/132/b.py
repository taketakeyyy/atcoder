# -*- coding:utf-8 -*-

def solve():
    n = int(input())
    P = list(map(int, input().split()))

    def f(a, b, c):
        lst = [a, b, c]
        lst.sort()
        if lst[1] == b:
            return True
        return False

    ans = 0
    for i in range(0, n-2):
        if f(P[i], P[i+1], P[i+2]):
            ans += 1
    
    print(ans)

if __name__ == "__main__":
    solve()
