# -*- coding:utf-8 -*-

def solve():
    """
    ((((()))())()())()()
    """
    N, K = map(int, input().split())
    S = input()
    buns = []  # 得られる対応バンズの美味しさの候補の全列挙
    now = 0    # 現在の対応バンズの美味しさ
    for moji in S:
        if moji == "(":
            now += 1
        elif moji == ")":
            now -= 1
        buns.append(now)
    buns.sort(reverse=True)

    ans = sum(buns[0:K])
    print(ans)


if __name__ == "__main__":
    solve()
