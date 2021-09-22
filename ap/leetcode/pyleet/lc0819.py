#
# Author: montreal91
# Time: 0:33
# Failed attempts: 0
#

class Solution:
    def mostCommonWord(self, paragraph, banned):
        banned = frozenset(banned)
        counter = {}
        for word in split_words(paragraph):
            if word in banned:
                continue

            if word in counter:
                counter[word] += 1
            else:
                counter[word] = 1
        return get_best(counter)


def split_words(paragraph):
    separators = " !?',;."
    start = 0
    for i, s in enumerate(paragraph):
        if s in separators:
            word = paragraph[start:i]
            start = i+1
            if len(word) > 0:
                yield word.lower()
    
    word = paragraph[start:len(paragraph)]
    if len(word) > 0:
        yield word.lower()


def get_best(counter):
    return max(counter.items(), key=lambda x: x[1])[0]


if __name__ == "__main__":
    assert Solution().mostCommonWord("a.", "") == "a"
    print("All tests passed.")
