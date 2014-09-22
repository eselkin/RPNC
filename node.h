#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "dataType.h"

using namespace std;

// We're really making this special to DataType for the output queue or Char for the operator stack
template<typename T = DataType>
struct node
{
    T *key;   // we will really make nodes of DataType type (unions).
    char data_type; // I, D, C, S, M, F; I think that's all the types I want nodes to be able to manage

    node *next;


    node(const T *k = NULL, const char dt = 'I', node<T> *n = NULL);
    ~node();
    node(const node<T> &n);
    node<T>& operator=(const node<T> &n);
    copy(const node<T> &n);
};


template<typename T>
node<T>::node(const T *k, const char dt, node<T> *n)
{
    key = k ? new T(*k) : NULL;
    data_type = dt;
    next = n;
}

template<typename T>
node<T>::~node()
{
    delete key;
    next = NULL;
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}


template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        delete key;
        next = NULL;
        copy(other);
    }
    return *this;
}

node::copy(const node<T> &n)
{
    next = NULL;
    key = new T(*other.key);
    data_type = other.data_type;
}


#endif // NODE_H
