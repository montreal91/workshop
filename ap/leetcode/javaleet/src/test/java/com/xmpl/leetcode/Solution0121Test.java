package com.xmpl.leetcode;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class Solution0121Test {
    @ParameterizedTest
    @MethodSource("provider")
    void test(int[] prices, int expected) {
        Solution0121 s = new Solution0121();
        assertEquals(expected, s.maxProfit(prices));
    }

    private static Stream<Arguments> provider() {
        return Stream.of(
                Arguments.of(new int[] {7,1,5,3,6,4}, 5),
                Arguments.of(new int[] {7}, 0),
                Arguments.of(new int[] {7, 4}, 0),
                Arguments.of(new int[] {7, 4, 7}, 3),
                Arguments.of(new int[] {7,5, 4, 3}, 0)
        );
    }

}