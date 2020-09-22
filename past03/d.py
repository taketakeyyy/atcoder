# -*- coding:utf-8 -*-

def solve():
    import sys

    zero = ["###",
            "#.#",
            "#.#",
            "#.#",
            "###"]

    one  = [".#.",
            "##.",
            ".#.",
            ".#.",
            "###"]

    two  = ["###",
            "..#",
            "###",
            "#..",
            "###"]

    three  = ["###",
              "..#",
              "###",
              "..#",
              "###"]

    four  = ["#.#",
             "#.#",
             "###",
             "..#",
             "..#"]

    five  = ["###",
             "#..",
             "###",
             "..#",
             "###"]

    six  = ["###",
            "#..",
            "###",
            "#.#",
            "###"]

    seven  = ["###",
              "..#",
              "..#",
              "..#",
              "..#"]

    eight  = ["###",
              "#.#",
              "###",
              "#.#",
              "###"]

    nine  = ["###",
             "#.#",
             "###",
             "..#",
             "###"]


    N = int(sys.stdin.readline())
    Ss = []
    for _ in range(5):
        s = sys.stdin.readline().rstrip()
        Ss.append(s)

    ans = ""
    for i in range(1, N+1):
        left, right = (4*i-2)-1, (4*i)-1
        newS = []
        for j in range(5):
            newS.append(Ss[j][left:right+1])

        if newS == zero:
            ans += "0"
        elif newS == one:
            ans += "1"
        elif newS == two:
            ans += "2"
        elif newS == three:
            ans += "3"
        elif newS == four:
            ans += "4"
        elif newS == five:
            ans += "5"
        elif newS == six:
            ans += "6"
        elif newS == seven:
            ans += "7"
        elif newS == eight:
            ans += "8"
        elif newS == nine:
            ans += "9"

    print(ans)


if __name__ == "__main__":
    solve()
