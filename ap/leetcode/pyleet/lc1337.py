#
# Author: montreal91
# Time: 01:02
# Failed attempts: 0
#

class Solution:
    @staticmethod
    def kWeakestRows(mat, k):
        pq = [None for _ in range(len(mat))]

        for i, row in enumerate(mat):
            pq[i] = (i, rowStrength(row=row))

        pq.sort(key=lambda x: x[1])
        return [x[0] for i, x in enumerate(pq) if i < k]


def rowStrength(row):
    left = 0
    right = len(row) - 1
    while left < right:
        mid = (left + right) // 2
        if row[mid] == 1 and row[mid+1] == 0:
            return mid + 1
        elif row[mid] == 0 and row[mid+1] == 0:
            right = mid - 1
        elif row[mid] == 1 and row[mid+1] == 1:
            left = mid + 1

    if row[left] == 0:
        return left
    return left + 1


if __name__ == "__main__":
    M0 = [
        [0, 0],
        [1, 0],
        [1, 1],
    ]
    M1 = [
        [1,1,0,0,0],
        [1,1,1,1,0],
        [1,0,0,0,0],
        [1,1,0,0,0],
        [1,1,1,1,1]
    ]
    M2 = [
        [1,0,0,0],
        [1,1,1,1],
        [1,0,0,0],
        [1,0,0,0]
    ]
    s = Solution()

    assert rowStrength([0, 0, 0, 0, 0]) == 0
    assert rowStrength([1, 0, 0, 0, 0]) == 1
    assert rowStrength([1, 1, 0, 0, 0]) == 2
    assert rowStrength([1, 1, 1, 0, 0]) == 3
    assert rowStrength([1, 1, 1, 1, 0]) == 4
    assert rowStrength([1, 1, 1, 1, 1]) == 5

    assert rowStrength([0, 0, 0, 0, 0, 0]) == 0
    assert rowStrength([1, 0, 0, 0, 0, 0]) == 1
    assert rowStrength([1, 1, 0, 0, 0, 0]) == 2
    assert rowStrength([1, 1, 1, 0, 0, 0]) == 3
    assert rowStrength([1, 1, 1, 1, 0, 0]) == 4
    assert rowStrength([1, 1, 1, 1, 1, 0]) == 5
    assert rowStrength([1, 1, 1, 1, 1, 1]) == 6

    assert rowStrength([0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert rowStrength([1, 0, 0, 0, 0, 0, 0, 0]) == 1
    assert rowStrength([1, 1, 0, 0, 0, 0, 0, 0]) == 2
    assert rowStrength([1, 1, 1, 0, 0, 0, 0, 0]) == 3
    assert rowStrength([1, 1, 1, 1, 0, 0, 0, 0]) == 4
    assert rowStrength([1, 1, 1, 1, 1, 0, 0, 0]) == 5
    assert rowStrength([1, 1, 1, 1, 1, 1, 0, 0]) == 6
    assert rowStrength([1, 1, 1, 1, 1, 1, 1, 0]) == 7
    assert rowStrength([1, 1, 1, 1, 1, 1, 1, 1]) == 8

    assert s.kWeakestRows(M0, 1) == [0]
    assert s.kWeakestRows(M0, 2) == [0, 1]
    assert s.kWeakestRows(M0, 3) == [0, 1, 2]

    assert s.kWeakestRows(M1, 1) == [2]
    assert s.kWeakestRows(M1, 2) == [2, 0]
    assert s.kWeakestRows(M1, 3) == [2, 0, 3]
    assert s.kWeakestRows(M1, 4) == [2, 0, 3, 1]
    assert s.kWeakestRows(M1, 5) == [2, 0, 3, 1, 4]

    assert s.kWeakestRows(M2, 1) == [0]
    assert s.kWeakestRows(M2, 2) == [0, 2]
    assert s.kWeakestRows(M2, 3) == [0, 2, 3]
    assert s.kWeakestRows(M2, 4) == [0, 2, 3, 1]

    print("All tests passed.")
