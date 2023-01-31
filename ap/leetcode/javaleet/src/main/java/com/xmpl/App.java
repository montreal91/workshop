package com.xmpl;

import java.util.Set;
import java.util.TreeSet;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) {
        TreeSet<Integer> s = new TreeSet<>();
        s.add(1);
        s.add(2);
        s.add(10);
        s.add(4);
        System.out.println(s.last());
        System.out.println("Hello World!");
    }
}
