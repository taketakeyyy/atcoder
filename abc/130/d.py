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

    ruiseki = []
    total = 0
    for a in A:
        total += a
        ruiseki.append(total)
    rN = len(ruiseki)

    ans = 0
    total = 0
    right = 0
    while True:
        total += A[right]

        if total >= K:
            ans += N - right
            break
        right += 1

    for left in range(0, N):
        total -= A[left]

        while True:
            if total >= K:
                ans += N - right
                break
            
            right += 1
            if right+1 >= N:
                break
            total += A[right]
    
    print(ans)




if __name__ == "__main__":
    solve()
