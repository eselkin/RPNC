#ifndef QUEUE_H
#define QUEUE_H
// SINGLE DIRECTION NODE VERSION
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "node.h"

using namespace std;

enum qERRORS {qFULL, qEMPTY, qBAD_SIZE};

class queue
{
public:
    typedef node* nodePtr;

    queue(int s = 5);
    ~queue();
    queue(const queue&other);
    queue& operator=(const queue &other);

    bool empty() const;
    bool full();
    void clear();
    int size();
    int capacity();
    void resize(int s);
    const node &peek() const;
    void enqueue(void *data, const char dType);
    node dequeue();

    friend
    ostream& operator<<(ostream& out, const queue &que);


    friend
    istream& operator>>(istream& in, queue &que);

private:
    nodePtr quehead, quetail; // we don't need to change the name
    int cap, mySize; // OK maybe in an array having no int with the size was a convenient way, but seriously, it's a waste of computation in nodes
    nodePtr nukem(nodePtr top);
    nodePtr bye(nodePtr top);
    void copy(const queue &other);
};

queue::queue(int s)
{
    cap = s;
    quehead = quetail = new node(); // tail should always be pointing to NULL... head should only be pointing to NULL if there's nothing in the list
    mySize = -1;
}

queue::~queue()
{
    (quehead->next) && nukem(quehead->next);
    quehead = quetail = new node();
    mySize = -1;
}


queue::queue(const queue &other)
{
    // copy constructor only gets called when instantiating or directly calling the copy or passing a var by value
    // so should have no values to delete
    copy(other);
}

queue& queue::operator=(const queue &other)
{
    if(this != &other)
    {
        quehead->next && nukem(quehead->next);
        copy(other);
    }
    return *this;
}

void queue::clear()
{
    quehead->next && nukem(quehead);
    quehead = quetail = new node();
    mySize = -1;
}

bool queue::empty() const
{
    return mySize == -1; // Had trouble if head and tail were pointing to the same node.
}

bool queue::full()
{
    return false;
    return cap == mySize; // this is so silly... not silly anymore
}

int queue::size()
{
    return mySize+1;
    // THIS IS SO SILLY, WE SHOULD NOT COMPUTE SIZE EVERY TIME, WHAT IF IT'S A HUGE QUEUE!
    // On a large queue, the size difference of storing a int variable with the size in it is negligeable compared to CPU time to calculate
    //    int size=0;
    //    queue::nodePtr myPointer = quehead;
    //    while (myPointer)
    //    {
    //        size++;
    //        myPointer = myPointer->next; // WHEN NULL, stops while at next loop
    //    }
    //    return size;
    // Array method that I liked!
    // if queue is empty head==tail this is wrong! We need a three part if-like option... which this new nested ternary represents
    // return tail >= head ? (tail == head? tail-head : tail-head+1): (cap+tail-head); // this was my best line! for the array at least!
}

int queue::capacity()
{
    return cap;
}

void queue::resize(int s)
{
    if(s < 1)
        throw qBAD_SIZE;
    quehead->next && nukem(quehead->next);
    cap = s; // changing capacity, nuked the old stuff
    quehead = quetail = NULL;
    mySize = -1;
}

const node& queue::peek() const
{
    if(empty())
        throw qEMPTY;
    return *quehead;
}

void queue::enqueue(void *data, const char dType)
{
    if(full())
        throw qFULL;
    node* quepointer = quetail->next = new node(data, dType); // if it's the first element, it is the head!
    quetail = quetail->next; // otherwise, quetail will point to the element that we just added, which will be different from the head.
    mySize == -1 && (quehead = quepointer); // this moves the head to the first element on that we add
    mySize++;
}

node queue::dequeue()
{
    if(empty())
        throw qEMPTY; // head = tail = NULL
    queue::nodePtr oldhead = quehead;
    quehead = quehead->next; // could point to NULL and make the list empty
    mySize--;
    return *oldhead; // return the node at oldhead... deref outside of dequeue
}


node *queue::bye(node *top)
{
    if (top)
        delete top;
    top = NULL;
    return top;
}

node *queue::nukem(node *top)
{
    if (top->next)
        nukem(top->next);
    bye(top); // will delete the head as well
    return NULL;
}

void queue::copy(const queue &other)
{
    cap = other.cap;
    node* quepointer = other.quehead; // not sure I can do this
    quetail = quetail->next; // otherwise, quetail will point to the element that we just added, which will be different from the head.

    mySize = -1;
    while (quepointer)
    {
        if (quepointer->data_type == 'N')
            quetail = new node(quepointer->key.mPtr, quepointer->data_type);
        else
            quetail = new node(quepointer->key.opPtr, quepointer->data_type);
        (mySize == -1) && (quehead = quetail); // this moves the head to the first element on that we add
        quetail = quetail->next;
        cout <<"QUETAIL:" << *quetail->key.mPtr << endl;
        quepointer = quepointer->next;
        mySize++;
    }

    //for(int i = other.head; i != tail; i = (++i)%cap)
}


ostream& operator<<(ostream& out, const queue &que)
{
    node* quepointer = que.quehead;

    for(; quepointer->next ; quepointer = quepointer->next)
    {
        switch(quepointer->data_type)
        {
        case 'N':
            out << *(quepointer->key.mPtr) << " " ;
            break;
        case 'O':
        case 'P':
            out << (quepointer->key.opPtr->theOp) << " ";
            break;
        default:
            break;
        }
    }
    switch(quepointer->data_type)
    {
    case 'N':
        out << *(quepointer->key.mPtr) << " " ;
        break;
    case 'O':
    case 'P':
        out << (quepointer->key.opPtr->theOp) << " ";
        break;
    default:
        break;
    }
    return out;
}


#endif // QUEUE_H
