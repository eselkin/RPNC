#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "node.h"
#include "theStack.h"
#include "queue.h"

using namespace std;

enum itopERROR { PAREN_MISMATCH };

class InfixtoPostfix
{
public:

    InfixtoPostfix();
    void parseinfix();

    char getNextTokenType(string infix_list);

    friend
    ostream& operator<<(ostream& out, const InfixtoPostfix& outpost);

    friend
    istream& operator>>(istream& in, InfixtoPostfix& ininfix);

private:
    queue output_queue;
    theStack<OpPr> operator_stack;
    string infix_input;
};

#endif // INFIXTOPOSTFIX_H
