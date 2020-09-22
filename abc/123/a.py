# -*- coding:utf-8 -*-

def solve():
    city = []
    city.append(int(input()))
    city.append(int(input()))
    city.append(int(input()))
    city.append(int(input()))
    city.append(int(input()))
    k = int(input())

    for i in range(0, len(city)):
        for j in range(i+1, len(city)):
            if abs(city[i]-city[j]) > k:
                print(":(")
                exit()
    
    print("Yay!")

if __name__ == "__main__":
    solve()
