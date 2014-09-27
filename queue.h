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
    queue(const queue &other);
    queue& operator=(const queue &other);

    bool empty() const;
    bool full();
    void clear();
    int size();
    int capacity();
    void resize(int s);
    const node &peek() const;
    void enqueue(void *data, const char dType);
    void enqueue(node n);

    node* dequeue();

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
    quehead = quetail = NULL; // tail should always be pointing to NULL... head should only be pointing to NULL if there's nothing in the list
    mySize = -1;
}

queue::~queue()
{
    quehead && nukem(quehead);
    quehead = quetail = NULL;
    mySize = -1;
}


queue::queue(const queue &other)
{
    mySize = -1;
    quetail = quehead = NULL;
    // copy constructor only gets called when instantiating or directly calling the copy or passing a var by value
    // so should have no values to delete
    copy(other);
}

queue& queue::operator=(const queue &other)
{
    if(this != &other)
    {
        quehead && nukem(quehead);
        copy(other);
    }
    return *this;
}

void queue::clear()
{
    quehead && nukem(quehead);
    quehead = quetail = NULL;
    mySize = -1;
}

bool queue::empty() const
{
    return quehead == NULL;
}

bool queue::full()
{
    return false; // we are a linked list, so this is a dumb function
    //return cap == mySize; // this is so silly... not silly anymore
}

int queue::size()
{
    return mySize+1;
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
    quehead && nukem(quehead);
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

void queue::enqueue(node n)
{
    if(full())
        throw qFULL;
    if (quetail)
    {
        node* quepointer = quetail;
        quetail = quetail->next;
        quetail = new node(n); // if it's the first element, it is the head!
        quepointer->next = quetail;
    }
    else
    {
        quetail = new node(n);
        quehead = quetail;
    }
    mySize++;
}

void queue::enqueue(void *data, const char dType)
{
    if(full())
        throw qFULL;
    if (quetail)
    {
        quetail->next = new node(data, dType); // if it's the first element, it is the head!
        quetail = quetail->next;
    }
    else
        quetail = new node(data, dType);
    (mySize == -1) && (quehead = quetail); // this moves the head to the first element on that we add
    mySize++;
}

node *queue::dequeue()
{
    if(empty())
        throw qEMPTY; // head = tail = NULL
    queue::nodePtr oldhead = quehead;
    quehead = quehead->next; // could point to NULL and make the list empty
    mySize--;
    return oldhead; // return the node at oldhead... deref outside of dequeue
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
    if (!top)
        return NULL;
    if (top->next)
        nukem(top->next);
    bye(top); // will delete the head as well
    return NULL;
}

void queue::copy(const queue &other)
{
    cap = other.cap;
    node* quepointer = other.quehead; // set the quepointer to the quehead of the other queue
    while (quepointer)
    {
        // progress down the line of the other queue and enqueu into this queue dereferencing the right type
        enqueue(*quepointer);
        quepointer = quepointer->next;
    }

}


ostream& operator<<(ostream& out, const queue &que)
{
    node* quepointer = que.quehead;
    out << "QUEUE SIZE: " << que.mySize + 1 << endl;
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
