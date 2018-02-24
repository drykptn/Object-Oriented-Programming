
package hw7;

import javafx.util.Pair;

/**
 *
 * @author derya
 */
public class Hw7 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    
        try{
            GTUSet<Integer> setA = new GTUSet<>();
            GTUSet<Integer> setB = new GTUSet<>();
            GTUSet<Integer> setC;
            for (int i = 10; i >= 0; i--) 
                setA.insert(i);

            //setA.insert(2);        // ayni elemani eklerse exception firlatir

            for (int i = 0; i < 10; i++) 
                setB.insert(i*4);


            System.out.print("setA print ediliyor\n");
            setA.printArr();
            System.out.print("\n\n");
            GTUSet<Integer>.GTUIterator<Integer> it = (GTUSet.GTUIterator)setA.find(4);
            System.out.print("setA da find(4) un iter.next i\n\n");
            System.out.print(it.next());
            System.out.print("\n\n");

            System.out.print("setA dan eleman silindi - 7\n\n");
            setA.erase(7);
            System.out.print("setA print ediliyor\n\n");
            setA.printArr();
            System.out.print("setB print ediliyor\n\n");
            setB.printArr();
            setC = (GTUSet<Integer>) setA.intersection(setB);

            System.out.print("\nsetA ve setB intersect\n");
            setC.printArr();
            System.out.print("\n");

            GTUMap<Integer, Integer> map1 = new GTUMap();
            map1.insert(new Pair<>(1,2));
            map1.insert(new Pair<>(3,6));
            map1.insert(new Pair<>(2,8));
            map1.insert(new Pair<>(6,4));
            map1.insert(new Pair<>(4,9));
            System.out.print("map1 print ediliyor\n\n");
            map1.printArr();
            System.out.print("\n\n");

           // map1.printArr();

            GTUMap<Integer, Integer> map2 = new GTUMap<>();
            Pair p = new Pair<>(1,10);
            map2.insert(p);
            Pair p2 = new Pair<>(4,0);
            map2.insert(p2);

            GTUSet<Integer>.GTUIterator<Integer> itr = (GTUSet.GTUIterator)map2.find(p);
            System.out.print("İter->next\n\n");
            System.out.print(itr.next());
            System.out.print("\n\n");
            System.out.print("map2 print\n\n");
            map2.printArr();
            System.out.print("\nerase p pairi\n\n");
            map2.erase(p);
            System.out.print("map2 print\n\n");
            map2.printArr();
            GTUMap<Integer, Integer> map3;
        }catch(Exception e){
             System.out.println("Exception occurred");
        }
    
    }
}