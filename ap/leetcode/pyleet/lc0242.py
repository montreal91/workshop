#
# Author: montreal91
# Time: 0:14
# Failed attempts: 0
#

class Solution:
    def isAnagram(self, first, second):
        if len(first) != len(second):
            return False
        counter1 = {}
        for l in first:
            if not l in counter1:
                counter1[l] = 1
            else:
                counter1[l] += 1

        counter2 = {}
        for m in second:
            if not m in counter2:
                counter2[m] = 1
            else:
                counter2[m] += 1

        return counter1 == counter2


if __name__ == "__main__":
    assert Solution().isAnagram("anagram", "nagaram")
    assert not Solution().isAnagram("car", "rat")
    assert not Solution().isAnagram("car", "cars")
    print("All tests passed.")
