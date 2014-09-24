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
    string temp_token;
    stringstream ss;
    int pos_first_space = infix_copy.find_first_of(" ");
    while (pos_first_space != -1)
    {
        // (, ( 3 ...
        // (, 3 + 2 5/2 )
        // 3, + 2 5/2 )
        // +, 2 5/2 )
        // 2, 5/2 ) // so if last_token_type is Numeric and this token type contains / and numbers but no space
        // then we will combine (means pop the last number back off the output stack and combine it as a mixed number)
        // 2 5/2, ) * // and push the mixed number back on the output stack
        // // 3 2/3 * ( 2 + 2 2/3 )
        // we have to dequeue two tokens at a time

        switch(getNextTokenType(infix_copy))
        {
        case 'N':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space); // erase what we took into the temp string
            if (getNextTokenType(infix_copy) == 'N')
            {
                temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
                infix_copy.erase(0,pos_first_space); // erase what we took into the temp string
            }
            // we should have a whole mixed number now in temp_token
            MixedNum tempNumber; // Any way, even if only the first token is N we make a mixed number from it
            ss << temp_token;
            ss >> tempNumber;
            output_queue.enqueue(tempNumber, 'N'); // mixed number
            temp_token.clear();
            ss.str("");
            break;
        }
        case 'O':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space); // erase what we took into the temp string
            switch (temp_token[0])
            {
            case '*':
                break;

            }

            // switch will determine what to do with this operator as well as check the operator stack

            break;

        }
        case 'E':
        default:
        {

            break;
        }
        }
    }
}

char getNextTokenType(string infix_list)
{
    // Get substring to first space
    // Check if substring has number
    // If has number return N
    // Check if substring has "(),/+-*"
    // if has operator return O
    string current_token;
    int pos = infix_list.find(" ");
    if (pos != -1)
        current_token = infix_list.substr(0,pos);
    else
        current_token = infix_list.substr(0,string::npos);
    if (current_token == " " || current_token == "")
        return 'E'; // end of line
    if (current_token.find("0123456789") != -1)
        return 'N';
    return 'O';
}

