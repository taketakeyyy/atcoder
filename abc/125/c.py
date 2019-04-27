# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    # 他のAiにはあって、あるAiに唯一ない約数が答え
    
    candidates = []

    if N == 2:
        print(max(A[0], A[1]))
        return

    candidates = {}
    # まずは0番目の奴の候補を考える
    j = A[0]
    for i in range(1, A[0]+1):
        if i >= j:
            break
        if A[0]%i == 0:
            candidates[i] = 1
            j = A[0]//i
            candidates[j] = 1

    for key in candidates.keys():
        if A[1]%key != 0:
            candidates[key] -= 1

    j = A[1]
    for i in range(1, A[1]+1):
        if i >= j:
            break
        if A[1]%i == 0:
            if not i in candidates:
                candidates[i] = 0
            j = A[1]//i
            if not j in candidates:
                candidates[j] = 0

    import copy
    for i in range(2, N):
        copied_candidates = copy.deepcopy(candidates)
        for key in copied_candidates.keys():
            if A[i]%key == 0:
                pass
            else:
                candidates[key] -= 1
                if candidates[key] < 0:
                    candidates.pop(key)
    
    ans = 0
    for key in candidates.keys():
        ans = max(ans, key)
    
    print(ans)


    

if __name__ == "__main__":
    solve()
