# -*- coding:utf-8 -*-

def solve():
    S = input()

    def func(s):
        moji_dic = {}
        for moji in s:
            if not moji in moji_dic:
                moji_dic[moji] = 0
            moji_dic[moji] += 1
        
        if len(moji_dic.keys()) != 2:
            return False
        
        for v in moji_dic.values():
            if v != 2:
                return False
        
        return True
    
    if func(S):
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
