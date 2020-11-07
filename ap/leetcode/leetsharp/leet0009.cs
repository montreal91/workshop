
//
// Problem: https://leetcode.com/problems/palindrome-number/
// Author: montreal91
// Solved in 1:05
//

using System;
using System.Diagnostics;
using System.Numerics;

namespace leetsharp {


class Solution {
  public bool IsPalindrome(BigInteger x) {
    if (x < 0) {
      return false;
    }
    int digits = (int) Math.Log10((double)x) + 1;
    for (int i = 0; i < digits / 2; i++) {
      if (GetDigitAtPos(x, digits - i) != GetDigitAtPos(x, i + 1)) {
        return false;
      }
    }
    return true;
  }

  private static int GetDigitAtPos(BigInteger number, int pos) {
    BigInteger numBase = 10;
    BigInteger i = BigInteger.Pow(numBase, pos);
    BigInteger j = i / numBase;
    try {
      return (int)((number % i - number % j) / j);
    } catch (OverflowException) {
      return -1;
    }
  }

  public static void TestSolution() {
    var s = new Solution();
    TestGetDigit();
    Debug.Assert(s.IsPalindrome(0) == true);
    Debug.Assert(s.IsPalindrome(11) == true);
    Debug.Assert(s.IsPalindrome(101) == true);
    Debug.Assert(s.IsPalindrome(1111) == true);
    Debug.Assert(s.IsPalindrome(12321) == true);
    Debug.Assert(s.IsPalindrome(554455) == true);
    Debug.Assert(s.IsPalindrome(89734543798) == true);
    Debug.Assert(s.IsPalindrome(-1) == false);
    Debug.Assert(s.IsPalindrome(-11) == false);
    Debug.Assert(s.IsPalindrome(-20) == false);
    Debug.Assert(s.IsPalindrome(65536) == false);
    Debug.Assert(s.IsPalindrome(61) == false);

    Console.WriteLine("All tests passed.");
  }

  private static void TestGetDigit() {
    Debug.Assert(Solution.GetDigitAtPos(10, 2) == 1);
    Debug.Assert(Solution.GetDigitAtPos(10, 1) == 0);
    Debug.Assert(Solution.GetDigitAtPos(11, 1) == 1);
    Debug.Assert(Solution.GetDigitAtPos(65536, 5) == 6);
    Debug.Assert(Solution.GetDigitAtPos(65536, 4) == 5);
    Debug.Assert(Solution.GetDigitAtPos(65536, 3) == 5);
    Debug.Assert(Solution.GetDigitAtPos(65536, 2) == 3);
    Debug.Assert(Solution.GetDigitAtPos(65536, 1) == 6);
  }
}

} // namespace leetsharp
