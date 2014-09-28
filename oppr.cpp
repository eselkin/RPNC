#include "oppr.h"

// OPERATOR WITH PRECEDENCE
// This way we can have the operators compare themselves for precedence or associativity

OpPr::OpPr(char newOp)
{
    theOp = newOp;
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
    case '*':
    case '/':
        return (otherOp.theOp == '^')? false : true;
        break;
    case '+':
    case '-':
        return (otherOp.theOp == '*' || otherOp.theOp == '/' || otherOp.theOp == '^')? false : true;
        break;
    default:
        return false;
        break;
    }
    return false;
}

bool OpPr::operator <(const OpPr &otherOp)
{
    switch (theOp)
    {
    case '*':
    case '/':
        return (otherOp.theOp == '^')? true : false;
        break;
    case '+':
    case '-':
        return (otherOp.theOp == '*' || otherOp.theOp == '/' || otherOp.theOp == '^')? true : false;
        break;
    default:
        return false;
        break;
    }
    return false;
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
    return false;
}



