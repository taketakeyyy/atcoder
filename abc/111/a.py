# -*- coding: utf-8 -*-

def main():
    n = input()
    ans = ""
    for nn in n:
        if nn == "9":
            ans += "1"
        elif nn == "1":
            ans += "9"
    print(ans)


if __name__ == '__main__':
    main()
