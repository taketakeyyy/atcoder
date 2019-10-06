# -*- coding:utf-8 -*-

if __name__ == '__main__':
    N, M = list(map(int, input().split()))
    bridges = []
    for i in range(M):
        a, b = list(map(int, input().split()))
        bridges.append([a, b])
    bridges.sort()
    # 実装
    ans = 0
    while bridges != []:
        deletes = []
        left_max  = 0
        right_min = 10**5+1
        for i in range(len(bridges)):
            if bridges[i][0] <= right_min:
                if bridges[i][1] >= left_max:
                    deletes.append(i)
                    left_max  = bridges[i][0]
                    right_min = bridges[i][1]
        for i in range(len(deletes)-1, -1, -1):
            bridges.pop(i)
        ans += 1
    print(ans)
