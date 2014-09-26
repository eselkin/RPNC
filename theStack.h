#ifndef THESTACK_H
#define THESTACK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include "node.h"
#include "oppr.h"

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

theStack::theStack(int s)
{
    if(s < 1)
        throw sINVALID_SIZE;
    cap = s;
    anchor = new node();
    anchor->next = NULL;
    tos = -1;
}

theStack::theStack(const theStack &other)
{
    copy(other);
}

theStack::~theStack()
{
    if (anchor->next)
        nukem(anchor->next);// anchor holds no key, so start from its next
    anchor = new node();
    anchor->next = NULL;
    tos = -1;
}

theStack& theStack::operator=(const theStack &other)
{
    if(this != &other)
    {
        if (anchor->next)
            nukem(anchor->next);// anchor holds no key, so start from its next
        anchor = new node();
        anchor->next = NULL;
        copy(other);
    }
    return *this;
}


bool theStack::empty()
{
    // or we could do tos == -1
    return anchor->next == NULL;
}

bool theStack::full()
{
    return false;
}

void theStack::clear()
{
    if (anchor->next)
        nukem(anchor->next);// anchor holds no key, so start from its next
    tos = -1;
    anchor = new node();
    anchor->next = NULL;
}

void theStack::push(void *x, const char theType)
{
    if(full())
        throw sFULL;
    tos++; // we successfully are adding something to the stack

    // switch here
    node *newNext = new node(x, theType, anchor->next); // make a nodepointer with a node with key *x
    newNext->next = anchor->next; // put it into the head position and keep the others afterward
    anchor->next = newNext; // point anchor to it
}

node* theStack::top()
{
    if (anchor->next)
        return anchor->next; // we always push from the head
    return NULL;
}

node* theStack::pop()
{
    if(empty())
        throw sEMPTY;
    --tos;
    nodePtr holder = anchor->next;
    anchor->next = holder->next;
    holder->next = NULL;
    return holder;
}

int theStack::size()
{
    return tos + 1;
}

int theStack::capacity()
{
    return cap;
}

void theStack::resize(int s)
{
    cap = s;
    if(s < 1)
        throw sINVALID_SIZE;
    if (anchor->next)
        nukem(anchor->next);// anchor holds no key, so start from its next
    tos = -1;
}


void theStack::bye(node *top)
{
    delete top;
    top = NULL;
}

void theStack::nukem(node* top)
{
    if (top->next)
        nukem(top->next);
    bye(top); // changed from !top->next
}

void theStack::copy(const theStack &other)
{
    cap = other.cap;
    tos = other.tos;
    node* otherPtr = other.anchor->next;
    node* myPtr = anchor;
    while (otherPtr)
    {
        switch(otherPtr->data_type){
        case 'N':
            myPtr->next=new node(otherPtr->key.mPtr, otherPtr->data_type);
            break;
        case 'O':
        case 'P':
            myPtr->next=new node(otherPtr->key.opPtr, otherPtr->data_type);
            break;
        default:
            break;
        }
        otherPtr = otherPtr->next;
        myPtr = myPtr->next;
    }
}

theStack& theStack::operator<<(const theStack &other)
{
    copy(other);
    return *this;
}

theStack& theStack::operator>>(theStack &other)
{
    other.copy(*this);
    return *this;
}

ostream& operator<<(ostream &out, const theStack &s)
{
    if (s.tos != -1)
    {
        if(out == cout)
            out<<"The stack contains "<<s.tos+1<<" items. They are: "<<endl;
        else
            out<<"Capacity:"<<s.cap<<endl
              <<"TOS:"<<s.tos<<endl;
        node* Pointer = s.anchor->next;
        while (Pointer){
            switch(Pointer->data_type)
            {
            case 'N':
                out << *(Pointer->key.mPtr) << endl;
                break;
            case 'O':
            case 'P':
                out << (Pointer->key.opPtr->theOp) << endl;
                break;
            default:
                break;
            }
            Pointer = Pointer->next;

        }
        return out;
    }
}
#endif // THESTACK_H
