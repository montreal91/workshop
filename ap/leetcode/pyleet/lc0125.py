#
# Author: montreal91
# Time: 0:10
# Failed attempts: 0
#

class Solution:
    def isPalindrome(self, s):
        processed = []
        for ch in s:
            if ch.isalnum():
                processed.append(ch.lower())

        if len(processed) == 0:
            return True

        N = len(processed)
        for i in range(N):
            if processed[i] != processed[N - i - 1]:
                return False

        return True


if __name__ == "__main__":
    assert Solution().isPalindrome(" a") == True
    assert Solution().isPalindrome(" ") == True
    assert Solution().isPalindrome("A man, a plan, a canal: Panama") == True
    assert Solution().isPalindrome("race a car") == False
    print("All tests passed")
