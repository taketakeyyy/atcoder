# -*- coding:utf-8 -*-

def solve():
    """ 
    dic[a] := 数字aが紙に書かれているか否か（True/False）
    """
    N = int(input())
    dic = {}
    for i in range(N):
        a = int(input())
        if not a in dic:
            dic[a] = True
            continue
        if dic[a] == True:
            dic[a] = False
        else:
            dic[a] = True
    
    ans = 0
    for key in dic:
        if dic[key]: ans += 1
    print(ans)

if __name__ == "__main__":
    solve()
