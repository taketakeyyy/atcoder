# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    """方針
    from1 := 1から行ける島番号のリスト
    canN[i] := 島iがNに行くことができるか否か
    from1の中の島bのうち、canN[b] == Trueのものがあるならば、POSSIBLE
    計算量はO(N)
    """
    from1 = []
    canN = [False] * (N+1)
    for i in range(M):
        a, b = list(map(int, input().split()))
        if a == 1:
            from1.append(b)
        elif b == N:
            canN[a] = True
    
    for b in from1:
        if canN[b]:
            print("POSSIBLE")
            return
    print("IMPOSSIBLE")
        

if __name__ == "__main__":
    solve()
