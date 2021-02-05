#
# Author: montreal91
# Type: contest
# Time: 01:06
# Failed attempts: 0
#

def fill_the_mountains(mounts, stones):
    finished = False
    i = 0
    k = 0
    last_stone = 0
    while not finished:
        if i >= len(mounts) - 1:
            finished = True
            return -1
        if k == stones:
            finished = True
            return last_stone

        if mounts[i+1] > mounts[i]:
            k += 1
            mounts[i] += 1
            last_stone = i + 1
            if i > 0 and mounts[i-1] < mounts[i]:
                i -= 1
        else:
            i += 1

    return None


if __name__ == '__main__':
    T = int(input())
    import time
    t1 = time.time()
    for _ in range(T):
        m, k = tuple(map(int, input().split(" ")))
        mountains = list(map(int, input().split(" ")))
        print(fill_the_mountains(mounts=mountains, stones=k))
    t2 = time.time()
