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

enum qERRORS {FULL, EMPTY, BAD_SIZE};

template<typename T = DataType>
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
    void enqueue(const T &data);
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
};

template<typename T>
queue<T>::queue(int s)
{
    cap = s;
    quehead = quetail = new node<T>; // tail should always be pointing to NULL... head should only be pointing to NULL if there's nothing in the list
    mySize = -1;
}

template<typename T>
queue<T>::~queue()
{
    (quehead->next) && nukem(quehead->next);
    quehead = quetail = new node<T>;
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
        quehead->next && nukem(quehead->next);
        copy(other);
    }
    return *this;
}

template<typename T>
void queue<T>::clear()
{
    quehead->next && nukem(quehead);
    quehead = quetail = new node<T>;
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
    quehead->next && nukem(quehead->next);
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
void queue<T>::enqueue(const T &data)
{
    if(full())
        throw FULL;

    T* tempdata = new T(data);       // workaround for const data
    node<T>* quepointer = quetail->next = new node<T>(tempdata); // if it's the first element, it is the head!
    delete tempdata;

    quetail = quetail->next; // otherwise, quetail will point to the element that we just added, which will be different from the head.

    mySize == -1 && (quehead = quepointer); // this moves the head to the first element on that we add

    //cout << "ADDR OF HEAD:" << quehead << " ADDR OF TAIL:" << quetail << endl; // DEBUG
    mySize++;
}

template<typename T>
void queue<T>::dequeue(T &data)
{
    if(empty())
        throw EMPTY; // head = tail = NULL
    queue<T>::nodePtr tempholder = quehead;
    quehead = quehead->next; // could point to NULL and make the list empty
    data = *tempholder->key;
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
    if (top->next)
        nukem(top->next);
    bye(top); // will delete the head as well
    return NULL;
}

template<typename T>
void queue<T>::copy(const queue<T> &other)
{
    cap = other.cap;
    node<T>* quepointer = other.quehead; // not sure I can do this

    quetail = quetail->next; // otherwise, quetail will point to the element that we just added, which will be different from the head.

    mySize = -1;
    while (quepointer)
    {
        quetail = new node<T>(*quepointer->key);
        mySize == -1 && (quehead = quetail); // this moves the head to the first element on that we add
        quetail = quetail->next;
        quepointer = quepointer->next;
        mySize++;
    }
    //for(int i = other.head; i != tail; i = (++i)%cap)
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
    que.quehead = que.quetail = new node<U>;
    for(int i = 0; i < list.size(); i++)
    {
        que.quetail->next = new node<U>(&list[i]);
        que.quetail = que.quetail->next; // pointing to that node that we just made. It's next is NULL
        que.mySize == -1 && (que.quehead = que.quetail); // this moves the head to the first element that we add
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
        cout << "LINE:" << line << endl;
        ss << line;
        ss >> que.cap;
        cout << "QUE CAP: " << que.cap << endl;
    }
    getline(in,line);
    while(line != "")
    {
        list.push_back(line);
        getline(in,line);
    }
    que.cap = list.size();
    que.quehead = que.quetail = new node<string>;
    for(int i = 0; i < list.size(); i++)
    {
        que.quetail->next = new node<string>(&list[i]);
        que.quetail = que.quetail->next; // pointing to that node that we just made. It's next is NULL
        que.mySize == -1 && (que.quehead = que.quetail); // this moves the head to the first element that we add
        que.mySize++;
    }
    return in;
}

template<typename U>
ostream& operator<<(ostream& out, const queue<U> &que)
{
    node<U>* quepointer = que.quehead;
    for(; quepointer->next ; quepointer = quepointer->next)
        out<<*quepointer->key<<endl;
    out << *quepointer->key<<endl;
    return out;
}


#endif // QUEUE_H
