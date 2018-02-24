/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: derya
 *
 * Created on 29 Aralık 2016 Perşembe, 11:37
 */

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>
#include <stdexcept>

using namespace std;

class myException : public exception {
public:
    myException() {}
    myException( const char* theMessage ) : message( theMessage ) { }
    virtual const char* what() const throw()
    {
        return message;
    }
private:
    const char* message;
};

#endif /* EXCEPTION_H */

