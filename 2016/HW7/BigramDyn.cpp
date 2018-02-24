#include "BigramDyn.h"
#include "myException.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>      
#include <cstring> 

using namespace std;

template <class T>
BigramDyn<T>::BigramDyn ( ) {}

template <class T>
BigramDyn<T>::BigramDyn( int dataT ) : dataType(dataT) {
}

// This function set size of file 
template<class T>
void BigramDyn<T>::setSizeOfFile(int num){
    sizeOfFile = num;
    // if file is empty
    if( sizeOfFile == -1 ){
        throw myException("Empty file");
        exit(1);
    }
}

// copy constructor
template <class T>
BigramDyn<T>::BigramDyn ( const BigramDyn& obj ) {
    if( getSizeOfFile()!= 0 ){
        bigramList = new T[ getSizeOfFile() ];
        for ( int i = 0; i < getSizeOfFile(); i++ )
            bigramList[i] = obj.bigramList[i];   
        }
}

// destructor
template <class T>
BigramDyn<T>::~BigramDyn ( ) {
    if( bigramList ){
       delete [] bigramList;
       bigramList = nullptr;
    }
}

template<class T>
void BigramDyn<T>::checkFile ( const char* filename ) {
    fstream file;
    file.open (filename);
    string word, temp;
    while ( file >> word ){
        if( dataType == 1 ){
            for ( int i = 0; i < getSizeOfFile() ; i++ ) {
                temp = word;
                for ( int i = 0; i < temp.size() ; i++ ) {
                    if ( temp.at(i) < 48 || temp.at(i) > 57 )
                        throw myException("You can't send a mix file");
                }    
            }
        }
        else if ( dataType == 2 ){
            for ( int i = 0; i < getSizeOfFile() ; i++ ) {
                temp = word;
                for ( int i = 0; i < temp.size() ; i++ ) {
                    if ( temp.at(i) > 48 && temp.at(i) < 57 
                        || temp.at(i) >= 33 && temp.at(i) < 48 )
                        throw myException("You can't send a mix file");
                }    
            }
        }
        else if ( dataType == 3 ){
            for ( int i = 0; i < getSizeOfFile() ; i++ ) {
                temp = word;
                for ( int i = 0; i < temp.size() ; i++ ) {
                    if ( temp.at(i) < 48 || temp.at(i) > 57 ){
                        if ( temp.at(i) != 46)
                            throw myException("You can't send a mix file");
                    }    
                }    
            }
        }
    }
    file.close();
}


// This function finds size of file end send to set function
template<class T>
void BigramDyn<T>::findSize( const char* filename){
    fstream file;
    file.open (filename);
    T word;
    int count = 0;
    
    while ( file >> word )
        count++;

    count--;
    if ( count == -1 )
    	throw myException("File empty");
    
    setSizeOfFile(count);
    file.close();
}

// This function reads the file, calculates all the bigrams 
template<class T>
void BigramDyn<T>::readFile ( const char* filename ) {
    findSize( filename );
    fstream file;
    file.open (filename);
    T word;
    int i = 0, j = 0, count = 0;
    // allocate
    bigramList = new T[getSizeOfFile()+1];
    couple = new pair<T,T>[getSizeOfFile()+1];
    
    while ( file >> word )
    {
        bigramList[i] = word;
        i++;
    }
    checkFile(filename);

    //  add to pair
    for ( int j = 0; j < sizeOfFile ; j++ )
        couple[j] = make_pair(bigramList[j], bigramList[j+1]);    
    
    file.close();
}

template<class T>
int BigramDyn<T>::numGrams(){
    return getSizeOfFile();
}

//takes two elements as bigrams and returns the number of that bigram read so far
template<class T>
int BigramDyn<T>::numOfGrams( T p1, T p2 ){
    int i = 0, count = 0; 
    
    while( i != getSizeOfFile() )
    {
        if( couple[i].first == p1 )
        {
            if( couple[i].second == p2 )
                count++;
        }
        i++;
    }          
    return count;
}

// returns the bigram that has occurred most frequently
template<class T>
std::pair<T , T> BigramDyn<T>::maxGrams ( ) {
    int sizeArr[getSizeOfFile()];
    
    // send pair to numOfGrams and add to list
    for ( int i = 0; i < getSizeOfFile(); i++ )
        sizeArr[i] = numOfGrams( couple[i].first, couple[i].second );
    
    // sort the list
    *sizeArr = sortBigram( sizeArr );
    
    for ( int i = 0; i < getSizeOfFile(); i++ ){ 
        if( numOfGrams( couple[i].first, couple[i].second ) == sizeArr[0] )
            return make_pair(couple[i].first, couple[i].second );
    }
    
}

// sort coming int list 
template<class T>
int BigramDyn<T>::sortBigram ( int* sizeArr ) {
    int temp;
    for( int i = 0 ; i < getSizeOfFile() ; i++ ) {
        for( int j = 0 ; j < getSizeOfFile()-i-1 ; j++ ){
            if( sizeArr[j] < sizeArr[j+1]){
                temp = sizeArr[j];  
                sizeArr[j] = sizeArr[j+1];  /*Swap have been done here*/ 
                sizeArr[j+1] = temp;               
            }    
        }     
    } 
    return *sizeArr;
}

// operator<< virtual function
template<class T>
void BigramDyn<T>::print ( ostream& os )  {
    // for pairs and their frequently
    struct Couples {
        T first;
        T second;
        int ID;
    } zeytin[getSizeOfFile()], pamuk;

    int sizeArr[getSizeOfFile()], count = 0;
    
    // send pair to numOfGrams and add to list
    for ( int i = 0; i < getSizeOfFile(); i++ )
        sizeArr[i] = numOfGrams( couple[i].first, couple[i].second );
    
    // add to all pair and their frequently to struct
    for ( int i = 0; i < getSizeOfFile(); i++ ){
        zeytin[i].first = couple[i].first;
        zeytin[i].second = couple[i].second;
        zeytin[i].ID = sizeArr[i];
    }
    
    // then sort the structure array
    for( int i = 0 ; i < getSizeOfFile() ; i++ ) {
        for( int j = 0 ; j < getSizeOfFile()-i-1 ; j++ ){
            if( zeytin[j].ID < zeytin[j+1].ID ){
                pamuk = zeytin[j];  
                zeytin[j] = zeytin[j+1];  /*Swap have been done here*/ 
                zeytin[j+1] = pamuk;               
            }    
        }     
    } 
    
    // print all of them 
    for( int i = 0 ; i < getSizeOfFile()- count ; i++ ) {
        os << "("<< zeytin[i].first << "," << zeytin[i].second << ") -> " << zeytin[i].ID << endl;
        
    }
}
