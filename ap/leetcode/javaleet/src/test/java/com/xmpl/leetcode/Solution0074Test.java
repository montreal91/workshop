package com.xmpl.leetcode;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class Solution0074Test {
    @ParameterizedTest
    @MethodSource("provider")
    void test(int[][] matrix, int number, boolean expected) {
        Solution0074 s = new Solution0074();
        assertEquals(expected, s.searchMatrix(matrix, number));
    }

    static Stream<Arguments> provider() {
        return Stream.of(
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 2, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 3, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 4, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 5, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 6, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 7, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 8, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 9, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 10, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 11, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 12, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 13, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 14, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 15, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}}, 16, true),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}, {18, 20, 22, 24}}, 17, false),
                Arguments.of(new int[][] {{2, 4, 6, 8}, {10, 12, 14, 16}, {18, 20, 22, 24}}, 18, true),
                Arguments.of(new int[][]{{1, 3}}, 3, true),
                Arguments.of(new int[][]{{1, 3}}, 1, true),
                Arguments.of(new int[][]{{1, 3}}, 2, false)
        );
    }

}