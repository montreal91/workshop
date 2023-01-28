# 19:23
# 19:40

class Solution:
    def merge(self, intervals):
        intervals.sort()
        res = []
        curr = intervals[0]
        for interval in intervals:
            if interval[0] <= curr[1]:
                curr[1] = max(curr[1], interval[1])
            else:
                res.append(curr)
                curr = interval
        res.append(curr)
        return res


if __name__ == "__main__":
    assert Solution().merge([[1,3],[2,6],[8,10],[15,18]]) == [[1,6],[8,10],[15,18]]
    assert Solution().merge([[1,4],[4,5]]) == [[1,5]]
    assert Solution().merge([[1,3],[4,5]]) == [[1,3],[4,5]]
    assert Solution().merge([[1,3],[4,5],[2,10]]) == [[1, 10]]
    print("All tests passed.")