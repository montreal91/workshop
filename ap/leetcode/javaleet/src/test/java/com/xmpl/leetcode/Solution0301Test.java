package com.xmpl.leetcode;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.Collections;
import java.util.List;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class Solution0301Test {
    @ParameterizedTest
    @MethodSource("provider")
    void test(String input, List<String> expected) {
        Solution0301 s = new Solution0301();
        var answer = s.removeInvalidParentheses(input);
        Collections.sort(answer);
        assertEquals(expected, answer);
    }

    static Stream<Arguments> provider() {
        return Stream.of(
                Arguments.of("()", List.of("()")),
                Arguments.of("(()", List.of("()")),
                Arguments.of("(", List.of("")),
                Arguments.of("()())()", List.of("(())()", "()()()")),
                Arguments.of("(a)())()", List.of("(a())()", "(a)()()")),
                Arguments.of(")(", List.of("")),
                Arguments.of("((((((((((((((((((((aaaaa", List.of("aaaaa")),
                Arguments.of(")()(e()))))))((((", List.of("((e()))", "()(e())"))
//                Arguments.of("(((((((((aaaaa", List.of("aaaaa"))
        );
    }
}