#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "theStack.h"
#include "queue.h"
enum itopERROR { PAREN_MISMATCH };
class InfixtoPostfix
{
public:

    InfixtoPostfix();
    void parseinfix();

    friend
    char getNextTokenType(string infix_list);

    friend
    ostream& operator<<(ostream out, const InfixtoPostfix& outpost);

    friend
    istream& operator>>(istream in, InfixtoPostfix& ininfix);

private:
    theStack<OpPr> operator_stack;
    queue<DataType> output_queue;
    string infix_input;
};

#endif // INFIXTOPOSTFIX_H
