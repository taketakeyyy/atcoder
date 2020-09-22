# -*- coding: utf-8 -*-


if __name__ == '__main__':
    C = [[-1 for i in range(3)] for j in range(3)]
    minv = 101
    min_a_i = -1  # 最小のときのaの添字
    min_b_i = -1
    for a_i in range(3):
        lists = list(map(int, input().split()))
        for b_i in range(3):
            C[a_i][b_i] = lists[b_i]
            if lists[b_i] < minv:
                minv = lists[b_i]
                min_a_i = a_i
                min_b_i = b_i

    # 最小の値から、aとbの取りうる範囲を全探索する
    for v in range(0, minv+1):
        A = [-1]*3
        B = [-1]*3
        A[min_a_i] = v
        for b_i in range(3):
            B[b_i] = C[min_a_i][b_i] - v
        a_i = min_a_i
        for _ in range(2):
            a_i += 1
            if a_i == 3: a_i = 0
            A[a_i] = C[a_i][a_i] - B[a_i]
        # ansCを作って元のCと比較する
        ans = [[-1 for i in range(3)] for j in range(3)]
        for a_i in range(3):
            for b_i in range(3):
                ans[a_i][b_i] = A[a_i] + B[b_i]
        if ans == C:
            print("Yes")
            exit()
    print("No")
