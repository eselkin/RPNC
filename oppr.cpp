#include "oppr.h"
#include <cctype>
OpPr::OpPr(char newOp)
{
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

