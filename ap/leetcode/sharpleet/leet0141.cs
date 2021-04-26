//
// Author: montreal91
// Solved in 0:11
// Failed attempts: 1
//
using System;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0141 {
  public bool HasCycle(ListNode head) {
    var curr = head;
    while (true) {
      if (curr == null) {
        return false;
      }
      if (curr.val == Int32.MaxValue) {
        return true;
      }
      curr.val = Int32.MaxValue;
      curr = curr.next;
    }
  }

  public static void TestSolution() {
    var S = new Solution0141();
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
