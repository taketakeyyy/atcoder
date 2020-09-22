# -*- coding:utf-8 -*-

def solve():
    a, b = list(map(int, input().split()))
    ans1 = str(a)*b
    ans2 = str(b)*a

    ans = ans1 if ans1 < ans2 else ans2
    print(ans)


if __name__ == "__main__":
    solve()
