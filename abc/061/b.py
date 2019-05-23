# -*- coding:utf-8 -*-
"""解き方
[入力例1]
4 3
1 2
2 3
1 4

道路\都市 | 1 | 2 | 3 | 4
           ○   ○ 
               ○   ○
           ○           ○

[出力例1]
2
2
1
1
"""
def solve():
    N, M = list(map(int, input().split()))
    road_cnt = [0 for i in range(N)]

    for i in range(M):
        a, b = list(map(int, input().split()))
        a, b = a-1, b-1

        road_cnt[a] += 1
        road_cnt[b] += 1
    
    for cnt in road_cnt:
        print(cnt)


if __name__ == "__main__":
    solve()
