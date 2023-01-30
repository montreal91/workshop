package com.xmpl.leetcode;

class Solution0074 {
    public boolean searchMatrix(int[][] matrix, int target) {
        int row = findRow(matrix, target);
        if (row == -1) {
            return false;
        }
        return findInRow(matrix[row], target);
    }

    int findRow(int[][] matrix, int target) {
        int left = 0, right = matrix.length - 1;
        int mid;
        int last = matrix[0].length - 1;

        if (target < matrix[0][0] || matrix[right][last] < target) {
            return -1;
        }

        while (true) {
            mid = (left + right) / 2;
            if (mid == matrix.length - 1) {
                if (matrix[mid][last] < target) {
                    return -1;
                }
                return mid;
            }
            if (matrix[mid][0] <= target && target < matrix[mid + 1][0]) {
                return mid;
            }

            if (matrix[mid][last] < target) {
                left = mid + 1;
            }
            if (target < matrix[mid][0]) {
                right = mid - 1;
            }
        }
    }

    boolean findInRow(int[] row, int target) {
        int left = 0, right = row.length - 1;
        int mid;

        if (target < row[0] || row[row.length - 1] < target) {
            return false;
        }

        while (true) {
            mid = (left + right) / 2;

            if (row[mid] == target) {
                return true;
            }

            if (mid > 0) {
                if (row[mid - 1] < target && target <row[mid]) {
                    return false;
                }
            }

            if (row[mid] < target) {
                left = mid + 1;
            }
            if (target < row[mid]) {
                right = mid - 1;
            }
        }
    }
}
