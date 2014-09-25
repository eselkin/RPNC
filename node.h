#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "dataType.h"

using namespace std;

// We're really making this special to DataType for the output queue or Char for the operator stack
struct node
{
    DataType key;   // we will really make nodes of DataType type (unions).
    char data_type; // M, O; I think that's all the types I want nodes to be able to manage

    node *next;

    node(void *k = NULL, const char dt = 'I', node *n = NULL);
    ~node();
    node(const node &n);
    node& operator=(const node &n);
    void copy(const node &other);
    void nukem();
};


node::node( void *k, const char dt, node *n)
{
    key.vptr = k;
    data_type = dt;
    next = n;
}

node::~node()
{
    nukem();
}

node::node(const node &other)
{
    copy(other);
}


node& node::operator=(const node &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

void node::copy(const node &other)
{
    switch (other.data_type)
    {
    case 'O':
        key.opPtr = new OpPr(other.key.opPtr->theOp);
        data_type = 'O';
        break;
    case 'P':
        key.opPtr = new OpPr(other.key.opPtr->theOp);
        data_type = 'P';
        break;
    case 'N':
        key.mPtr = new MixedNum(*other.key.mPtr);
        break;
    default:
        //
        break;
    }
    next = NULL;
    data_type = other.data_type;
}

void node::nukem()
{
    switch (data_type)
    {
    case 'O':
        delete key.opPtr;
        break;
    case 'P':
        delete key.opPtr;
        break;
    case 'N':
        delete key.mPtr;
        break;
    default:
        //
        break;
    }
    next = NULL;
}


#endif // NODE_H
