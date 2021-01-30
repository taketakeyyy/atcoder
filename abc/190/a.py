# -*- coding:utf-8 -*-

def solve():
    A, B, C = list(map(int, input().split()))
    if C == 0:
        cnt = 0
        while True:
            if cnt%2 == 0:
                if A==0:
                    print("Aoki")
                    return
                A -= 1
            else:
                if B==0:
                    print("Takahashi")
                    return
                B -= 1
            cnt += 1
    else:
        cnt = 1
        while True:
            if cnt%2 == 0:
                if A==0:
                    print("Aoki")
                    return
                A -= 1
            else:
                if B==0:
                    print("Takahashi")
                    return
                B -= 1
            cnt += 1


if __name__ == "__main__":
    solve()
