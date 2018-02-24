package hw7;

import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;
import javafx.util.Pair;

/**
 *
 * @author derya
 * @param <T>
 */
public class GTUSet<T> implements GTUSetInt<T> {
    protected int _size = 0;
    protected int _maxSize;
    protected T[] _setArr;
   

    GTUSet() {
        _size = 0;
        _setArr = (T[]) new Object[_size];
    }
    GTUSet(int size) {
        _size = 0;
        _setArr = (T[]) new Object[_size];
    }
    public void printArr()  {
        for (int i = 0; i < _size; ++i){
             System.out.print(get(i));
             System.out.println("");
        }
    }

    public GTUSet(Class<T[]> cls, int num){
        System.out.print(num);
        _setArr = cls.cast(Array.newInstance(cls.getComponentType(), 20));  
        _size = num;
    }

    public void set(int index, T value) {
        _setArr[index] = value;
    }

    public final T get(int index) {
        return _setArr[index];
    }

    /**
     *
     * @return
     */
    @Override
    public boolean empty() {
        return _size != 0;
    }

    /**
     *
     * @return
     */
    @Override
    public int size(){
        return _size;
    }

    /**
     *
     * @return
     */
    @Override
    public int max_size(){
        return _maxSize;
    }
    
    @Override
    public Object erase(Object val){
        int position = 0;
        // silinecek value array de hangi konumda oldugu bulunur
        for (int k = 0; k < _size; ++k) {
            if (get(k).equals((T)val))           // array in elemanlariyla gelen value yu karsilastirir
                position = k;               // silinecek value nun indexini position a atar
        }
        // position i atlayarak uzerine array in uzerine yazar 
        for (int i = position + 1; i < _size ; i++) 
            _setArr[i - 1] = _setArr[i];

       // size i azaltir
        _size = _size - 1;
        return val;
    }

    @SuppressWarnings("unchecked")
    @Override
    public GTUIterator<T> begin() {
        GTUIterator iter = new GTUIterator<>();
        iter.marker = 0;
        return iter;	
    }
    @SuppressWarnings("unchecked")
    @Override
    public GTUIterator<T> end() {
    GTUIterator iter = new GTUIterator<>();
        iter.marker = _size;
        return iter;	
    }

    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){
       GTUSet setB = new GTUSet(other.size());
       GTUIterator iter;
      
       // other class in array indeki elemanlara erismek icin iterator kullanarak baska array e atilir
        for (iter = other.begin(); iter.marker != other.size(); )     
            setB.insert(iter.next());
       
        int intersectSize = 0;       // intersection setinin size i icin
        // iki array boyunca dolasilip iki sette ayni olan eleman varsa intersect setine atilir
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < other.size(); j++) {
                if(this._setArr[i].equals(setB._setArr[j])){
                    setB._setArr[intersectSize] = this._setArr[i];
                    intersectSize++;
                }
            }
       }
       setB._size = intersectSize;          // yeni size belirlenir
       Arrays.sort(setB._setArr);           // array sort edilir
       return setB;
    }
    
    @Override
    public void clear(){
        _setArr = null;
        _size = 0;
    }
    
    @Override
    public int count(T val){
        for (int i = 0; i < _size; ++i) {
        if (_setArr[i].equals(val))
            return 1;
        }
        return 0;
    }

    @Override
    public Object find(Object val) { 
        GTUIterator iter;
        // iteratorla array icinde dolasip value var mi diye bakar
        for (iter = this.begin() ; iter.hasNext(); ++iter.marker) {
              if (val.equals(iter.next()))
                  return iter;
        }
         return this.end();
    }

    @Override
    public Pair<GTUIterator<T>, Boolean> insert(T val) {
       Pair<GTUIterator<T>, Boolean> temp = null;
        for (int j = 0; j < _size; ++j) {
            if (get(j) == val) {
                temp = new Pair(find(val), false);
                throw new InvalidParameterException();
            }
        }
        // yeni eleman icin kendi size indan +1 fazla yer allocate eder
        T[] tempS = (T[]) new Object[_size + 1];
       
        // set icindekileri temp degiskene atar
        for (int i = 0; i < _size; i++)
            tempS[i] = get(i);
     
        // eklenecek degeri son elemente atar
        tempS[_size] = val;
        
        // temp setini this in setine atamak icin temizlenir, her elemana null atanir
        Arrays.fill(_setArr, null);
       
        this._setArr = tempS;
        this._size = _size + 1;
        //Arrays.sort(_setArr);
      
        return temp;
    }
    
    @Override
     public String toString(){
        GTUIterator iter = new GTUIterator<>();
        return "Current elements " + iter.next(); 
    }
    
   	
    public class GTUIterator<K> implements Iterator<K>{
        protected int marker = 0;    // current element
        private K[] ptr;

        public GTUIterator(){ /* Intentionally empty */ }

        public GTUIterator(K[] x){  ptr = x; }

        @Override
        public boolean hasNext(){
            return (marker < _setArr.length);
        }

        @SuppressWarnings("unchecked")
        @Override
       public K next(){
            if (!hasNext())
            throw new NoSuchElementException();

        return (K) _setArr[marker++];
        }

        public boolean hasPrevious(){
            return ( ptr != null );
        }

        @SuppressWarnings("unchecked")
       public K previous(){
           if(!hasPrevious()) 
                  throw new NoSuchElementException(); 
            return  (K) _setArr[marker--];
       }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("Not supported yet.");
        }
       
        @Override
        public String toString(){
            return "Current iterator ->> " + _setArr[marker];
        }
    }
}