package com.xmpl.leetcode;

class Solution0033 {
    public int search(int[] nums, int target) {
        int maxInd = findIndOfMax(nums);
        int left, right;
        if (target < nums[0]) {
            left = maxInd + 1;
            right = nums.length - 1;
        } else {
            left = 0;
            right = maxInd;
        }
        return find(nums, left, right, target);
    }

    private int find(int[] nums, int left, int right, int target) {
        int mid;
        while (left < right) {
            mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }

            if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        return -1;
    }

    private int findIndOfMax(int[] nums) {
        int left = 0, right = nums.length - 1;
        int mid;
        while (left < right) {
            mid = (left + right) / 2;

            if (nums[mid] > nums[mid+1]) {
                return mid;
            }
            if (left == mid) {
                if (nums[left] > nums[right]) {
                    return left;
                }
                return right;
            }

            if (nums[left] > nums[mid]) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        return left;
    }
}
