# -*- coding: utf-8 -*-

if __name__ == '__main__':
    A = int(input()) # 500
    B = int(input()) # 100
    C = int(input()) # 50
    X = int(input())

    ans = 0
    for i_500 in range(A):
        if 500*i_500 > X: break
        for i_100 in range(B):
            if (500*i_500+100*i_100) > X: break
            for i_50 in range(C):
                if (500*i_500 + 100*i_100 + 50*i_50) > X:
                    break
                if (500*i_500 + 100*i_100 + 50*i_50) == X:
                    ans += 1
                    break
    print(ans)
