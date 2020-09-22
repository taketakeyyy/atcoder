# -*- coding:utf-8 -*-
import math

def solve():
    N = int(input())
    vehicles = []
    for i in range(0, 5):
        vehicles.append(int(input()))
    
    botle_neck = vehicles[0]
    for i in range(1, 5):
        if vehicles[i] < botle_neck:
            botle_neck = vehicles[i]
            continue
        else:
            vehicles[i] = botle_neck
    
    # 結局vehicles[4] + 4分？
    ans = math.ceil(N/vehicles[4]) + 4

    print(ans)



if __name__ == "__main__":
    solve()
