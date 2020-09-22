# -*- coding:utf-8 -*-

def solve():
    K, S = list(map(int, input().split()))

    ans = 0
    for x in range(K+1):
        for y in range(K+1):
            if x+y > S:
                break
            if S-x-y <= K:
                ans += 1
    print(ans)



if __name__ == "__main__":
    solve()
