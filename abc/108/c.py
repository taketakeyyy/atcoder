# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))

    # K|a+b K|b+c K|c+a
    # K|2a  K|2b  K|2c

    # Kが奇数のとき、 K|a も K|b も K|c も、Kの倍数
    # Kが偶数のとき、 K/2|a  K/2|b  K/2|c
    if K%2 != 0:
        # Kが奇数のとき、aがKで割り切れる数は、
        kinds = (N//K)  # kinds通りある
        # 同様に、b, cも kinds通りある。
        # よって、答えはa, b, cの組み合わせなので
        print(kinds**3)
        return
    K //= 2
    m = N // K
    ans = (m//2) ** 3 + (m - m//2) ** 3
    print(ans)
    return           


if __name__ == "__main__":
    solve()