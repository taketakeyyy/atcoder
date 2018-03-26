#-*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    A = list(map(int, input().split()))
    A.insert(0, 0)
    A.append(0)
    # 本来のコスト計算
    honrai_cost = 0
    for i in range(N+1):
        honrai_cost += abs(A[i]-A[i+1])
    # iを訪れるのをやめたときのコストを計算して出力
    for i in range(1, N+1):
        minus_cost = abs(A[i-1] - A[i]) + abs(A[i] - A[i+1])
        plus_cost  = abs(A[i-1] - A[i+1])
        print(honrai_cost - minus_cost + plus_cost)
