#include "infixtopostfix.h"

InfixtoPostfix::InfixtoPostfix()
{
}

void InfixtoPostfix::parseinfix()
{
    // string input will have tokens separated by operators or spaces, but spaces between
    // ( ( 3 + 2 5/2 ) * 1.25 + 1 1/2 ) * 5 3/4
    // (( will give error?
    // 3+ will give error?
    // )* will give error?
    // 1/2) will give error?
    //
    char last_token_type = ' ';
    string infix_copy = infix_input;
    while (infix_copy.find_first_of(" "))
    {
        // (, ( 3 ...
        // (, 3 + 2 5/2 )
        // 3, + 2 5/2 )
        // +, 2 5/2 )
        // 2, 5/2 ) // so if last_token_type is Numeric and this token type contains / and numbers but no space
        // then we will combine (means pop the last number back off the output stack and combine it as a mixed number)
        // 2 5/2, ) * // and push the mixed number back on the output stack



    }
}
