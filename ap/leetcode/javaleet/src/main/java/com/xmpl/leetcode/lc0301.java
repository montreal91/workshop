package com.xmpl.leetcode;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;

class Solution0301 {
    public List<String> removeInvalidParentheses(String s) {
        Set<String> visited = new HashSet<>();
        Set<String> valid = new HashSet<>();

        Queue<String> queue = new ArrayDeque<>();
        boolean level = false;
        queue.add(s);

        String tmp;
        while (!queue.isEmpty()) {
            tmp = queue.poll();
            visited.add(tmp);
            if (isValid(tmp)) {
                valid.add(tmp);
                level = true;
            }

            if (level) {
                continue;
            }

            Set<String> newLevel = new HashSet<>();
            for (int i=0; i<tmp.length(); i++) {
                if (!isPar(tmp.charAt(i))) {
                    continue;
                }
                String newStr = tmp.substring(0, i) + tmp.substring(i + 1);

                if (!newLevel.contains(newStr) && !visited.contains(newStr)) {
                    queue.add(newStr);
                    newLevel.add(newStr);
                }

            }

        }

        return new ArrayList<>(valid);
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

    boolean isPar(char c) {
        return c == '(' || c == ')';
    }
}
