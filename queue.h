#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "node.h"

using namespace std;

enum qERRORS {FULL, EMPTY, BAD_SIZE};

template<typename T = char, typename V = int>
class queue
{
public:
    typedef node<T>* nodePtr;

    queue(int s = 5);
    ~queue();
    queue(const queue<T>&other);
    queue<T>& operator=(const queue<T>&other);

    bool empty() const;
    bool full();
    void clear();
    int size();
    int capacity();
    void resize(int s);
    const T& peek() const;
    void enqueue(const T &data, const V &priority);
    void dequeue(T &data);
    queue<T>& operator<<(const T &data);
    queue<T>& operator>>(T &data);

    template<typename U>
    friend
    ostream& operator<<(ostream& out, const queue<U> &que);


    template<typename U>
    friend
    istream& operator>>(istream& in, queue<U> &que);

private:
    nodePtr quehead, quetail; // we don't need to change the name
    int cap, mySize; // OK maybe in an array having no int with the size was a convenient way, but seriously, it's a waste of computation in nodes
    nodePtr nukem(nodePtr top);
    nodePtr bye(nodePtr top);
    void copy(const queue<T> &other);
    nodePtr moveUp(nodePtr moveMe);
};

template<typename T>
queue<T>::queue(int s)
{
    cap = s;
    quehead = quetail = NULL; // tail should always be pointing to NULL... head should only be pointing to NULL if there's nothing in the list
    mySize = -1;
}

template<typename T>
queue<T>::~queue()
{
    (quehead) && nukem(quehead);
    quehead = quetail = NULL;
    mySize = -1;
}


template<typename T>
queue<T>::queue(const queue<T>&other)
{
    // copy constructor only gets called when instantiating or directly calling the copy or passing a var by value
    // so should have no values to delete
    copy(other);
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T>&other)
{
    if(this != &other)
    {
        quehead && nukem(quehead);
        copy(other);
    }
    return *this;
}

template<typename T>
void queue<T>::clear()
{
    quehead && nukem(quehead);
    quehead = quetail = NULL;
    mySize = -1;
}

template<typename T>
bool queue<T>::empty() const
{
    return mySize == -1; // Had trouble if head and tail were pointing to the same node.
}

template<typename T>
bool queue<T>::full()
{
    return cap == mySize; // this is so silly... not silly anymore
}

template<typename T>
int queue<T>::size()
{
    return mySize+1;
    // THIS IS SO SILLY, WE SHOULD NOT COMPUTE SIZE EVERY TIME, WHAT IF IT'S A HUGE QUEUE!
    // On a large queue, the size difference of storing a int variable with the size in it is negligeable compared to CPU time to calculate
    //    int size=0;
    //    queue<T>::nodePtr myPointer = quehead;
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

template<typename T>
int queue<T>::capacity()
{
    return cap;
}

template<typename T>
void queue<T>::resize(int s)
{
    if(s < 1)
        throw BAD_SIZE;
    quehead && nukem(quehead);
    cap = s; // changing capacity, nuked the old stuff
    quehead = quetail = NULL;
    mySize = -1;
}

template<typename T>
const T& queue<T>::peek() const
{
    if(empty())
        throw EMPTY;
    return *quehead->key;
}

template<typename T>
void queue<T>::enqueue(const T &data, const V &priority)
{
    if(full())
        throw FULL;

    node<T>* quepointer = new node<T>(data); // if it's the first element, it is the head!
    quepointer->setpri(priority);
    mySize == -1 && (quehead = quetail = quepointer); // this moves the head to the first element on that we add
    quepointer->setPrev(quetail);
    quetail->setNext(quepointer); // otherwise, quetail will point to the element that we just added, which will be different from the head.
    quetail = quepointer;
    mySize++;
    // NOW MOVE UP THE CHAIN
    moveUp(quetail);
}

template<typename T>
void queue<T>::dequeue(T &data)
{
    if(empty())
        throw EMPTY; // head = tail = NULL
    queue<T>::nodePtr tempholder = quehead;
    quehead = quehead->getNext(); // could point to NULL and make the list empty
    quehead->setPrev(NULL);
    data = tempholder->getkey();
    delete tempholder; // deleting node
    mySize--;
}

template<typename T>
queue<T>& queue<T>::operator<<(const T &data)
{
    enqueue(data);
    return *this;
}

template<typename T>
queue<T>& queue<T>::operator>>(T &data)
{
    dequeue(data);
    return *this;
}

template<typename T>
node<T>* queue<T>::bye(node<T>* top)
{
    if (top)
        delete top;
    top = NULL;
    return top;
}

template<typename T>
node<T>* queue<T>::nukem(node<T>* top)
{
    if (top->getNext())
        nukem(top->getNext());
    bye(top); // will delete the head as well
    return NULL;
}

template<typename T>
void queue<T>::copy(const queue<T> &other)
{
    cap = other.cap;
    node<T>* quepointer = other.quehead; // not sure I can do this

    quetail = quetail->right; // otherwise, quetail will point to the element that we just added, which will be different from the head.

    mySize = -1;
    while (quepointer)
    {
        quetail = new node<T>(*quepointer->key);
        mySize == -1 && (quehead = quetail); // this moves the head to the first element on that we add
        quetail = quetail->right;
        quepointer = quepointer->right;
        mySize++;
    }
    //for(int i = other.head; i != tail; i = (++i)%cap)
}

template<typename T>
node<T>* queue<T>::moveUp(node<T>* moveMe)
{
    node<T>* beforeMe;
    while (moveMe->getpri() > moveMe->getPrev()->getpri())
    {
        beforeMe = moveMe->getPrev();
        (moveMe == quetail) && (quetail = beforeMe);
        moveMe->setNext(beforeMe);
        moveMe->setPrev(beforeMe->getPrev());
        beforeMe->setNext(NULL); // this may be quetail.
    }
}


template<typename U>
istream& operator>>(istream& in, queue<U> &que)
{
    vector<U> list;
    U data;
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
    int i = 0;
    node<U>* quepointer = new node<U>(list[i]); // if it's the first element, it is the head!
    que.quehead = que.quetail = quepointer; // this moves the head to the first element on that we add
    for(++i; i < list.size(); i++)
    {
        que.quetail->setNext(new node<U>(list[i]));
        que.quetail->getNext()->setPrev(que.quetail);
        que.quetail = que.quetail->getNext();
        que.mySize++;
    }
    return in;
}

template<>
istream& operator>>(istream& in, queue<string> &que)
{
    vector<string> list;
    string line;
    stringstream ss;
    if (in != cin)
    {
        getline(in,line);
        int pos = line.find(':');
        line = line.substr(pos+1,string::npos); // already puts in npos
        ss << line;
        ss >> que.cap;
    }
    getline(in,line);
    while(line != "")
    {
        list.push_back(line);
        getline(in,line);
    }
    que.mySize = -1;
    int i = 0;
    node<string>* quepointer = new node<string>(list[i]); // if it's the first element, it is the head!
    que.quehead = que.quetail = quepointer; // this moves the head to the first element on that we add
    for(++i; i < list.size(); i++)
    {
        que.quetail->setNext(new node<string>(list[i]));
        que.quetail->getNext()->setPrev(que.quetail);
        que.quetail = que.quetail->getNext();
        que.mySize++;
    }
    return in;
}

template<typename U>
ostream& operator<<(ostream& out, const queue<U> &que)
{
    node<U>* quepointer = que.quehead;
    for(; quepointer->getNext() ; quepointer = quepointer->getNext())
        out<<quepointer->getkey()<<endl;
    out << quepointer->getkey()<<endl;
    return out;
}


#endif // QUEUE_H
