package com.xmpl.leetcode;

class Solution0714 {
    public int maxProfit(int[] prices, int fee) {
        if (prices.length < 1) {
            return 0;
        }
        int[] profits = new int[prices.length];
        int[] effectiveBuy = new int[prices.length];

        profits[0] = 0;
        effectiveBuy[0] = prices[0];

        for (int i = 1; i < prices.length; i++) {
            profits[i] = Math.max(
                    profits[i - 1],
                    prices[i] - effectiveBuy[i - 1] - fee
            );
            effectiveBuy[i] = Math.min(effectiveBuy[i - 1], prices[i] - profits[i]);
        }

        return profits[profits.length - 1];
    }
}
