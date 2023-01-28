# 19:35
# 19:55

class Solution:
    def topKFrequent(self, words, k):
        counter = {}
        for word in words:
            counter[word] = counter.get(word, 0) + 1

        records = sorted(counter.items(), key=lambda item: (-item[1], item[0]))
        return [records[i][0] for i in range(k)]


if __name__ == "__main__":
    assert Solution().topKFrequent(
        ["i","love","leetcode","i","love","coding"],
        2
    ) == ["i","love"]
    print("All tests passed.")
