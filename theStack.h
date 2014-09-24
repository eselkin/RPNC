#ifndef THESTACK_H
#define THESTACK_H
#include <node.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include "oppr.h"

using namespace std;

enum ERRORS {sINVALID_SIZE, sEMPTY, sFULL};

template<typename T = DataType>
class theStack
{
public:
    typedef node<T>* nodePtr;

    theStack(int s = 5);
    theStack(T data, int s); // giving init val? Not anymore
    theStack(const theStack &other);
    ~theStack();
    theStack& operator=(const theStack &other);

    bool empty();
    bool full();
    void clear(); // has to be a call to nukem because we can't leave freestore stuff lying around
    nodePtr top(); // STL usually makes copies of things you pass, so PUSH/POP/TOP POINTERS!!!
    nodePtr pop();
    void push(const T &x, const char theType); // point to x's location, don't change it, but you can also pass a literal, etc.
    int size();
    int capacity();
    void resize(int s); // change the maxSize

    theStack<T>& operator<<(const T& x);  // push an element onto the list
    theStack<T>& operator>>(T &x); // pop the element off the list

    theStack<T>& operator>>(theStack<T> &other);
    theStack<T>& operator<<(const theStack<T> &other);

    template<typename U>
    friend
    ostream& operator<<(ostream &out, const theStack<U> &s);

    template<typename U>
    friend
    istream& operator>>(istream &in, theStack<U> &s);

private:
    nodePtr anchor; // WHICH WILL AUTOMATICALLY POINT TO THE TOS!! anchor->next is the TOS
    int cap, tos; // capacity, tos just keeps count of how many elements we have.

    void nukem(nodePtr top);
    void bye(nodePtr top);
    void copy(const theStack &other);
};

template<typename T>
theStack<T>::theStack(int s)
{
    cap = s;
    anchor = new node<T>;
    anchor->next = NULL;
    tos = -1;
    if(s < 1)
        throw sINVALID_SIZE;
}

template<typename T>
theStack<T>::theStack(T data, int s)
{
    cap = s;
    anchor = new node<T>;
    anchor->next = NULL;
    tos = -1;
    if(s<1)
        throw sINVALID_SIZE;
    push(data);
}

template<typename T>
theStack<T>::theStack(const theStack &other)
{
    copy(other);
}

template<typename T>
theStack<T>::~theStack()
{
    if (anchor->next)
        nukem(anchor->next);// anchor holds no key, so start from its next
    anchor = new node<T>;
    anchor->next = NULL;
    tos = -1;
}

template<typename T>
theStack<T>& theStack<T>::operator=(const theStack &other)
{
    if(this != &other)
    {
        if (anchor->next)
            nukem(anchor->next);// anchor holds no key, so start from its next
        anchor = new node<T>;
        anchor->next = NULL;
        copy(other);
    }
    return *this;
}


template<typename T>
bool theStack<T>::empty()
{
    // or we could do tos == -1
    return anchor->next == NULL;
}

template<typename T>
bool theStack<T>::full()
{
    return tos == cap;
}

template<typename T>
void theStack<T>::clear()
{
    if (anchor->next)
        nukem(anchor->next);// anchor holds no key, so start from its next
    tos = -1;
    anchor = new node<T>;
    anchor->next = NULL;
}

template<typename T>
node<T>* theStack<T>::top()
{
    if (anchor->next)
        return anchor->next; // we always push from the head
    return NULL;
}

template<typename T>
typename theStack<T>::nodePtr theStack<T>::pop()
{
    if(empty())
        throw sEMPTY;
    --tos;
    nodePtr holder = anchor->next;
    anchor->next = holder->next;
    holder->next = NULL;
    return holder;
}

template<typename T>
void theStack<T>::push(const T &x, const char theType)
{
    if(full())
        throw sFULL;
    tos++; // we successfully are adding something to the stack

    // switch here
    node<T> *newNext = new node<T>(&x, theType, anchor->next); // make a nodepointer with a node with key *x
    newNext->next = anchor->next; // put it into the head position and keep the others afterward
    anchor->next = newNext; // point anchor to it
}

