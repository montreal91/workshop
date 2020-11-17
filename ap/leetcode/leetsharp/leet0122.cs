//
// Problem: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
// Author: montreal91
// Solved in 0:51
//

using System;
using System.Diagnostics;


namespace leetsharp {


class Solution {
  public int MaxProfit(int[] prices) {
    int profit = 0;
    int bought = prices[0];
    int i;
    for (i=1; i<prices.Length; i++) {
      if (prices[i] > prices[i-1]) {
        // Growth, do nothing;
      }
      else {
          profit += Math.Max(0, prices[i-1] - bought);
          bought = prices[i];
      }
      bought = Math.Min(bought, prices[i]);
    }
    profit += Math.Max(0, prices[prices.Length-1] - bought);
    Console.WriteLine($"The answer: {profit}");
    return profit;
  }

  public static void TestSolution() {
    var leet0 = new int[] {7,1,5,3,6,4}; // expected 7
    var leet1 = new int[] {1,2,3,4,5}; // expected 4
    var leet2 = new int[] {7,6,4,3,1}; // expected 0
    var minIn = new int[] {10}; // 0
    var my1 = new int[] {5, 6, 3, 4, 1, 2, 1, 2, 1, 4, 3, 6, 5};
    var my2 = new int[] {3, 1, 2, 5, 4, 5}; // 5
    var my3 = new int[] {3, 1, 2, 5, 5, 6}; // 5

    var S = new Solution();
    Debug.Assert(S.MaxProfit(leet0) == 7);
    Debug.Assert(S.MaxProfit(leet1) == 4);
    Debug.Assert(S.MaxProfit(leet2) == 0);
    Debug.Assert(S.MaxProfit(minIn) == 0);
    Debug.Assert(S.MaxProfit(my1) == 10);
    Debug.Assert(S.MaxProfit(my2) == 5);
    Debug.Assert(S.MaxProfit(my3) == 5);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
