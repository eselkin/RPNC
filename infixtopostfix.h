#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "queue.h"
#include "theStack.h"
enum itopERROR { PAREN_MISMATCH };
class InfixtoPostfix
{
public:

    InfixtoPostfix();
    void parseinfix();

    char getNextTokenType(string infix_list);

    friend
    ostream& operator<<(ostream out, const InfixtoPostfix& outpost);

    friend
    istream& operator>>(istream in, InfixtoPostfix& ininfix);

private:
    theStack<OpPr> operator_stack;
    queue output_queue;
    string infix_input;
};

#endif // INFIXTOPOSTFIX_H
