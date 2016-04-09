/**
 * Created by montreal on 11/19/15.
 */

import java.util.*;

public class Hello {
    public static void main( String args[] ) {
        TreeMap<String, Long> class_map = new TreeMap<String, Long>();
        class_map.put("Zelenograd", new Long(5));
        class_map.put("Memphis", new Long(10));
        class_map.put("Quatar", new Long(15));
        class_map.put("Quirrell", new Long(20));
        class_map.put("Zibo", new Long(25));
        class_map.put("Moscow", new Long(30));
        class_map.put("Monte Carlo", new Long(35));
        class_map.put("Luisiana", new Long(40));
        class_map.put("Amsterdam", new Long(45));
        class_map.put("Adelaide", new Long(45));
        class_map.put("Atlanta", new Long(45));
        class_map.put("Boston", new Long(50));
        class_map.put("Bangkok", new Long(55));
        class_map.put("Mozambique", new Long(60));
        class_map.put("Amsterdam", new Long(65));
        class_map.put("Mazda", new Long(70));
        class_map.put("MazdaMan", new Long(75));
        class_map.put("ZZZ", new Long(80));
        class_map.put("ZzZ", new Long(85));
        class_map.put("ZElenograd", new Long(90));


        SortedMap<String, Long> sm = class_map.subMap("Ad", "Zez");
        // System.out.println(class_map);
        System.out.println(sm);
    }
}
