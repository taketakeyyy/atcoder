# -*- coding:utf-8 -*-

def solve():
    X, Y, Z, K = list(map(int, input().split(" ")))
    A = list(map(int, input().split(" ")))
    B = list(map(int, input().split(" ")))
    C = list(map(int, input().split(" ")))
    A.sort(reverse=True)
    B.sort(reverse=True)
    C.sort(reverse=True)

    ans = []

    for x in range(X):
        for y in range(Y):
            ab = A[x] + B[y]
            for z in range(Z):
                if (x+1)*(y+1)*(z+1) > K:
                    break

                ans.append(ab + C[z])

    ans.sort(reverse=True)

    for i in range(0, K):
        print(ans[i])


if __name__ == "__main__":
    solve()
