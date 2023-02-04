package com.xmpl.leetcode;


import java.util.ArrayDeque;
import java.util.Deque;

class MonotonicQueue {
    private Deque<Integer> queue;

    MonotonicQueue() {
        queue = new ArrayDeque<>();
    }

    int max() {
        return queue.peekFirst();
    }

    void push(int k) {
        while (!queue.isEmpty() && queue.peekLast() < k) {
            queue.removeLast();
        }
        queue.addLast(k);
    }

    void pop(int k) {
        if (!queue.isEmpty() && queue.peekFirst() == k) {
            queue.removeFirst();
        }
    }
}

class Solution0239 {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int[] res = new int[nums.length - k + 1];

        MonotonicQueue mq = new MonotonicQueue();
        for (int i = 0; i < k; i++) {
            mq.push(nums[i]);
        }

        res[0] = mq.max();

        for (int i = k; i < nums.length; i++) {
            mq.pop(nums[i - k]);
            mq.push(nums[i]);
            res[i - k + 1] = mq.max();
        }

        return res;
    }
}
