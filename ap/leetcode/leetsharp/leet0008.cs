//
// Problem: https://leetcode.com/problems/string-to-integer-atoi/
// Author: montreal91
// Solved in 01:30
// Failed attempts: 1
//

using System;
using System.Numerics;
using System.Diagnostics;


namespace leetsharp {


class Solution0008 {
  private static readonly char space = ' ';
  private static readonly char minus = '-';
  private static readonly char plus = '+';

  public int MyAtoi(string s) {
    long tmp = StringToInteger(Trim(s));
    return (int) Math.Max(Int32.MinValue, Math.Min(Int32.MaxValue, tmp));
  }

  private string Trim(string s) {
    for (int i=0; i<s.Length; i++) {
      if (Char.IsDigit(s[i]) || s[i] == minus || s[i] == plus) {
        return ReadNumber(s, i);
      }
      if (s[i] != space) {
        return "";
      }
    }
    return "";
  }

  private int StringToInteger(string s) {
    BigInteger res = 0;
    BigInteger power = 1;
    int last = s.Length - 1;
    int zero = '0';
    for (int i=0; i<s.Length; i++) {
      if (s[last-i] == minus) {
        res *= -1;
      } 
      else if(s[last-i] == plus) {
        res *= +1;
      }
      else {
        res += (s[last - i] - zero) * power;
      }
      power *= 10;
    }
    return (int) BigInteger.Max(Int32.MinValue, BigInteger.Min(Int32.MaxValue, res));
  }

  private string ReadNumber(string s, int pos) {
    int end = 0;
    int i = pos;
    if (s[i] == minus || s[i] == plus) {
      i++;
    }
    for (;i<s.Length; i++) {
      if (!Char.IsDigit(s[i])) {
        end=i;
        break;
      }
    }
    end = i;
    return s.Substring(pos, end-pos);
  }

  public static void TestSolution() {
    var S = new Solution0008();
    Debug.Assert(S.MyAtoi("") == 0);
    Debug.Assert(S.MyAtoi(" ") == 0);
    Debug.Assert(S.MyAtoi("-") == 0);
    Debug.Assert(S.MyAtoi("abc") == 0);
    Debug.Assert(S.MyAtoi("abc10") == 0);
    Debug.Assert(S.MyAtoi("- 10") == 0);
    Debug.Assert(S.MyAtoi("10") == 10);
    Debug.Assert(S.MyAtoi("-10") == -10);
    Debug.Assert(S.MyAtoi("-91283472332") == Int32.MinValue);
    Debug.Assert(S.MyAtoi("9128347233290123") == Int32.MaxValue);
    Debug.Assert(S.MyAtoi("-10 and words") == -10);
    Debug.Assert(S.MyAtoi("-289.300") == -289);
    Debug.Assert(S.MyAtoi("+289300") == 289300);
    Debug.Assert(S.MyAtoi("-10 and words") == -10);
    Debug.Assert(S.MyAtoi("9223372036854775808") == 2147483647);
    Debug.Assert(S.MyAtoi("92233720368547758089223372036854775808922337203685477580892233720368547758089223372036854775808922337203685477580892233720368547758089223372036854775808") == 2147483647);
    Debug.Assert(S.MyAtoi("-92233720368547758089223372036854775808922337203685477580892233720368547758089223372036854775808922337203685477580892233720368547758089223372036854775808") == Int32.MinValue);
    Console.WriteLine("All tests passed.");
  }
}

} // namespace leetsharp
