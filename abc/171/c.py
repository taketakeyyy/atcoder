# -*- coding:utf-8 -*-

def solve():
    N = int(input())

    # どの桁帯にいるかを求める
    b = 1
    d = 26
    num = 26
    while N > num:
        b += 1
        d *= 26
        num += d

    N = N - (num - d)
    N -= 1  # 0-indexedにする

    # 26進数で答えを求める
    ans = ""
    for i in range(b-1, -1, -1):
        a = N//(26**i)
        ans += chr(97+a)
        N -= (26**i)*a

    print(ans)


if __name__ == "__main__":
    solve()
