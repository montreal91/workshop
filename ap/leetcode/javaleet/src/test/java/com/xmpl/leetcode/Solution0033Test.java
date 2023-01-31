package com.xmpl.leetcode;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class Solution0033Test {
    @ParameterizedTest
    @MethodSource("provider")
    void test(int[] nums, int target, int expected) {
        Solution0033 s = new Solution0033();
        assertEquals(expected, s.search(nums, target));
    }

    private static Stream<Arguments> provider() {
        return Stream.of(
                Arguments.of(new int[] {1}, 1, 0),
                Arguments.of(new int[] {1}, 2, -1),
                Arguments.of(new int[] {0, 2}, -1, -1),
                Arguments.of(new int[] {0, 2}, 0, 0),
                Arguments.of(new int[] {0, 2}, 1, -1),
                Arguments.of(new int[] {0, 2}, 2, 1),
                Arguments.of(new int[] {0, 2}, 3, -1),
                Arguments.of(new int[] {2, 0}, -1, -1),
                Arguments.of(new int[] {2, 0}, 0, 1),
                Arguments.of(new int[] {2, 0}, 1, -1),
                Arguments.of(new int[] {2, 0}, 2, 0),
                Arguments.of(new int[] {2, 0}, 3, -1),
                Arguments.of(new int[] {0, 2, 4}, -1, -1),
                Arguments.of(new int[] {0, 2, 4}, 0, 0),
                Arguments.of(new int[] {0, 2, 4}, 1, -1),
                Arguments.of(new int[] {0, 2, 4}, 2, 1),
                Arguments.of(new int[] {0, 2, 4}, 3, -1),
                Arguments.of(new int[] {0, 2, 4}, 4, 2),
                Arguments.of(new int[] {0, 2, 4}, 5, -1),

                Arguments.of(new int[] {4, 0, 2}, -1, -1),
                Arguments.of(new int[] {4, 0, 2}, 0, 1),
                Arguments.of(new int[] {4, 0, 2}, 1, -1),
                Arguments.of(new int[] {4, 0, 2}, 2, 2),
                Arguments.of(new int[] {4, 0, 2}, 3, -1),
                Arguments.of(new int[] {4, 0, 2}, 4, 0),
                Arguments.of(new int[] {4, 0, 2}, 5, -1),

                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, -1, -1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 0, 4),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 1, -1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 2, 5),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 3, -1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 4, 0),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 5, -1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 6, 1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 7, -1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 8, 2),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 9, -1),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 10, 3),
                Arguments.of(new int[] {4, 6, 8, 10, 0, 2}, 11, -1)
        );
    }
}