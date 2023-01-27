
#
# Author: montreal91
# Time: 0:15
# Failed attempts: 0
#

class Solution:
    def restoreString(self, s, indices):
        res = [c for c in s]
        for i, ind in enumerate(indices):
            res[ind] = s[i]
        return "".join(res)


if __name__ == "__main__":
    assert Solution().restoreString("codeleet", [4,5,6,7,0,2,1,3]) == "leetcode"
    assert Solution().restoreString("abc", [0, 1, 2]) == "abc"
    assert Solution().restoreString("abc", [0, 2, 1]) == "acb"
    assert Solution().restoreString("abc", [1, 0, 2]) == "bac"
    assert Solution().restoreString("abc", [1, 2, 0]) == "cab"
    assert Solution().restoreString("abc", [2, 0, 1]) == "bca"
    assert Solution().restoreString("abc", [2, 1, 0]) == "cba"
    print("All tests passed.")
