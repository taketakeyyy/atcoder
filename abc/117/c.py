# -*- coding:utf-8 -*-
def solve():
    # 解説放送を実装
    # 区切る問題
    N, M = [int(x) for x in input().split(" ")]
    X = [int(x) for x in input().split(" ")]

    if M == 1:
        print(0)
        return

    X.sort()
    distance = []
    for i in range(0, len(X)-1):
        distance.append(X[i+1] - X[i])
    
    distance.sort()

    ans = 0
    for i in range(0, len(distance)-(N-1)):
        ans += distance[i]
    
    print(ans)



if __name__ == "__main__":
    solve()