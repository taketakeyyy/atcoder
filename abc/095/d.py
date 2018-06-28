#Static Sushi
""" zehnpaard氏
from itertools import accumulate, chain

n, c = map(int, input().split())
xs, vs = zip(*(map(int, input().split()) for _ in range(n)))

ds = [j - i for i, j in zip(chain([0], xs), chain(xs, [c]))]

clockwise1      = chain([0], (v - d*2 for v, d in zip(accumulate(vs), accumulate(ds))))
anticlockwise1  = chain([0], (v - d for v, d in zip(accumulate(vs[::-1]), accumulate(ds[::-1]))))
clock_anticlock = (x + y for x, y in zip(clockwise1, reversed(list(accumulate(anticlockwise1, func=max)))))

anticlockwise2  = chain([0], (v - d*2 for v, d in zip(accumulate(vs[::-1]), accumulate(ds[::-1]))))
clockwise2      = chain([0], (v - d for v, d in zip(accumulate(vs), accumulate(ds))))
anticlock_clock = (x + y for x, y in zip(anticlockwise2, reversed(list(accumulate(clockwise2, func=max)))))

print(max(chain(clock_anticlock, anticlock_clock)))
"""

if __name__ == "__main__":
    N, C = list(map(int, input().split()))
    X = []
    V = []
    for i in range(N):
        x, v = list(map(int, input().split()))
        X.append(x)
        v.append(v)
    # 準備完了
