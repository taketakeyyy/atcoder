# -*- coding:utf-8 -*-

def solve():
    """
    あるXに着目した時、X-1とX+1はXにできる。
    よって、各Xについて数を数える
    """
    N = int(input())
    A = list(map(int, input().split()))

    dic = {}
    for a in A:
        if not a in dic:
            dic[a] = 1
        else:
            dic[a] += 1
        if not a-1 in dic:
            dic[a-1] = 1
        else:
            dic[a-1] += 1
        if not a+1 in dic:
            dic[a+1] = 1
        else:
            dic[a+1] += 1
    
    dic_values = list(dic.values())
    dic_values.sort()
    print(dic_values[-1])


if __name__ == "__main__":
    solve()
