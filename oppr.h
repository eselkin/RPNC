#ifndef OPPR_H
#define OPPR_H
// OPERATOR WITH PRECEDENCE
// This way we can have the operators compare themselves for precedence or associativity

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
