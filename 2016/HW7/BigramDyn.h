

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H
#include "Bigram.h"

using namespace std;

template <class T>
class BigramDyn : public Bigram<T> {
protected:
    virtual void print(ostream& os) ;
public:
    // constructurs
    BigramDyn();
    BigramDyn( int dataT );
    // copy constructor
    BigramDyn(const BigramDyn<T>& orig);
    // destructor
    ~BigramDyn();
    void findSize( const char* filename );
    void setSizeOfFile( int num );
    int getSizeOfFile() { return sizeOfFile; }
    void readFile( const char* );
    int numGrams();
    int numOfGrams( T p1, T p2 );
    pair<T,T> maxGrams();
    int sortBigram( int* sizeArr );
    void checkFile( const char* filename );
private:
    int dataType;
    T* bigramList = nullptr;
    int sizeOfFile = 0;
    pair <T,T> *couple;
};
#endif /* BIGRAMDYN_H */