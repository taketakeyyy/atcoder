# -*- coding:utf-8 -*-
"""考え方
1回目のt行きは、右行ったあと上
1回目のs行きは、左行ったあと下
2回目のt行きは、一回下行って、右行ったあと上、その後左
2回目のs行きは、一回上行って、左行ったあと下、その後右
"""
def solve():
    sx, sy, tx, ty = list(map(int, input().split()))
    ans = ""
    
    # 一回目のt行き
    ans += "R"*(tx-sx)
    ans += "U"*(ty-sy)

    # 一回目のs行き
    ans += "L"*(tx-sx)
    ans += "D"*(ty-sy)

    # 二回目のt行き
    ans += "D"
    ans += "R"*(tx-sx+1)
    ans += "U"*(ty-sy+1)
    ans += "L"

    # 二回目のs行き
    ans += "U"
    ans += "L"*(tx-sx+1)
    ans += "D"*(ty-sy+1)
    ans += "R"

    print(ans)

if __name__ == "__main__":
    solve()
