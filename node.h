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

    node(const Datatype *k = NULL, const char dt = 'I', node *n = NULL);
    ~node();
    node(const node &n);
    node& operator=(const node &n);
    void copy(const node &other);
};


node::node(const Datatype *k, const char dt, node *n)
{
    key = k ? new Datatype(*k) : NULL;
    data_type = dt;
    next = n;
}

node::~node()
{
    delete key;
    next = NULL;
}

node::node(const node &other)
{
    copy(other);
}


node& node::operator=(const node &other)
{
    if(this != &other)
    {
        delete key;
        next = NULL;
        copy(other);
    }
    return *this;
}

void node::copy(const node &other)
{
    next = NULL;
    key = new Datatype(*other.key);
    data_type = other.data_type;
}


#endif // NODE_H
