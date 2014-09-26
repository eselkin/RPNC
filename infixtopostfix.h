#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include "queue.h"
#include "theStack.h"

using namespace std;

enum itopERROR { PAREN_MISMATCH };

class InfixtoPostfix
{
public:

    InfixtoPostfix(string inf);
    void parseinfix();
    void doCalculate();
    MixedNum answer;

    char getNextTokenType(string infix_list);

    friend
    ostream& operator<<(ostream out, const InfixtoPostfix& outpost);

    friend
    istream& operator>>(istream in, InfixtoPostfix& ininfix);

private:
    theStack<OpPr> operator_stack;
    queue output_queue;
    theStack<MixedNum> operand_stack;
    string infix_input;
};


InfixtoPostfix::InfixtoPostfix( string inf )
{
    infix_input = inf;
}

void InfixtoPostfix::parseinfix()
{
    string infix_copy = infix_input;
    string temp_token;
    stringstream ss;
    int i =0;
    int pos_first_space = infix_copy.find_first_of(" ");
    while (pos_first_space != -1)
    {
        switch(getNextTokenType(infix_copy))
        {
        case 'N':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space+1); // erase what we took into the temp string
            if (getNextTokenType(infix_copy) == 'N')
            {
                temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
                infix_copy.erase(0,pos_first_space+1); // erase what we took into the temp string
            }
            // we should have a whole mixed number now in temp_token
            MixedNum* tempNumber = new MixedNum; // Any way, even if only the first token is N we make a mixed number from it
            temp_token.append("\n"); // because we use getline
            ss.str(temp_token);
            ss >> *tempNumber;
            output_queue.enqueue(tempNumber, 'N'); // mixed number
            temp_token = "";
            // MIXED NUMBER IN FREESTORE GETS DELETED BY THE DESTRUCTOR OF THE QUE...
            break;
        }
        case 'O':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space+1); // erase what we took into the temp string
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
            temp_token = "";
            ss.str("");
            break;
        }
        case 'P':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space+1); // erase what we took into the temp string
            OpPr *tempOp = new OpPr(temp_token[0]);
            switch(temp_token[0])
            {
            case '(':
                operator_stack.push(tempOp, 'P'); // put this operator/parenthesis onto the stack
                //cout << "( PAREN HERE, top of stack is? :" << operator_stack.top()->key.opPtr->theOp << endl;
                break;
            case ')':
            {
                //cout << ") PAREN HERE:" <<operator_stack.top()->key.opPtr->theOp << endl;
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
            }
            default:
                // throw error?
                break;
            }
            temp_token = "";
            break;
        }
        case 'E':
        {
            infix_copy.erase(0,pos_first_space+1); // erase what we took into the temp string
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
        pos_first_space = infix_copy.find(" ");
    }

    while (!operator_stack.empty())
    {
        switch(operator_stack.top()->data_type)
        {
        case 'N':
            output_queue.enqueue(operator_stack.pop()->key.mPtr, 'N');
            break;
        case 'O':
        case 'P':
        default:
            output_queue.enqueue(operator_stack.pop()->key.opPtr, 'O');
            break;
        }
    }
    cout << "OUTPUT QUEUE: " << output_queue << endl;
}

void InfixtoPostfix::doCalculate()
{
    queue CopyQueue(output_queue); // copy constructor
    cout << "COPY QUEUE" <<endl <<  CopyQueue << endl;
    while (!CopyQueue.empty())
    {
        while (CopyQueue.peek().data_type == 'N')
            operand_stack.push(CopyQueue.dequeue().key.mPtr, 'N');

        cout << operand_stack << endl;

        if ( CopyQueue.peek().key.opPtr->theOp == '^' )
            operand_stack.push(&(*(operand_stack.pop()->key.mPtr)^ *(operand_stack.pop()->key.mPtr)), 'N');
        else
            if ( CopyQueue.peek().key.opPtr->theOp == '*' )
                operand_stack.push(&(*operand_stack.pop()->key.mPtr * *operand_stack.pop()->key.mPtr), 'N');
            else
                if ( CopyQueue.peek().key.opPtr->theOp == '/' )
                    operand_stack.push(&(*operand_stack.pop()->key.mPtr / *operand_stack.pop()->key.mPtr), 'N');
                else
                    if ( CopyQueue.peek().key.opPtr->theOp == '+' )
                        operand_stack.push(&(*operand_stack.pop()->key.mPtr + *operand_stack.pop()->key.mPtr), 'N');
                    else
                        if ( CopyQueue.peek().key.opPtr->theOp == '-' )
                            operand_stack.push(&(*operand_stack.pop()->key.mPtr - *operand_stack.pop()->key.mPtr), 'N');
        CopyQueue.dequeue(); // Dequeu the operator
    }
    answer = *(operand_stack.pop()->key.mPtr); // The final answer
    cout << answer << endl;
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
    if (current_token.find_first_of("0123456789") != -1)
        return 'N';
    if (current_token.find_first_of("()") != -1)
        return 'P';
    return 'O';
}

#endif // INFIXTOPOSTFIX_H
