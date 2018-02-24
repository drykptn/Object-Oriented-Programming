package hw7;

import javafx.util.Pair;

public interface GTUSetInt<T> {
    public boolean empty();
    public int size();
    public int max_size();
    public Object erase(Object val);
    public void clear();
    public int count(T val);
    public Object find( Object val);
    public Pair<GTUSet<T>.GTUIterator<T>, Boolean> insert( T val);
    public GTUSet<T>.GTUIterator<T> begin();
    public GTUSet<T>.GTUIterator<T> end();
    public GTUSetInt<T> intersection(GTUSetInt<T> other);
}