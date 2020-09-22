

def solve():
    # 解説放送を実装
    N = int(input())
    flowers = [0]*N
    h = [int(x) for x in input().split(" ")]
    ans = h[0]
    stack = h[0]

    for i in range(1, N):
        if h[i] <= stack:
            stack = h[i]
        else:
            ans += (h[i] - stack)
            stack = h[i]
    
    print(ans)


if __name__ == "__main__":
    solve()