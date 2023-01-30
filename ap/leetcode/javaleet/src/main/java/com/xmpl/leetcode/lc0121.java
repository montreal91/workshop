package com.xmpl.leetcode;

import java.util.ArrayList;
import java.util.List;

// 13:20
// 13:35
class Solution0121 {
    public int maxProfit(int[] prices) {
        if (prices.length == 0) {
            return 0;
        }

        int toBuy = prices[0];
        int profit = 0;

        for (int i=1; i<prices.length; i++) {
            toBuy = Math.min(toBuy, prices[i]);
            profit = Math.max(profit, prices[i] - toBuy);
        }

        return profit;
    }
}
