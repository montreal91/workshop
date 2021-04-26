//
// Problem: https://leetcode.com/problems/longest-word-in-dictionary/
// Author: montreal91
// Solved in 1:26
// Failed attempts: 2
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Trie0720 {
  private Trie0720 parent;
  private readonly string value;
  private bool isWord;
  private readonly Dictionary<char, Trie0720> children;

  public Trie0720(string value) {
    this.parent = null;
    this.value = value;
    this.isWord = value.Length == 0;
    this.children = new Dictionary<char, Trie0720>();
  }

  public void AddWord(string word) {
    if (word.Length == 0) {
      isWord = true;
      return;
    }

    char firstLetter = word[0];
    if (!children.ContainsKey(firstLetter)) {
      var newChild = new Trie0720(firstLetter.ToString());
      newChild.parent = this;
      children[firstLetter] = newChild;
    }
    children[firstLetter].AddWord(word.Substring(1));
  }

  public string GetLongestWord() {
    var resultArr = new List<string>();
    foreach (var node in children.Values) {
      node.CollectWords(resultArr, new List<char>());
    }
    return FindLongMin(resultArr);
  }

  private void CollectWords(List<string> collection, List<char> letters) {
    letters.Add(value[0]);
    if (isWord && CanConstruct(this)) {
      collection.Add(new string(letters.ToArray()));
    }
    foreach (var node in children.Values) {
      node.CollectWords(collection, new List<char>(letters));
    }
  }

  private string FindLongMin(List<string> words) {
    string res = "";
    foreach (var word in words) {
      if (word.Length > res.Length) {
        res = word;
      }
      else if (word.Length == res.Length && word.CompareTo(res) < 0) {
        res = word;
      }
    }
    return res;
  }

  private bool CanConstruct(Trie0720 node) {
    var curr = node;
    while (curr.value != "") {
      if (!curr.isWord) {
        return false;
      }
      curr = curr.parent;
    }
    return true;
  }

  private void PrintArray(List<string> arr) {
    foreach(var v in arr) {
      Console.WriteLine(v);
    }
  }
}

class Solution0720 {
  public string LongestWord(string[] words) {
    var trieRoot = new Trie0720("");
    foreach (var word in words) {
      trieRoot.AddWord(word);
    }
    return trieRoot.GetLongestWord();
  }

  public static void TestSolution() {
    var leetDict1 = new string[]{"w","wo","wor","worl", "world"};
    var leetDict2 = new string[]{"a", "banana", "app", "appl", "ap", "apply", "apple"};
    var short1 = new string[]{"a"};
    var short2 = new string[]{"aa"};
    var case1 = new string[]{"w","wo","wor", "world"};
    var reversedCase1 = new string[]{"world", "wor", "wo", "w"};
    var manyEqual = new string[]{"baka", "ba", "boku", "bo"};
    var leetErrorCase = new string[]{"m","mo","moc","moch","mocha","l","la","lat","latt","latte","c","ca","cat"};

    var S = new Solution0720();
    Debug.Assert(S.LongestWord(leetDict1) == "world");
    Debug.Assert(S.LongestWord(leetDict2) == "apple");
    Debug.Assert(S.LongestWord(short1) == "a");
    Debug.Assert(S.LongestWord(short2) == "");
    Debug.Assert(S.LongestWord(case1) == "wor");
    Debug.Assert(S.LongestWord(reversedCase1) == "wor");
    Debug.Assert(S.LongestWord(manyEqual) == "");
    Debug.Assert(S.LongestWord(leetErrorCase) == "latte");

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
