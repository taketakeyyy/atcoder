# -*- coding:utf-8 -*-
import copy

def solve():
    N, M = list(map(int, input().split()))
    A = list(map(int, input().split()))
    candidates = copy.deepcopy(A[1:])

    for i in range(N-1):
        A = list(map(int, input().split()))
        A = copy.deepcopy(A[1:])

        copied_candidates = copy.deepcopy(candidates)
        for candidate in copied_candidates:
            if candidate in A:
                continue
            else:
                candidates.remove(candidate)
            
    print(len(candidates))



if __name__ == "__main__":
    solve()
