#ifndef OPPR_H
#define OPPR_H
#include <cctype>
#include <iostream>

using namespace std;

class OpPr
{
public:
    OpPr(char newOp);
    ~OpPr();

    char theOp; // holds either (,),*,/,+,-, or =
    bool assoc; // Right associativity set by the constructor
    bool operator > ( const OpPr& otherOp );
    bool operator < ( const OpPr& otherOp );
    bool operator ==( const OpPr& otherOp );
    bool operator !=( const OpPr& otherOp );
};
#endif // OPPR_H
