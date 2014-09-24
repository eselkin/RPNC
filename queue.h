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
    const DataType& peek() const;
    void enqueue(const void &data, const char dType);
    node dequeue();
    queue& operator<<(const DataType &data);
    queue& operator>>(DataType &data);

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
    quehead = quetail = new node; // tail should always be pointing to NULL... head should only be pointing to NULL if there's nothing in the list
    mySize = -1;
}

queue::~queue()
{
    (quehead->next) && nukem(quehead->next);
    quehead = quetail = new node;
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
    quehead = quetail = new node;
    mySize = -1;
}

bool queue::empty() const
{
    return mySize == -1; // Had trouble if head and tail were pointing to the same node.
}

bool queue::full()
{
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

const DataType& queue::peek() const
{
    if(empty())
        throw qEMPTY;
    return *quehead->key;
}

void queue::enqueue(const void &data, const char dType)
{
    if(full())
        throw qFULL;

    DataType* tempdata = new DataType(data);       // workaround for const data  // DEBUG, does this still work or do we need to change this
    node* quepointer = quetail->next = new node(*tempdata, dType); // if it's the first element, it is the head!
    delete tempdata; // because it's been deref'd with ->
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

queue& queue::operator<<(const DataType &data)
{
    enqueue(data);
    return *this;
}

queue& queue::operator>>(DataType &data)
{
    dequeue(data);
    return *this;
}

node* queue::bye(node* top)
{
    if (top)
        delete top;
    top = NULL;
    return top;
}

node* queue::nukem(node* top)
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
        quetail = new node(*quepointer->key);
        mySize == -1 && (quehead = quetail); // this moves the head to the first element on that we add
        quetail = quetail->next;
        quepointer = quepointer->next;
        mySize++;
    }
    //for(int i = other.head; i != tail; i = (++i)%cap)
}


istream& operator>>(istream& in, queue &que)
{
    vector list;
    DataType data;
    string line;
    stringstream ss;
    if (in != cin)
    {
        getline(in,line);
        int pos = line.find(':');
        line = line.substr(pos); // already puts in npos
        ss << line;
        ss >> que.cap;
        ss.clear();
        ss.str("");
    }
    getline(in,line);
    ss << line;
    ss >> data; // needed for anything with spaces... not sure about '.' for double
    ss.clear();
    while(line != "")
    {
        list.push_back(data);
        getline(in,line);
        ss << line;
        ss >> data;
        ss.clear();
        ss.str("");
    }
    que.cap = list.size();
    que.mySize = -1;
    que.quehead = que.quetail = new node;
    for(int i = 0; i < list.size(); i++)
    {
        que.quetail->next = new node(&list[i]);
        que.quetail = que.quetail->next; // pointing to that node that we just made. It's next is NULL
        que.mySize == -1 && (que.quehead = que.quetail); // this moves the head to the first element that we add
        que.mySize++;
    }
    return in;
}

ostream& operator<<(ostream& out, const queue &que)
{
    node* quepointer = que.quehead;
    for(; quepointer->next ; quepointer = quepointer->next)
        out<<*quepointer->key<<endl;
    out << *quepointer->key<<endl;
    return out;
}


#endif // QUEUE_H
