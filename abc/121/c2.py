# -*- coding:utf-8 -*-

class Shop():
    def __init__(self, v, n):
        self.value = v
        self.zaiko = n

def solve():
    N, M = list(map(int, input().split()))
    shops = []
    for i in range(N):
        a, b = list(map(int, input().split()))
        shops.append(Shop(a, b))
    
    shops.sort(key=lambda x: x.value)

    rest = M
    ans = 0
    for i in range(N):
        if shops[i].zaiko <= rest:
            ans += shops[i].value * shops[i].zaiko
            rest -= shops[i].zaiko
        else:
            ans += shops[i].value * rest
            break
    
    print(ans)


if __name__ == "__main__":
    solve()
