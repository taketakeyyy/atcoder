# -*- coding:utf-8 -*-

class Conv():
    def __init__(self, b, c):
        self.b = b
        self.c = c

def solve():
    N, M = list(map(int, input().split()))
    A = list(map(int, input().split()))
    A.sort()
    B, C = [], []
    conv = []  # conv[c] := cに変換できる枚数
    for i in range(M):
        b, c = list(map(int, input().split()))
        conv.append(Conv(b, c))
    
    sorted_conv = sorted(conv, key=lambda x: x.c, reverse=True)

    i = 0
    j = 0
    while True:
        if i == len(sorted_conv) or j == N:
            break
        
        if sorted_conv[i].b == 0:
            i += 1
            continue
        
        if sorted_conv[i].c > A[j]:
            A[j] = sorted_conv[i].c
            sorted_conv[i].b -= 1
            j += 1
            continue
        
        break

    print(sum(A))

if __name__ == "__main__":
    solve()
