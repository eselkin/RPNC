#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "theStack.h"
#include "queue.h"

using namespace std;

enum itopERROR { PAREN_MISMATCH };

class InfixtoPostfix
{
public:
    InfixtoPostfix();
    InfixtoPostfix(string inf);
    void parseinfix();
    void doCalculate();
    void readNum(string &infix_copy);


    char getNextTokenType(string infix_list);
    string getPostfixOutput();
    void setInfixInput(string input);
    string getInfixInput();
    string getAnswer();
    void resetcalc();
    //friend
    //ostream& operator<<(ostream out, const InfixtoPostfix& outpost);

    friend
    istream& operator>>(istream in, InfixtoPostfix& infix);

private:
    MixedNum answer;
    theStack operator_stack;
    queue output_queue;
    theStack operand_stack;
    string infix_input;
};
#endif // INFIXTOPOSTFIX_H
