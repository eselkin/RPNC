#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "theStack.h"
#include "queue.h"

class InfixtoPostfix
{
public:
    InfixtoPostfix();
    void parseinfix();

private:
    theStack<char> operator_stack;
    queue<DataType> output_queue;
    string infix_input;
};

#endif // INFIXTOPOSTFIX_H
