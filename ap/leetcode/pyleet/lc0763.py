# 20:00
# 20:30

class Solution:
    def partitionLabels(self, s):
        counter = {}
        for i, l in enumerate(s):
            if l in counter:
                counter[l][1] = i
            else:
                counter[l] = [i, i]

        intervals = sorted(list(counter.values()))
        merged = []
        curr = intervals[0]

        for interval in intervals:
            if interval[0] <= curr[1]:
                curr[1] = max(curr[1], interval[1])
            else:
                merged.append(curr)
                curr = interval

        merged.append(curr)
        return [ivl[1] - ivl[0] + 1 for ivl in merged]


if __name__ == "__main__":
    assert Solution().partitionLabels("a")  == [1]
    assert Solution().partitionLabels("ababcbacadefegdehijhklij")  == [9,7,8]
    assert Solution().partitionLabels("eccbbbbdec")  == [10]
    assert Solution().partitionLabels("abc") == [1,1,1]
    assert Solution().partitionLabels("aaaa") == [4]
    print("All tests passed.")
