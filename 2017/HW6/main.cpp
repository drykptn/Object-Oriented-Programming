#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUMap.h"
#include "GTUMap.cpp"
#include "GTUIterator.h"
#include "GTUIterator.cpp"

using namespace CaptainD;

template<class T>
std::shared_ptr<GTUSetBase<T> > setIntersection(const GTUSetBase<T> &A, const GTUSetBase<T> &B) {
    
}


int main() {
    try {
        GTUSet<int> set, set2;

        cout << "SET 1" << endl << endl;
        set.insert(1);
        set.insert(3);
        set.insert(4);

        set.printArr();

        cout << endl << "clear" << endl << endl;
        set.clear();

        set.insert(5);
        set.insert(3);
        set.insert(8);
        set.insert(6);
        set.insert(2);
        set.insert(9);

        set.printArr();
        cout << endl;

        cout << "set.erase(3) -> " << endl;
        set.erase(3);

        set.printArr();

        cout << endl;
        cout << "set.size() -> " << set.size() << endl;

        int num = 8;
        if(set.count(num) == 1)
            cout << num << " is my element" << endl;


        cout << endl << "SET 2" << endl << endl;
        set2.insert(1);
        set2.insert(2);
        set2.insert(6);
        set2.insert(8);

        set2.printArr();

        GTUIterator<int> itr = set2.find(6);
        cout << endl << "set2.find(6) un iteratorini gösterir -> " << *itr << endl;


        cout << endl << "PAIR " << endl;
        GTUMap<int, int> mymap;
        mymap.insert(make_pair(4, 5));
        mymap.insert(make_pair(6, 3));
        mymap.insert(make_pair(8, 0));
        mymap.insert(make_pair(2, 4));

        cout << endl;
        for (auto it = mymap.begin(); it != mymap.end(); ++it)
            cout << it->first << " " << it->second << endl;

        cout << "mymap[6] nın pair secondı ->  " << mymap[6] << endl;

        cout << endl << "Map size -> " << mymap.size() << endl;

    }
    catch (int x) {
        cerr << "You can't add the element of set Error: " << x << endl;
    }
    return 0;
}

