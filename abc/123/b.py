# -*- coding:utf-8 -*-
import math

def solve():
    menus = []
    for i in range(0, 5):
        menus.append(int(input()))
    
    # １の位が最も小さいものを最後に注文する。あとはなんでもいい
    amari = 10
    last = 0
    for i in range(0, 5):
        if menus[i]%10 < amari and menus[i]%10 != 0:
            last = i
            amari = menus[i]%10
    
    ans = 0
    for i in range(0, 5):
        if i == last:
            continue

        ans += menus[i]
        ans = math.ceil(ans/10) * 10
    
    ans += menus[last]
    print(ans)



if __name__ == "__main__":
    solve()
