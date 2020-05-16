# -*- coding:utf-8 -*-

def solve():
    import sys

    N = int(sys.stdin.readline())
    n = N//5
    N %= 5

    start = 1 + n%6

    cards = []
    for i in range(6):
        cards.append(str(start))
        start += 1
        if start == 7: start = 1

    for i in range(N):
        left, right = i%5, i%5+1
        cards[left], cards[right] = cards[right], cards[left]

    ans = "".join(cards)
    print(ans)


if __name__ == "__main__":
    solve()