template<typename T>
int theStack<T>::size()
{
    return tos + 1;
}

template<typename T>
int theStack<T>::capacity()
{
    return cap;
}

template<typename T>
void theStack<T>::resize(int s)
{
    cap = s;
    if(s < 1)
        throw sINVALID_SIZE;
    if (anchor->next)
        nukem(anchor->next);// anchor holds no key, so start from its next
    tos = -1;
}

template<>
void theStack<string>::resize(int s)
{
    cap = s;
    if(s < 1)
        throw sINVALID_SIZE;
    tos = -1;
}

template<typename T>
theStack<T>& theStack<T>::operator<<(const T& x)
{
    // pushes a value!
    push(x);
    return *this;
}

template<typename T>
theStack<T>& theStack<T>::operator>>(T& x)
{
    x = *(pop()->key); // a node's key
    return *this;
}

template<typename T>
void theStack<T>::bye(node<T> *top)
{
    delete top;
    top = NULL;
}

template<typename T>
void theStack<T>::nukem(node<T>* top)
{
    if (top->next)
        nukem(top->next);
    bye(top); // changed from !top->next
}

template<typename T>
void theStack<T>::copy(const theStack &other)
{
    cap = other.cap;
    tos = other.tos;
    node<T>* otherPtr = other.anchor->next;
    node<T>* myPtr = anchor;
    while (otherPtr)
    {
        myPtr->next=new node<T>(otherPtr->key);
        otherPtr = otherPtr->next;
        myPtr = myPtr->next;
    }
}


template<typename T>
theStack<T>& theStack<T>::operator<<(const theStack<T> &other)
{
    copy(other);
    return *this;
}

template<typename T>
theStack<T>& theStack<T>::operator>>(theStack<T> &other)
{
    other.copy(*this);
    return *this;
}

template<typename U>
ostream& operator<<(ostream &out, const theStack<U> &s)
{
    if (s.tos != -1)
    {
        if(out == cout)
            out<<"The stack contains "<<s.tos+1<<" items. They are: "<<endl;
        else
            out<<"Capacity:"<<s.cap<<endl
              <<"TOS:"<<s.tos<<endl;
        node<U>* Pointer = s.anchor->next;
        while (Pointer->next){
            out << *(Pointer->key) << endl;
            Pointer = Pointer->next;
        }
        out << *(Pointer->key) << endl;
    }
    return out;
}

template<typename U>
istream& operator>>(istream &in, theStack<U> &s)
{
    int cap, tos;
    string line;
    stringstream ss;
    U data, *data2;
    if(in == cin)
    {
        cout<<"What size of a stack do you want: ";
        cin>>cap;
        s.resize(cap);
        cin.ignore();
    }
    else
    {
        getline(in,line);
        line = line.substr((line.find(':')+1));
        ss<<line;
        ss>>cap;
        ss.str("");
        s.resize(cap);
        s.tos=-1;
        getline(in,line);
        ss.clear();
    }
    getline(in,line);
    data2 = new U();
    ss << line;
    ss >> *data2;
    ss.clear();
    while (line != "")
    {
        s << *data2;
        getline(in, line);
        data2 = new U();
        if (line != "")
        {
            ss << line;
            ss >> *data2;
            ss.clear();
        }
    }
    return in;
}

template<>
istream& operator>>(istream &in, theStack<string> &s)
{
    int cap, tos;
    string line;
    stringstream ss;
    string* data;
    if(in == cin)
    {
        cout<<"What size of a stack do you want: ";
        in>>cap;
        s.resize(cap);
        in.ignore();
        getline(in,line);
        data = new string(line);
        while(*data != "")
        {
            s << *data;
            getline(in,line);
            data = new string(line);
        }
    }
    else
    {
        getline(in,line);
        line = line.substr(line.find(':')+1);
        ss<<line;
        ss>>cap;
        ss.clear();
        s.resize(cap);
        getline(in,line);
        ss.clear();
        getline(in,line);
        data = new string(line);
        while (line != "")
        {
            s << *data;
            getline(in, line);
            data = new string(line);
            ss >> *data;
        }
    }
    return in;
}


#endif // THESTACK_H
