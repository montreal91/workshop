//
// Problem: https://leetcode.com/problems/repeated-dna-sequences/
// Author: montreal91
// Solved in 0:29
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution0187 {
  private static readonly int L = 10;
  public IList<string> FindRepeatedDnaSequences(string s) {
    var tracker = new Dictionary<string, int>();
    string tmp;
    for (int i=0; i<s.Length - L + 1; i++) {
      tmp = s.Substring(i, L);
      if (tracker.ContainsKey(tmp)) {
        tracker[tmp]++;
      }
      else {
        tracker[tmp] = 1;
      }
    }
    var result = new List<string>();
    foreach (var entry in tracker) {
      if (entry.Value > 1) {
        result.Add(entry.Key);
      }
    }
    return result;
  }

  public static void TestSolution() {
    var leet1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    var leet2 = "AAAAAAAAAAAAA";
    var shord = "AAAA";
    var shord2 = "AAAAAAAAA";
    var my1 = "AGATAGTACAGATAGTACA";
    var my2 = "AAABBBBAAABBBBAAA";

    var S = new Solution0187();
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(leet1),
      new List<string>{"AAAAACCCCC","CCCCCAAAAA"}
    ));
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(leet2),
      new List<string>{"AAAAAAAAAA"}
    ));
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(shord),
      new List<string>{}
    ));
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(""),
      new List<string>{}
    ));
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(shord2),
      new List<string>{}
    ));
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(my1),
      new List<string>{"AGATAGTACA"}
    ));
    Debug.Assert(CompareLists(
      S.FindRepeatedDnaSequences(my2),
      new List<string>{"AAABBBBAAA"}
    ));

    Console.WriteLine("All tests passed.");
  }


  private static bool CompareLists(IList<string> one, IList<string> two) {
    if (one == null || two == null) {
      return false;
    }

    if (one.Count != two.Count) {
      return false;
    }
    for (int i=0; i<one.Count; i++) {
      if (one[i] != two[i]) {
        return false;
      }
    }
    return true;
  }
}

} // namespace leetsharp
