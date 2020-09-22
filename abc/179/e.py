# -*- coding:utf-8 -*-

def solve():
    N, X, M = list(map(int, input().split()))

    def f(x, m):
        return x%m

    # A[i]の値は必ず mod Mの範囲に収まる
    # ということはたかだかMの周期でループする
    # ただし、ループして戻るのはA[0]とは限らず、適当なA[?]に戻る
    # 注意として、A[i]=0になったら、A[i+1]以降は必ず0
    A = [0]*(10**5+2)  # A[i]
    Ar = [0]*(10**5+2)  # Ar[i] := A[i]以下の累積和
    A[0], Ar[0] = X, X
    Adic = {X:0}  # Adic[A[i]]=i => 過去のA[i]はi番目に出現した
    stop_i = 0
    is_zero = False
    for i in range(1, N):
        A[i] = f(pow(A[i-1], 2, M), M)
        Ar[i] = Ar[i-1] + A[i]
        if A[i] == 0:
            is_zero = True
            stop_i = i
            break
        if A[i] in Adic:
            stop_i = i
            break
        Adic[A[i]] = i

    if stop_i == 0:
        print(Ar[N-1])
    elif is_zero:
        print(Ar[stop_i])
    else:
        start_i = Adic[A[stop_i]]
        t = stop_i - start_i
        restN = N - start_i
        if start_i-1 >= 0:
            ans = Ar[start_i-1]
            ans += (Ar[stop_i-1] - Ar[start_i-1]) * (restN//t)
            ans += Ar[start_i-1+(restN%t)] - Ar[start_i-1]
        else:
            ans = Ar[stop_i-1] * (restN//t)
            ans += Ar[start_i-1+(restN%t)]
        print(ans)


if __name__ == "__main__":
    solve()
