//
// Problem: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// Author: montreal91
// Solved in 0:31
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution0017 {
  private static readonly Dictionary<char, List<string>> tableau = new Dictionary<char, List<string>> {
    {'2', new List<string> {"a", "b", "c"}},
    {'3', new List<string> {"d", "e", "f"}},
    {'4', new List<string> {"g", "h", "i"}},
    {'5', new List<string> {"j", "k", "l"}},
    {'6', new List<string> {"m", "n", "o"}},
    {'7', new List<string> {"p", "q", "r", "s"}},
    {'8', new List<string> {"t", "u", "v"}},
    {'9', new List<string> {"w", "x", "y", "z"}}
  };


  public IList<string> LetterCombinations(string digits) {
    IList<string> product = new List<string>();
    if (String.IsNullOrEmpty(digits)) {
      return product;
    }
    product = tableau[digits[0]];
    for (int i=1; i<digits.Length; i++) {
      var d = digits[i];
      product = DescartesProduct(product, tableau[d]);
    }

    return product;
  }

  private IList<string> DescartesProduct(IList<string> setA, IList<string> setB) {
    IList<string> product = new List<string>();
    foreach (string sa in setA) {
      foreach (string sb in setB) {
        product.Add(sa + sb);
      }
    }
    return product;
  }

  public static void TestSolution() {
    Solution0017 S = new Solution0017();
    PrintList(S.LetterCombinations("234"));
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }

  private static void PrintList(IList<string> ls) {
    foreach(string s in ls) {
      Console.WriteLine(s);
    }
  }
}


} // namespace leetsharp
