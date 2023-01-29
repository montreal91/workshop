package com.xmpl.leetcode;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// 15:30
// 16:15
class Solution0438 {
    private static final String LETTERS = "abcdefghijklmnopqrstuvwxyz";

    private Map<Character, Integer> makeMap() {
        Map<Character, Integer> res = new HashMap<>();
        for (int i = 0; i < LETTERS.length(); i++) {
            res.put(LETTERS.charAt(i), 0);
        }

        return res;
    }

    public List<Integer> findAnagrams(String s, String p) {
        if (s.length() < p.length()) {
            return List.of();
        }

        Map<Character, Integer> anagram = makeMap();
        for (int i = 0; i < p.length(); i++) {
            int count = anagram.getOrDefault(p.charAt(i), 0);
            anagram.put(p.charAt(i), count + 1);
        }

        Map<Character, Integer> tracker = makeMap();
        List<Integer> result = new ArrayList<>();

        for (int i = 0; i < p.length(); i++) {
            int count = tracker.getOrDefault(s.charAt(i), 0);
            tracker.put(s.charAt(i), count + 1);
        }

        if (tracker.equals(anagram)) {
            result.add(0);
        }

        int k;
        for (int i = p.length(); i < s.length(); i++) {
            // pop
            k = i - p.length();
            tracker.put(s.charAt(k), tracker.get(s.charAt(k)) - 1);

            // put
            int count = tracker.getOrDefault(s.charAt(i), 0);
            tracker.put(s.charAt(i), count + 1);

            if (tracker.equals(anagram)) {
                result.add(k + 1);
            }
        }

        return result;
    }
}
