# -*- coding:utf-8 -*-

def solve():
    N, C = list(map(int, input().split()))
    events = {}
    for _ in range(N):
        a, b, c = list(map(int, input().split()))
        if not a in events: events[a] = 0
        if not b+1 in events: events[b+1] = 0
        events[a] += c
        events[b+1] -= c

    ans = 0
    pre_day = 0
    total = 0
    for day in sorted(list(events.keys())):
        ans += min(C, total) * (day - pre_day)
        pre_day = day
        total += events[day]

    print(ans)


if __name__ == "__main__":
    solve()
