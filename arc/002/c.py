# -*- coding:utf-8 -*-

def solve():
    import sys

    N = int(sys.stdin.readline())
    Cs = sys.stdin.readline().rstrip()

    # 0個目からやるパターン
    Cdic = {}
    for i in range(0, len(Cs), 2):
        if i+1 == len(Cs): break

        cc = Cs[i]+Cs[i+1]

        if not cc in Cdic:
            Cdic[cc] = 0
        Cdic[cc] += 1

    commands = []
    for key, value in Cdic.items():
        commands.append((key, value))

    commands.sort(key=lambda x: x[1], reverse=True)

    if len(commands) >= 2:
        ans = commands[0][1] + commands[1][1] + (len(Cs) - commands[0][1]*2 - commands[1][1]*2)
    else:
        ans = commands[0][1] + (len(Cs) - commands[0][1]*2)

    # 1個目からやるパターン
    Cdic = {}
    for i in range(1, len(Cs), 2):
        if i+1 == len(Cs): break

        cc = Cs[i]+Cs[i+1]

        if not cc in Cdic:
            Cdic[cc] = 0
        Cdic[cc] += 1

    commands = []
    for key, value in Cdic.items():
        commands.append((key, value))

    commands.sort(key=lambda x: x[1], reverse=True)

    if len(commands) >= 2:
        ans = min(ans, commands[0][1] + commands[1][1] + (len(Cs) - commands[0][1]*2 - commands[1][1]*2))
    else:
        ans = min(ans, commands[0][1] + (len(Cs) - commands[0][1]*2))

    print(ans)


if __name__ == "__main__":
    solve()
