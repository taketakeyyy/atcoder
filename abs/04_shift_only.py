# -*- coding;utf-8 -*-

def challenge(A):
    for i in range(len(A)):
        if A[i]%2 != 0:
            return False
        A[i] = int(A[i]/2)
    return True

if __name__ == "__main__":
    N = int(input())
    A = list(map(int, input().split()))
    ans = 0
    while 1:
        if challenge(A) is False:
            break
        ans += 1
    print(ans)
