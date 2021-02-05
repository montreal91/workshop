#
# Author: montreal91
# Type: practice
# Time: N/A
# Failed attempts: 1
#

def get_painting(A, B, C):
    result = [-1 for _ in enumerate(C)]

    painters = {}
    for i, ci in enumerate(C):
        if ci in painters:
            painters[ci].append(i)
        else:
            painters[ci] = [i]

    for i, _ in enumerate(A):
        if A[i] == B[i]:
            continue
        else:
            # look for available painter
            if B[i] not in painters:
                # No suitable painter available
                result[0] = -1
                return result
            ci = painters[B[i]].pop()
            result[ci] = i + 1
            if len(painters[B[i]]) == 0:
                painters.pop(B[i])

    # If algorithm reached this point all boards are properly painted.
    # We should find proper jobs for remaining painters

    boards = {}
    for i, bi in enumerate(B):
        boards[bi] = i

    painted = [False for _ in enumerate(A)]
    for i, _ in enumerate(C):
        ind = len(C) - i - 1
        if result[ind] > 0:
            painted[result[ind] - 1] = True
            continue
        # Try to find board wiht same colour
        if C[ind] in boards:
            painted[boards[C[ind]]] = True
            result[ind] = boards[C[ind]] + 1
            continue

        # Try to find board which will be painted later
        found = False
        for j, _ in enumerate(painted):
            if painted[j]:
                result[ind] = j + 1
                found = True
                break
        if not found:
            result[ind] = -1
            return result
    return result


def check_result(res):
    return res.count(-1) == 0


def solve(A, B, C):
    res = get_painting(A, B, C)
    if check_result(res):
        return "YES", tuple(map(str, res))
    return "NO", "NO"


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        n, m = list(map(int, input().split(" ")))
        A = list(map(int, input().split(" ")))
        B = list(map(int, input().split(" ")))
        C = list(map(int, input().split(" ")))
        answer = solve(A, B, C)
        print(answer[0])
        if (answer[0] == "YES"):
            print(" ".join(answer[1]))
