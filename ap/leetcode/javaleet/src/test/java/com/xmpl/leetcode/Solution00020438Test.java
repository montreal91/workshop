package com.xmpl.leetcode;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.List;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class Solution00020438Test {
    @ParameterizedTest
    @MethodSource("testProvider")
    void test(String input, String anagram, List<Integer> expected) {
        Solution0438 s = new Solution0438();
        assertEquals(expected, s.findAnagrams(input, anagram));
    }

    static Stream<Arguments> testProvider() {
        return Stream.of(
                Arguments.arguments("cbaebabacd", "abc", List.of(0, 6)),
                Arguments.arguments("abab", "ab", List.of(0, 1, 2)),
                Arguments.arguments("cbaebabacd", "acd", List.of(7)),
                Arguments.arguments("aa", "aaa", List.of())
        );
    }
}
