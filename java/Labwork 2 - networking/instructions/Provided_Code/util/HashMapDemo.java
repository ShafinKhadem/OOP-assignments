package util;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

class HashMapDemo {
    public static void main(String args[]) {
        HashMap<String, Double> balance = new HashMap<>();
        String str;
        double bal;

        balance.put("John Doe", 3434.34);
        balance.put("Tom Smith", 123.22);
        balance.put("Jane Baker", null);
        balance.put("Tod Hall", 99.22);
        balance.put("Ralph Smith", -19.08);
        balance.put(null, 0.0);

        // show all balances in hashtable
        Set set = balance.keySet(); // get set view of keys
        // get iterator
        Iterator<String> itr = set.iterator();
        while (itr.hasNext()) {
            str = itr.next();
            System.out.println(str + ": " + balance.get(str));
        }
        System.out.println();
    }
}


