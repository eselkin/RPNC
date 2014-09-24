#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "theStack.h"
#include "queue.h"

class InfixtoPostfix
{
public:

    InfixtoPostfix();
    void parseinfix();

    friend
    ostream& operator<<(ostream out, const InfixtoPostfix& outpost);

    friend
    istream& operator>>(istream in, InfixtoPostfix& ininfix);

private:
    theStack<char> operator_stack;
    queue<DataType> output_queue;
    string infix_input;
};

#endif // INFIXTOPOSTFIX_H
