package com.xmpl.leetcode;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class Solution0239Test {
    @ParameterizedTest
    @MethodSource("provider")
    void test(int[] numsInput, int k, int[] expected) {
        Solution0239 solution = new Solution0239();
        assertEquals(
                arrayToList(expected),
                arrayToList(solution.maxSlidingWindow(numsInput, k))
        );
    }

    private static Stream<Arguments> provider() {
        return Stream.of(
                Arguments.of(new int[] {1,3,-1,-3,5,3,6,7}, 3, new int[]{3, 3,5, 5, 6, 7}),
                Arguments.of(new int[] {1}, 1, new int[]{1})
        );
    }

    List<Integer> arrayToList(int[] array) {
        List<Integer> res = new ArrayList<>();
        for (int j : array) {
            res.add(j);
        }
        return res;
    }
}