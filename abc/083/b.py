# -*- coding:utf-8 -*-

def solve():
    N, A, B = list(map(int, input().split()))

    ans = 0
    for i in range(1, N+1):
        keta_sum = 0
        num = i
        while True:
            if num == 0:
                break
            keta_sum += num%10
            num = num//10

        if keta_sum >= A and keta_sum <= B:
            ans += i
    
    print(ans)

if __name__ == "__main__":
    solve()
