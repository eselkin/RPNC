#include "infixtopostfix.h"

InfixtoPostfix::InfixtoPostfix()
{
}

void InfixtoPostfix::parseinfix()
{
    string infix_copy = infix_input;
    string temp_token;
    stringstream ss;
    int pos_first_space = infix_copy.find_first_of(" ");
    while (pos_first_space != -1)
    {
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
            output_queue.enqueue(&tempNumber, 'N'); // mixed number
            temp_token.clear();
            ss.str("");
            break;
        }
        case 'O':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space); // erase what we took into the temp string
            OpPr* tempOp = new OpPr(temp_token[0]); // create a tempOp
            while (( !operator_stack.empty() )
                   && (operator_stack.top()->data_type == 'O')
                   && ((!tempOp->assoc && (*tempOp < *operator_stack.top()->key.opPtr || *tempOp == *operator_stack.top()->key.opPtr))
                       || (*tempOp < *operator_stack.top()->key.opPtr)))
            {
                // While NOT empty
                // pop off the operators on the stack until we meet one with lower precedence and this is left associative
                // or pop the other off it is higher precedence no matter the associativity
                node* otherOp = operator_stack.pop();
                output_queue.enqueue(otherOp->key.opPtr, 'O'); // put the stack's operator onto the queue;
            }

            operator_stack.push(tempOp, 'O'); // put this operator onto the stack
            temp_token.clear();
            ss.str("");
            break;
        }
        case 'P':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space); // erase what we took into the temp string
            OpPr *tempOp = new OpPr(temp_token[0]);
            switch(temp_token[0])
            {
            case '(':
                operator_stack.push(tempOp, 'P'); // put this operator/parenthesis onto the stack
                break;
            case ')':
                while (( !operator_stack.empty() && operator_stack.top()->data_type != 'P')&&(operator_stack.top()->key.opPtr->theOp != '('))
                {
                    // run until we come to a (
                    node* otherOp = operator_stack.pop();
                    output_queue.enqueue(otherOp->key.opPtr, 'O'); // put the stack's operator onto the queue;
                }
                if (!operator_stack.empty() && (operator_stack.top()->key.opPtr->theOp == '('))
                {
                    operator_stack.pop(); // but don't save
                }
                else
                {
                    throw PAREN_MISMATCH;
                }
                break;
            default:
                // throw error?
                break;
            }
            break;
        }
        case 'E':
        {
            // we are empty
            break;
        }
        default:
        {
            // Not sure if E and default are the same... But I think so
            break;
        }
        }
        // I like how this switch spells out NOPE
        pos_first_space = infix_copy.find_first_of(" ");
    }
}

char InfixtoPostfix::getNextTokenType(string infix_list)
{
    // Get substring to first space
    // Check if substring has number
    // If has number return N
    // If substr has a parenthesis return P
    // Check if substring has ",/+-*"
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
    if (current_token.find_first_of("()") != -1)
        return 'P';
    return 'O';
}

