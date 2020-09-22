# -*- coding: utf-8 -*-

def main():
    import itertools
    nums = [int(c) for c in input()]
    ops = itertools.product(["+","-"], repeat=3)
    for op in ops:
        s = "{}{}{}{}{}{}{}".format(nums[0], op[0],
                                    nums[1], op[1],
                                    nums[2], op[2],
                                    nums[3])
        if eval(s) == 7:
            print(s + "=7")
            exit()


if __name__ == '__main__':
    main()
