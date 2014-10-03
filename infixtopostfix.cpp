#include "infixtopostfix.h"
#include <QDebug>

InfixtoPostfix::InfixtoPostfix( )
{
}

InfixtoPostfix::InfixtoPostfix( string inf )
{
    infix_input = inf;
}


void InfixtoPostfix::parseinfix()
{
    int openparen = 0, closeparen = 0;
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
            infix_copy.erase(0,pos_first_space + 1); // erase what we took into the temp string
            if (getNextTokenType(infix_copy) == 'N')
            {
                pos_first_space = infix_copy.find(" ");
                temp_token.append(" "); // space in mixed number
                temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
                infix_copy.erase(0,pos_first_space + 1); // erase what we took into the temp string
            }
            ss.clear();
            ss.str("");
            // we should have a whole mixed number now in temp_token
            MixedNum *tempNumber = new MixedNum; // Any way, even if only the first token is N we make a mixed number from it
            temp_token.append("\n"); // because we use getline
            ss << temp_token.c_str();
            ss >> *tempNumber;
            node mixedholder(tempNumber, 'N');
            output_queue.enqueue(mixedholder); // mixed number
            temp_token = "";
            //cout << output_queue << endl;
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
                openparen++;
                operator_stack.push(tempOp, 'P'); // put this operator/parenthesis onto the stack
                //cout << "( PAREN HERE, top of stack is? :" << operator_stack.top()->key.opPtr->theOp << endl;
                break;
            case ')':
            {
                closeparen++;
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
        case 'D':
        {
            temp_token.append(infix_copy.substr(0,pos_first_space).c_str()); // append the characters to the temp_token string
            infix_copy.erase(0,pos_first_space+1); // erase what we took into the temp string
            double *temp_double = new double;
            ss.str("");
            ss.clear();
            ss << temp_token.c_str();
            cout << "SS: " << ss.str().c_str() << endl;
            ss >> *temp_double;
            cout << "TEMP: "<< *temp_double << endl;
            node *doubleholder = new node(temp_double, 'D', NULL);
            cout << "NODE DOUBLE: " << *doubleholder->key.dPtr << endl;
            output_queue.enqueue(*doubleholder);
            cout << "DONE";
            temp_token = "";
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
        //        case 'N':
        //            output_queue.enqueue(operator_stack.pop()->key.mPtr, 'N');
        //            break;
        //        case 'D':
        //            output_queue.enqueue(operator_stack.pop()->key.dPtr, 'D');
        //            break;
        case 'O':
        case 'P':
        default:
            output_queue.enqueue(operator_stack.pop()->key.opPtr, 'O');
            break;
        }
    }
    if (openparen != closeparen)
        throw PAREN_MISMATCH;
}

void InfixtoPostfix::doCalculate()
{
    queue CopyQueue(output_queue); // copy constructor
    while (!CopyQueue.empty())
    {
        while (!CopyQueue.empty() && (CopyQueue.peek().data_type != 'O'))
        {
            node* deQueued = CopyQueue.dequeue();
            if (deQueued->data_type == 'D')
            {
                double data_holder = *deQueued->key.dPtr;
                MixedNum* temp_mixed = new MixedNum(data_holder);
                delete deQueued->key.dPtr;
                deQueued->key.vptr = temp_mixed; // associate mixed version of double
            }
            operand_stack.push(deQueued->key.mPtr, 'N');
        }
        if (!CopyQueue.empty())
        {
            switch(CopyQueue.peek().key.opPtr->theOp)
            {
            case '^':
                operand_stack.push(&(*operand_stack.pop()->key.mPtr ^ *operand_stack.pop()->key.mPtr), 'N');
                break;
            case '*': operand_stack.push(&(*operand_stack.pop()->key.mPtr * *operand_stack.pop()->key.mPtr), 'N');
                break;
            case '/': operand_stack.push(&(*operand_stack.pop()->key.mPtr / *operand_stack.pop()->key.mPtr), 'N');
                break;
            case '+': operand_stack.push(&(*operand_stack.pop()->key.mPtr + *operand_stack.pop()->key.mPtr), 'N');
                break;
            case '-': operand_stack.push(&(*operand_stack.pop()->key.mPtr - *operand_stack.pop()->key.mPtr), 'N');
                break;
            default: // do nothing with unknown operator
                break;
            }
            CopyQueue.dequeue(); // Dequeue the operator
        }
    }
    answer = *(operand_stack.pop()->key.mPtr); // The final answer
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
    if (int(current_token.find(".")) != -1)
        return 'D';
    if (int(current_token.find_first_of("0123456789")) != -1)
        return 'N';
    if (int(current_token.find_first_of("()")) != -1)
        return 'P';
    return 'O';
}

string InfixtoPostfix::getPostfixOutput()
{
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << output_queue;
    return ss.str();
}

void InfixtoPostfix::setInfixInput( string input )
{
    infix_input = input;
}

string InfixtoPostfix::getInfixInput()
{
    return infix_input;
}

string InfixtoPostfix::getAnswer()
{
    stringstream ss;
    ss << answer;
    return ss.str();
}

void InfixtoPostfix::resetcalc()
{
    operator_stack.clear();
    operand_stack.clear();
    output_queue.clear();
}

istream &operator>>(istream in, InfixtoPostfix &infix)
{
    string line;
    getline(in, line);
    infix.infix_input = line;
    return in;
}
