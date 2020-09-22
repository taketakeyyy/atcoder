# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    # 先に+をめくって、後に*をひたすらめくると良い

    ans = 0
    panels = []
    for n in range(N):
        c, a = input().split()
        a = int(a)

        if c == "+":
            ans += a
            continue
        elif c == "-":
            continue
        # *のパネルだけ追加
        panels.append((c,a))

    for c, a in panels:
        if a <= 0:
            continue
        ans *= a

    print(ans)



if __name__ == "__main__":
    solve()
