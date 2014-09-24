#ifndef OPPR_H
#define OPPR_H
// OPERATOR WITH PRECEDENCE
// This way we can have the operators compare themselves for precedence or associativity

using namespace std;

class OpPr
{
public:
    OpPr(char newOp);
    char theOp; // holds either (,),*,/,+,-, or =
    bool operator > ( const OpPr& otherOp );
    bool operator < ( const OpPr& otherOp );
    bool operator ==( const OpPr& otherOp );
    bool operator !=( const OpPr& otherOp );
};

#endif // OPPR_H
