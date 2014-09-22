#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template<typename T = int>
struct node
{
    T *key;
    node *next;

    node(const T *k = NULL, node<T> *n = NULL);
    ~node();
    node(const node<T> &n);
    node<T>& operator=(const node<T> &n);

    template<typename A>
    friend
    ostream& operator<<(ostream &out, const node<A> n );

    template<typename A>
    friend
    istream& operator>>(istream &in, node<A> *n );
};


template<typename A>
ostream& operator<<(ostream &out, const node<A> n )
{
    out<<"["<<*n.key<<"]";
    return out;
}

template<typename A>
istream& operator>>(istream &in, node<A> *n )
{
    // FIX THIS!
    return in;
}


template<typename T>
node<T>::node(const T *k, node<T> *n)
{
    key = k ? new T(*k) : NULL;
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
    next = NULL;
    key = new T(*other.key);
}


template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        next = NULL;
        key = new T(*other.key);
    }
    return *this;
}


#endif // NODE_H
