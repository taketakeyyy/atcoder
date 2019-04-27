# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    MOD = 10**9 + 7

    # 使える文字
    # A G C T

    # だめな部分文字列 
    # AGC ACG GAC    (3文字)
    # ATGC            (前二つを入れ替えの4文字) 
    # AGGC AGTC (後ろ二つを入れ替えの4文字)

    ans = 4**N
    
    if N >= 3:
        ans -= 3*(N-2)
    
    if N >= 4:
        ans -= 3*(N-3)
    
    print(ans)


if __name__ == "__main__":
    solve()
