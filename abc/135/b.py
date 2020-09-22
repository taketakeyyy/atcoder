# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    P = list(map(int, input().split()))

    target_i = None
    for i in range(1, N):
        if P[i-1] > P[i]:
            target = P[i-1]
            target_i = i-1
            if i-2 >= 0:
                low = P[i-2]
            else:
                low = None
            high = P[i]
            break
    
    # low超え high未満で、入れ替え可能な数字を探す
    if target_i is not None:
        for i in range(target_i+2, N):
            if P[i] < high:
                if low is None:
                    P[target_i] = P[i]
                    P[i] = target
                    break
                else:
                    if low < P[i]:
                        P[target_i] = P[i]
                        P[i] = target
                        break
                    else:
                        continue
    
    # 昇順か確認
    for i in range(N):
        if P[i] != i+1:
            print("NO")
            return
    print("YES")




if __name__ == "__main__":
    solve()
