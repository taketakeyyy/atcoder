# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    max_cnt = 0
    for i in range(N, 0, -1):
        cnt = 0
        num = i
        while True:
            if num == 1:
                print(i)
                return
            if num%2 == 0:
                num //=  2
                cnt += 1
                continue
            if cnt > max_cnt:
                max_cnt = cnt
                ans = i
            break
    print(ans)


if __name__ == "__main__":
    solve()
