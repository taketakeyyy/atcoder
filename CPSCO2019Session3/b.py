# -*- coding:utf-8 -*-

def solve():
    N, M = map(int, input().split())
    As = list(map(int, input().split()))
    As.sort(reverse=True)

    ans = 0
    for a in As:
        M -= a
        ans += 1
        if M <= 0:
            break

    print(ans)

if __name__ == "__main__":
    solve()
