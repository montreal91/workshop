package com.xmpl.leetcode;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class Solution0301c {
    List<String> removeInvalidParentheses(String s) {
        Set<String> res = new HashSet<>();
        int rmL = 0, rmR = 0;
        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == '(') rmL++;
            if(s.charAt(i) == ')') {
                if(rmL != 0) rmL--;
                else rmR++;
            }
        }

        int k = rmL + rmR;
        helper(s, res, new StringBuilder(), 0, s.length() - k);

        List<String> answer = new ArrayList<>();
        for (String ss : res) {
            if (isValid(ss)) {
                answer.add(ss);
            }
        }
        return answer;
    }

    void helper(String s, Set<String> res, StringBuilder sb, int pos, int k) {
        if (sb.length() == k) {
            res.add(sb.toString());
            return;
        }
        if (pos >= s.length()) {
            return;
        }

        int len = sb.length();

        // adding case
        sb.append(s.charAt(pos));
        helper(s, res, sb, pos + 1, k);
        sb.setLength(len);

        // non-adding case
        helper(s, res, sb, pos + 1, k);
        sb.setLength(len);
    }

    boolean isValid(String s) {
        int count = 0;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') count++;
            if (c == ')') {
                if (count == 0) return false;
                count--;
            }
        }
        return count == 0;
    }
}
