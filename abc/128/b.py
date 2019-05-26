# -*- coding:utf-8 -*-

class Restaurant():
    def __init__(self, i, name, point):
        self.i = i
        self.name = name
        self.point = point

def solve():
    N = int(input())
    restaurants = []
    for i in range(N):
        s, p = input().split()
        r = Restaurant(i, s, int(p))
        restaurants.append(r)
    
    sorted_restaurants = sorted(restaurants, key=lambda r: r.point, reverse=True)
    sorted_restaurants = sorted(sorted_restaurants, key=lambda r: r.name)

    for i in range(N):
        print(sorted_restaurants[i].i + 1)


if __name__ == "__main__":
    solve()
