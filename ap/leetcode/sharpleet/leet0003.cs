//
// Author: montreal91
// Solved in 0:35
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0003 {
  public int LengthOfLongestSubstring(string str) {
    var s = 0;
    var m = 0;
    var charmap = new Dictionary<char, int>();
    for (var i=0; i<str.Length; i++) {
      if (charmap.ContainsKey(str[i])) {
        s = Math.Max(s, charmap[str[i]] + 1);
      }
      m = Math.Max(m, i - s + 1);
      charmap[str[i]] = i;
    }
    return m;
  }

  public static void TestSolution() {
    var S = new Solution0003();
    Debug.Assert(S.LengthOfLongestSubstring("") == 0);
    Debug.Assert(S.LengthOfLongestSubstring("a") == 1);
    Debug.Assert(S.LengthOfLongestSubstring("aa") == 1);
    Debug.Assert(S.LengthOfLongestSubstring("ab") == 2);
    Debug.Assert(S.LengthOfLongestSubstring("aba") == 2);
    Debug.Assert(S.LengthOfLongestSubstring("abba") == 2);
    Debug.Assert(S.LengthOfLongestSubstring("abcda") == 4);
    Debug.Assert(S.LengthOfLongestSubstring("aabacda") == 4);
    Debug.Assert(S.LengthOfLongestSubstring("abcdaefa") == 6);
    Debug.Assert(S.LengthOfLongestSubstring("abcabcbb") == 3);
    Debug.Assert(S.LengthOfLongestSubstring("bbbbb") == 1);
    Debug.Assert(S.LengthOfLongestSubstring("pwwkew") == 3);
    Debug.Assert(S.LengthOfLongestSubstring("abaecbabcdeeabb") == 5);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
