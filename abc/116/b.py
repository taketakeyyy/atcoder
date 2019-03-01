
def func(n):
    if n%2 == 0:
        return n/2
    return 3*n+1

def solve():
    s = int(input())
    l = []
    l.append(s)

    n = s
    while True:
        n = func(n)

        flag = False
        for i in range(0, len(l)):
            if n == l[i]:
                flag = True
                break
        
        if flag:
            print(i+1)
            return
        
        l.append(n)


if __name__ == "__main__":
    solve()