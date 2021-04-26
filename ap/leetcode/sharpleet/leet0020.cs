//
// Problem: https://leetcode.com/problems/valid-parentheses/
// Author: montreal91
// Solved in 1:10
// Solution is accepted from the second attempt
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution20 {
  private List<char> lefts = new List<char>(new char[3]{'(', '[', '{'});
  private List<char> rights = new List<char>(new char[3]{')', ']', '}'});

  public bool IsValid(string s) {
    var bracketStack = new Stack<char>();
    foreach (char l in s) {
      if (lefts.Contains(l)) {
        bracketStack.Push(l);
        continue;
      }
      if (rights.Contains(l) && bracketStack.Count == 0) {
        return false;
      }
      if (rights.Contains(l) && ArePair(bracketStack.Peek(), l)) {
        bracketStack.Pop();
      }
      else {
        return false;
      }
    }
    return bracketStack.Count == 0;
  }

  private bool ArePair(char left, char right) {
    for (int i=0; i<3; i++) {
      if (lefts[i] == left && rights[i] == right) {
        return true;
      }
    }
    return false;
  }

  public static void TestSolution() {
    var solution = new Solution20();
    Debug.Assert(solution.IsValid("[]") == true);
    Debug.Assert(solution.IsValid("()") == true);
    Debug.Assert(solution.IsValid("{}") == true);
    Debug.Assert(solution.IsValid("[()]") == true);
    Debug.Assert(solution.IsValid("[{()}]") == true);
    Debug.Assert(solution.IsValid("[][]") == true);
    Debug.Assert(solution.IsValid("[]{}()") == true);
    Debug.Assert(solution.IsValid("[()()]{}([]{})") == true);

    Debug.Assert(solution.IsValid("[(])") == false);
    Debug.Assert(solution.IsValid("{[}]") == false);
    Debug.Assert(solution.IsValid("[[{]}]") == false);
    Debug.Assert(solution.IsValid("[][][][][][") == false);
    Debug.Assert(solution.IsValid("]") == false);
    Debug.Assert(solution.IsValid("[") == false);
    Debug.Assert(solution.IsValid("][") == false);
    Debug.Assert(solution.IsValid("(") == false);
    Debug.Assert(solution.IsValid(")") == false);
    Debug.Assert(solution.IsValid("{") == false);
    Debug.Assert(solution.IsValid("}") == false);
    Debug.Assert(solution.IsValid(")(") == false);
    Debug.Assert(solution.IsValid("}{") == false);
    Debug.Assert(solution.IsValid("{][}") == false);

    Console.WriteLine("All tests passed.");
  }
}

} // namespace leetsharp
