#ifndef THESTACK_H
#define THESTACK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include "node.h"

using namespace std;

enum ERRORS {sINVALID_SIZE, sEMPTY, sFULL};

class theStack
{
public:
    typedef node* nodePtr;

    theStack(int s = 5);
    theStack(const theStack &other);
    ~theStack();
    theStack& operator=(const theStack &other);

    bool empty();
    bool full();
    void clear(); // has to be a call to nukem because we can't leave freestore stuff lying around
    nodePtr top(); // STL usually makes copies of things you pass, so PUSH/POP/TOP POINTERS!!!
    nodePtr pop();
    void push(void *x, const char theType);

    int size();
    int capacity();
    void resize(int s); // change the maxSize

    theStack& operator<<(const void *x);  // push an element onto the list
    theStack& operator>>(node &x); // pop the element off the list

    theStack& operator>>(theStack &other);
    theStack& operator<<(const theStack &other);

    friend
    ostream& operator<<(ostream &out, const theStack &s);

    friend
    istream& operator>>(istream &in, theStack &s);

private:
    nodePtr anchor; // WHICH WILL AUTOMATICALLY POINT TO THE TOS!! anchor->next is the TOS
    int cap, tos; // capacity, tos just keeps count of how many elements we have.

    void nukem(nodePtr top);
    void bye(nodePtr top);
    void copy(const theStack &other);
};
#endif // THESTACK_H
