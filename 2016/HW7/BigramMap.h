
#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include "Bigram.h"
#include <vector>
#include <map>

using namespace std;

template<class T>
class BigramMap : public Bigram<T> {
protected:
    virtual void print(ostream& os) ;
public:
    // constructurs
    BigramMap();
    BigramMap( int dataT );
    void findSize( const char* filename );
    void setFilename( const char* filename );
    const char* getFilename(){ return fileName; }
    void setSizeOfFile( int num );
    int getSizeOfFile() { return sizeOfFile; }
    void readFile( const char* filename  );
    vector<int>& fillArr( vector<int>& sizeArr );
    int numGrams();
    int numOfGrams( T p1, T p2 );
    pair<T,T> maxGrams();
    vector<int>& sortBigram( vector<int>& sizeArr ); 
    void checkFile();
private:
    const char* fileName;
    int dataType;
    map < pair < T , T > , int  > bigramList;
    int sizeOfFile = 0;
    vector<pair<T,T> >couple;
};

#endif /* BIGRAMMAP_H */

