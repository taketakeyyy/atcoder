# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Cs = input()

    ans = 0
    left, right = 0, N-1
    while left <= right:
        if Cs[left]=="W" and Cs[right]=="R":
            ans += 1  # 石を入れ替える
            left, right = left+1, right-1
            continue
        elif Cs[left]=="W" and Cs[right]=="W":
            right -= 1
            continue
        elif Cs[left]=="R" and Cs[right]=="R":
            left += 1
            continue
        else:
            left, right = left+1, right-1
            continue


    print(ans)


if __name__ == "__main__":
    solve()
