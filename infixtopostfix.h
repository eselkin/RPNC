#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "theStack.h"
#include "queue.h"

class InfixtoPostfix
{
public:
    InfixtoPostfix();

private:
    theStack<char> operator_stack;
    queue<DataType> output_queue;
};

#endif // INFIXTOPOSTFIX_H
