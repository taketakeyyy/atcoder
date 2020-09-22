# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    D = list(map(int, input().split()))
    D.sort()

    """
    1 4 4 | 6 7 9　OK

    1 4 4 | 4 7 9　だめ

    1 2 3 | 3 7 9  だめ
    """

    if D[int(N//2)-1] == D[int(N//2)]:
        print(0)
        return
    
    ans = D[int(N//2)] - D[int(N//2)-1]

    print(ans)


if __name__ == "__main__":
    solve()
