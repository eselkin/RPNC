#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "dataType.h"

using namespace std;

struct node
{

    DataType key;   // we will really make nodes of DataType type (unions).
    char data_type; // N, O, P; I think that's all the types I want nodes to be able to manage

    node *next;

    node(void *k = NULL, const char dt = 'N', node *n = NULL);
    ~node();
    node(const node &n);
    node& operator=(const node &n);

    void copy(const node &other);
    void nukem();
};

// We're really making this special to DataType for the output queue or Char for the operator stack
// let's you make the node with a pointer that will point to the void pointer type in DataType
// Only data_type will tell us how to retrieve this.

#endif // NODE_H
