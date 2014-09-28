#include "node.h"

node::node(void *k, const char dt, node *n)
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
