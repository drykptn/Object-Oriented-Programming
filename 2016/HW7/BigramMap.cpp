#include "myException.h"
#include "BigramMap.h"
#include "Bigram.h"
#include "BigramDyn.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

template<class T>
BigramMap<T>::BigramMap ( ) { /* Emtpy constructor */ }

template<class T>
BigramMap<T>::BigramMap(int dataT) : dataType(dataT)
{ /* Emtpy constructor */ }

// This function set size of file 
template<class T>
void BigramMap<T>::setSizeOfFile(int num){
    sizeOfFile = num;
    // if file is empty
    if( sizeOfFile == -1 )
        throw myException("Empty file");
}

// sset the coming filename
template<class T>
void BigramMap<T>::setFilename ( const char* filename ) {
    fileName = filename;
}

// find the size of array and send to setSizeOfFile
template<class T>
void BigramMap<T>::findSize ( const char* filename ) {
    fstream file;
    file.open (filename);
    T word;
    int count = 0;
    
    while ( file >> word )
        count++;

    count--;
    setSizeOfFile(count);
    file.close();
}
// This function reads the file, calculates all the bigrams 
template<class T>
void BigramMap<T>::readFile ( const char* filename ) {
    setFilename( filename );
    findSize( getFilename() );
    fstream file;
    file.open(getFilename());
    
    T word;
    vector< T > temp;
    int i = 0, j = 0, count = 0;
    
    // if file is not opened
    if(!file)
        throw myException("File is not opened ");
    
    // read file
    while ( file >> word )
    {
        temp.push_back(word);
        i++;
    }
    // add to pair all of them
    for ( int j = 0; j < sizeOfFile ; j++ )
        couple.push_back(make_pair(temp[j], temp[j+1])) ;
    
    checkFile();
    file.close();
}
// virtual operator<< function
template<class T>
void BigramMap<T>::print (  ostream& os ) {
    // for pair's and their frequently 
    struct Couples {
        T first;
        T second;
        int ID;
    }zeytin[getSizeOfFile()], pamuk;

    int count = 0;
    vector<int> sizeArr;
    // fill the pairs frequently
    sizeArr = fillArr( sizeArr );
    
    // fill the structure with pair and their frequently
    for ( int i = 0; i < getSizeOfFile(); i++ ){
        zeytin[i].first = couple[i].first;
        zeytin[i].second = couple[i].second;
        zeytin[i].ID = sizeArr.at(i);
        
    }
    // sort the structure array      
    for( int i = 0 ; i < getSizeOfFile() ; i++ ) {
        for( int j = 0 ; j < getSizeOfFile()-i-1 ; j++ ){
            if( zeytin[j].ID < zeytin[j+1].ID ){
                pamuk = zeytin[j];  
                zeytin[j] = zeytin[j+1];  /*Swap have been done here*/ 
                zeytin[j+1] = pamuk;               
            }    
        }     
    } 
    // send to map
    for ( int i = 0; i < getSizeOfFile(); i++ ) 
        bigramList.insert( make_pair( make_pair(zeytin[i].first,zeytin[i].second ), zeytin[i].ID ));
    
    // then print them
    for( int i = 0 ; i < getSizeOfFile()- count ; i++ )
        os << "(" << zeytin[i].first << "," << zeytin[i].second << ") -> " 
             << bigramList[ make_pair(zeytin[i].first,zeytin[i].second )] << endl;
}

// for pairs frequently arrays
template<class T>
vector<int>& BigramMap<T>::fillArr ( vector<int>& sizeArr ) {
    for ( int i = 0; i < getSizeOfFile(); i++ )
        sizeArr.push_back( numOfGrams( couple[i].first, couple[i].second ) );
    return sizeArr;
}


template<class T>
int BigramMap<T>::numGrams ( ) {
    return getSizeOfFile();
}

//takes two elements as bigrams and returns the number of that bigram read so far
template<class T>
int BigramMap<T>::numOfGrams ( T p1 , T p2 ) {
    int i = 0, count = 0;
    while( i != getSizeOfFile() )
    {
        if( couple[i].first == p1 && couple[i].second == p2 )
            count++;    
        i++;
    }        
    return count;
}
// sort the coming vector array
template<class T>
vector<int>& BigramMap<T>::sortBigram ( vector<int>& sizeArr ) {
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
    return sizeArr;
}

// returns the bigram that has occurred most frequently
template<class T>
pair<T , T> BigramMap<T>::maxGrams ( ) {
    vector<int> sizeArr;
    // fill the array
    sizeArr = fillArr( sizeArr );
    // then sort them
    sizeArr = sortBigram( sizeArr );

    for ( int i = 0; i < getSizeOfFile(); i++ ){ 
        if( numOfGrams( couple[i].first, couple[i].second ) == sizeArr[0] )
            return make_pair(couple[i].first, couple[i].second );
    }
}

template<class T>
void BigramMap<T>::checkFile() {
    fstream file;
    file.open ( getFilename() );
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