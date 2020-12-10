//
// Problem: https://leetcode.com/problems/implement-trie-prefix-tree/
// Author: montreal91
// Solved in 0:54
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {

class TrieNode0208 {
  private bool isWord = false;
  private Dictionary<char, TrieNode0208> children = new Dictionary<char, TrieNode0208>();

  public void Insert(string s, int pos) {
    if (pos == s.Length) {
      isWord = true;
      return;
    }
    if (children.ContainsKey(s[pos])) {
      children[s[pos]].Insert(s, pos + 1);
    }
    else {
      children[s[pos]] = new TrieNode0208();
      children[s[pos]].Insert(s, pos + 1);
    }
  }

  public bool Search(string word, int pos) {
    if (pos == word.Length) {
      return isWord;
    }
    var whar = word[pos];
    if (!children.ContainsKey(whar)) {
      return false;
    }
    return children[whar].Search(word, pos + 1);
  }

  public bool StartsWith(string prefix, int pos) {
    if (prefix.Length == pos) {
      return children.Count > 0 || isWord;
    }
    var p = prefix[pos];
    if (!children.ContainsKey(p)) {
      return false;
    }
    return children[p].StartsWith(prefix, pos + 1);
  }
}

public class Trie0208 {
  private TrieNode0208 root = new TrieNode0208();

  public Trie0208() {}

  public void Insert(string word) {
    root.Insert(word, 0);
  }

  public bool Search(string word) {
    return root.Search(word, 0);
  }

  public bool StartsWith(string prefix) {
    return root.StartsWith(prefix, 0);
  }
}


class Solution0208 {
  public static void TestSolution() {
    var dict = new Trie0208();
    dict.Insert("diary");
    dict.Insert("dom");
    dict.Insert("domain");
    dict.Insert("dovakin");
    dict.Insert("propeller");
    dict.Insert("professional");
    dict.Insert("profession");
    dict.Insert("min");
    dict.Insert("max");
    dict.Insert("minmax");
    dict.Insert("maxmin");
    dict.Insert("marx");
    Debug.Assert(dict.Search("diary") == true);
    Debug.Assert(dict.Search("propeller") == true);
    Debug.Assert(dict.Search("professional") == true);
    Debug.Assert(dict.Search("profession") == true);
    Debug.Assert(dict.Search("min") == true);
    Debug.Assert(dict.Search("max") == true);
    Debug.Assert(dict.Search("minmax") == true);
    Debug.Assert(dict.Search("maxmin") == true);
    Debug.Assert(dict.Search("marx") == true);
    Debug.Assert(dict.Search("dom") == true);
    Debug.Assert(dict.Search("domain") == true);
    Debug.Assert(dict.Search("dovakin") == true);

    Debug.Assert(dict.Search("diaryz") == false);
    Debug.Assert(dict.Search("di") == false);
    Debug.Assert(dict.Search("professiona") == false);

    Debug.Assert(dict.StartsWith("d") == true);
    Debug.Assert(dict.StartsWith("di") == true);
    Debug.Assert(dict.StartsWith("dia") == true);
    Debug.Assert(dict.StartsWith("diar") == true);
    Debug.Assert(dict.StartsWith("diary") == true);
    Debug.Assert(dict.StartsWith("diaryx") == false);

    Debug.Assert(dict.StartsWith("da") == false);
    Debug.Assert(dict.StartsWith("x") == false);

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
