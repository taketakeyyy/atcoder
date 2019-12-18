# -*- coding:utf-8 -*-

def solve():
    N, X = map(int, input().split())
    As = list(map(int, input().split()))
    As.sort(reverse=True)

    max_a = As[0]
    ans = 1
    for a in As[1:]:
        if a+X >= max_a:
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
