# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    A = []
    B = []

    for i in range(N):
        A.append(list(input()))
    for i in range(M):
        B.append(list(input()))
    
    # 左上から順に走査する
    for i in range(N-M+1):
        for j in range(N-M+1):
            if A[i][j] == B[0][0]:
                is_contained = True
                for k in range(0, M):
                    for l in range(0, M):
                        if A[i+k][j+l] != B[k][l]:
                            is_contained = False
                            break
                    if not is_contained: break
                if is_contained:
                    print("Yes")
                    return
    print("No")


if __name__ == "__main__":
    solve()
