#include "oppr.h"
#include <cctype>
OpPr::OpPr(char newOp)
{
    // Set associativity of operator!
    switch (newOp)
    {
    case '^':
        assoc = true; // right
        break;
    default:
        assoc = false; // left for all other operators!
        break;
    }
}

OpPr::~OpPr()
{
    // delete nothing
}

bool OpPr::operator >(const OpPr &otherOp)
{
    switch (theOp)
    {
    case '^':
        return false; // nothing has greater precedence!
        break;
    case '*':
        return (otherOp.theOp == '^')? true : false;
        break;
    case '/':
        return (otherOp.theOp == '^')? true : false;
        break;
    case '+':
    case '-':
        return (otherOp.theOp == '*' || otherOp.theOp == '/' || otherOp.theOp) == '^'? true : false;
        break;
    default:
        // we have ()
        break;
    }
    return false;
}

bool OpPr::operator <(const OpPr &otherOp)
{
    return (otherOp > this); // since we defined it already
}

bool OpPr::operator ==(const OpPr &otherOp)
{
    switch (theOp)
    {
    case '^':
        return (otherOp.theOp != '^')? true : false;
        break;
    case '*':
    case '/':
        return (otherOp.theOp == '*' || otherOp.theOp == '/')? true : false;
        break;
    case '+':
    case '-':
        return (otherOp.theOp == '+' || otherOp.theOp == '-')? true : false;
        break;
    default:
        // we have ()?
        break;
    }
}

