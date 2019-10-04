# -*- coding:utf-8 -*-

if __name__ == '__main__':
    A = list(map(int, input().split()))
    min_costs = 0
    for i in range(len(A)):
        if i+1 >= 3:
            j = abs(3 - i+1)
        else:
            j = i+1
        if i+2 >= 3:
            k = abs(3 - i+2)
        else:
            k = i+2
        costs = abs(A[j] - A[i]) + abs(A[k] - A[i])
        if costs < min_costs:
            min_costs = costs
    print(min_costs)
