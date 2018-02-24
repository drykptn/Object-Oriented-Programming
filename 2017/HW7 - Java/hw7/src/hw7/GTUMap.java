package hw7;

import java.security.InvalidParameterException;


/**
 *
 * @author derya
 * @param <T>
 * @param <V>
 */
public class GTUMap<T, V> extends GTUSet< javafx.util.Pair <T, V>>{
    public V at(T k){
        for (int i = 0; i < this.size(); i++) {
            if(k.equals(this.get(i).getKey()))
                return this.get(i).getValue();
        }
        throw new InvalidParameterException();
    }

    /**
     *
     * @param key
     * @return 
     *
     */
     @Override
    public Object erase(Object key){
        int position = -1;
        
        // silinecek value array de hangi konumda oldugu bulunur
        for (int k = 0; k < size(); ++k) {      
            if (get(k).getKey().equals(key)){      // array in elemanlariyla gelen value yu karsilastirir else {
                position = k;               // silinecek value nun indexini position a atar
                System.out.print(position);
            }
        }
        
        //System.out.print(position);
        if(position == -1)                  // silinecek key map te yoksa
            return (V) new NullPointerException();
        
        System.arraycopy(_setArr, position, _setArr, position + 1, size() - position);
       
        _size = _size - 1;
        
        return key;
    }
    
    @Override
     public Object find( Object key) { 
        GTUIterator iter;
        // iteratorla array icinde dolasip value var mi diye bakar
        for (iter = this.begin() ; iter.hasNext(); ++iter.marker) {
              if (key.equals(iter.next()))
                  return iter;
        }
         return this.end();
    } 
     
    @Override
    public String toString(){
        return "myMap";
    }
}
