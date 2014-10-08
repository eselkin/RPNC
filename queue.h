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
    const node &peekattail() const;
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
#endif // QUEUE_H
