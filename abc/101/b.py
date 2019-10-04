

if __name__ == "__main__":
    N = input()
    Sn = 0
    for i in N:
        Sn += int(i)
    if (int(N)%Sn) == 0:
        print("Yes")
    else:
        print("No")
