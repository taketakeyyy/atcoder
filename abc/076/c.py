# -*- coding: utf-8 -*-

def zehnpaard():
    s = input()
    t = input()

    def match(s1, t):
        return all(a in (b, '?') for a, b in zip(s1, t))

    substrings = [s[i:i+len(t)] for i in range(len(s)-len(t)+1)]
    res = 'UNRESTORABLE'
    for ss in reversed(substrings):
        if match(ss, t):
            left, _, right = s.rpartition(ss)
            res = left + t + right
            res = res.replace('?', 'a')
            break
    print(res)

def main4():
    """ AC """
    s = input() # abcdr?tc????
    t = input() # coder

    def match(sub, t):
        for i in range(len(t)):
            if sub[i] == "?":
                continue
            if sub[i] == t[i]:
                continue
            return False
        return True

    substrings = []
    for i in range(len(s)-len(t)+1):
        substrings.append(s[i:i+len(t)])
    # s = c????c????
    # t = coder
    # のとき、辞書順最小の文字列にするためには c????coderにしなければならない。
    # ので、リストを逆順に走査する
    substrings = reversed(substrings)
    # substrings ==> ['c????', 'tc???', '?tc??', 'r?tc?', 'dr?tc', 'cdr?t', 'bcdr?', 'abcdr']

    for sub in substrings:
        if match(sub, t):
            left, _, right = s.rpartition(sub)
            result = (left + t + right).replace("?", "a")
            print(result)
            exit()
    print('UNRESTORABLE')


def main3():
    def product_mask_s(s, c):
        import itertools
        s_products = list(itertools.product(s, c))

        s_masks = []
        len_s = len(s)
        for products in itertools.product(range(2), repeat=len_s):
            t = ""
            for i in range(len_s):
                t += s_products[i][products[i]]
            s_masks.append(t)
        return s_masks

def main2():
    """ TLE WA """
    # atcoder
    # ?tc????
    # ?t?o?er
    import itertools
    s_prime = input()
    t_origin = input()
    len_t = len(t_origin)
    t_products = list(itertools.product(t_origin, "?"))

    t_kouho = []
    for products in itertools.product(range(2), repeat=len_t):
        t = ""
        for i in range(len_t):
            t += t_products[i][products[i]]
        t_kouho.append(t)

    for t in t_kouho:
        find_i = s_prime.find(t)
        if find_i == -1:
            continue
        # 見つかったなら、tを代入する
        ans = "{}{}{}".format(s_prime[:find_i], t_origin, s_prime[find_i+len_t:])
        print(ans.replace("?", "a"))
        exit()
    print("UNRESTORABLE")


def main():
    """ WA """
    s_change = lambda s, i, c: "{}{}{}".format(s[:i-1], c, s[i-1+1:])

    s_prime = input() # ?tc????
    t_origin = input()       # coder

    # s_prime の中から tの部分文字列の位置を探す
    len_t = len(t_origin)
    t = t_origin

    t_kouho = [t]
    for t_i in range(1, len_t):
        t_tail = s_change(t, len_t-t_i+1, "?")
        t_head = s_change(t, t_i, "?")
        if t_tail == t_head:
            t_kouho.append(t_tail)
        else:
            t_kouho.append(t_tail)
            t_kouho.append(t_head)
        t = s_change(t_tail, t_i, "?")
        if t == "?"*len_t:
            break
    print(t_kouho)

    for t in t_kouho:
        t_i = s_prime.find(t)
        if t_i == -1:
            continue
        # 見つかったなら、tを代入する
        ans = "{}{}{}".format(s_prime[:t_i], t_origin, s_prime[t_i+len_t:])
        print(ans.replace("?", "a"))
        exit()
    print("UNRESTORABLE")

if __name__ == '__main__':
    main4()
