#
# Author: montreal91
# Time: 1:00
# Failed attempts: 0
#

import unittest


class TrieNode:
    def __init__(self):
        self._letters = {}
        self._is_word = False

    def addWord(self, word, ind):
        if ind == len(word):
            self._is_word = True
            return

        c = word[ind]
        if not c in self._letters:
            self._letters[c] = TrieNode()

        self._letters[c].addWord(word, ind + 1)

    def search(self, word, ind):
        if ind == len(word):
            return self._is_word

        c = word[ind]
        if c == ".":
            for child in self._letters.values():
                if child.search(word, ind + 1):
                    return True
            return False

        if c in self._letters:
            return self._letters[c].search(word, ind + 1)

        return False


class WordDictionary:
    def __init__(self):
        self._root = TrieNode()

    def addWord(self, word):
        self._root.addWord(word, 0)

    def search(self, word):
        return self._root.search(word, 0)


TEST_WORDS = (
    "a",
    "an",
    "and",
    "am",
    "i",
    "is",
    "it",
    "its",
    "saw",
    "see",
    "super",
    "summon",
    "supper",
    "supply",
    "sea",
    "sun",
    "sand",
    "sight",
    "trie",
    "tree",
    "trunk",
    "trust",
    "trump",
    "trick",
    "tampa",
    "this",
    "that",
    "those"
)

TEST_FALSE_WORDS = (
    "as",
    "in",
    "saws",
    "sum",
    "arse"
)

TEST_TRUE_PATTERNS = (
    ".",
    "..",
    "...",
    "a.",
    "s.n",
    "..nd",
    "t...",
    "t...."
)

TEST_FALSE_PATTERNS = (
    "t.",
    "t..",
    "t..z",
    "t...z",
    "t.....",
    "........."
)

class SolutionTests(unittest.TestCase):
    def test_basics(self):
        dictionary = WordDictionary()

        for word in TEST_WORDS:
            self.assertFalse(dictionary.search(word))
            dictionary.addWord(word)
            self.assertTrue(dictionary.search(word))

        for word in TEST_FALSE_WORDS:
            self.assertFalse(dictionary.search(word))

    def test_patterns(self):
        dictionary = WordDictionary()
        for word in TEST_WORDS:
            dictionary.addWord(word)

        for pattern in TEST_TRUE_PATTERNS:
            self.assertTrue(dictionary.search(pattern))

        for fpattern in TEST_FALSE_PATTERNS:
            self.assertFalse(dictionary.search(fpattern), fpattern)


if __name__ == "__main__":
    unittest.main()
