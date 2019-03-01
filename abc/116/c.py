# Timeout

def update_stops(flowers, h, stops):
    N = len(flowers)
    for i in range(N):
        if flowers[i] == h[i]:
            stops[i] = True    
    

def do_water(ans, flowers, start, stop):
    for i in range(start, stop):
        flowers[i] += 1
    ans += 1
    return ans, flowers

def is_end(stops):
    for i in range(len(stops)):
        if stops[i] is False:
            return False
    return True


def solve():
    N = int(input())
    flowers = [0]*N
    h = [int(x) for x in input().split(" ")]

    stops = [False]*N

    ans = 0
    while True:
        update_stops(flowers, h, stops)
        if is_end(stops):
            print(ans)
            return

        start = 0
        stop = N
        while True:
            for i in range(start, N):
                if stops[i] is False:
                    start = i
                    break
            for j in range(i, N):
                if stops[j] is True:
                    stop = j
                    break

            ans, flowers = do_water(ans, flowers, start, stop)

            if stop == N:
                break
            
            start = stop + 1


if __name__ == "__main__":
    solve()