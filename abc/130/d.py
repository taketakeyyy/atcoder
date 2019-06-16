# -*- coding:utf-8 -*-
"""考え方
累積和

・3パターン考える
|_連続部分列_|.....

.....|_連続部分列_|

.....|_連続部分列_|.....


"""

def solve():
    N, K = list(map(int, input().split()))
    A = list(map(int, input().split()))

    ruiseki = [0]
    total = 0
    for a in A:
        total += a
        ruiseki.append(total)
    rN = len(ruiseki)
    
    ans = 0
    # .....|_連続部分列_|.....
    for l in range(0, rN):
        for r in range(l+1, rN):
            if (ruiseki[r] - ruiseki[l]) >= K:
                ans += (rN - r)
                break

    print(ans)

if __name__ == "__main__":
    solve()
