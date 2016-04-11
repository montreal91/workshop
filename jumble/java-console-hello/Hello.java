/**
 * Created by montreal on 11/19/15.
 */

import java.util.*;

public class Hello {
    public static void main( String args[] ) {
        TreeMap<String, Long> class_map = new TreeMap<String, Long>();
        class_map.put("Boston", new Long(10));
        class_map.put("Barselona", new Long(30));
        class_map.put("Barnaul", new Long(30));
        class_map.put("Bombey", new Long(30));
        class_map.put("Adelaide", new Long(3859));
        class_map.put("Albukerque", new Long(1859));
        class_map.put("Canberra", new Long(19999999));
        class_map.put("Coro", new Long(991991));
        class_map.put("Cottbus", new Long(138));
        class_map.put("Cusco", new Long(221));
        class_map.put("Cusan", new Long(221));

        SortedMap<String, Long> sm = class_map.subMap("B", "Bz");
        // System.out.println(class_map);
        // System.out.println(sm);
        String s = "al";
        // System.out.println(s + "z");
        Long g = new Long(122);
        Long h = new Long(221);
        // System.out.println(g > h);
        long[] la = {3, 3, 3, 2, 1, 3 ,5};
        Arrays.sort(la);
        for (int i = 0; i < la.length; i++) {
            System.out.println(la[i]);
        }
    }
}
