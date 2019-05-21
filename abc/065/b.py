# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = []
    for i in range(N):
        A.append(int(input())-1)
    
    is_pushed = [False for i in range(N)] # 既に押されたかどうか

    i = A[0]
    ans = 1
    is_pushed[0] = True
    while True:
        if i == 1:
            print(ans)
            return
        # ボタンを押す
        if is_pushed[i]:
            print(-1)
            return
        is_pushed[i] = True
        i = A[i]
        ans += 1


if __name__ == "__main__":
    solve()
