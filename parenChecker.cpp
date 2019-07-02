
//<!*---------- MUST BE RUN WITH C++ 11 COMPILER ----------*!>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// INPUTS: string testString
// OUTPUTS: true/false
// FUNCTION: takes a string as input, and checks that string for balanced parentheses
//              if the string is BALANCED, then the function returns TRUE
//              if the string is NOT BALANCED, then the function returns FALSE
bool areParensBalanced (string testString)
{
    vector <char> parenVector;          // vector struct to serve as the stack for the parentheses (stack is the main key to this program)
    char tempChar = 'x';                // temp char to store top of stack when comparing closed to open parentheses

    // loop thru each position in the string to check for parentheses
    for (int i = 0; i < testString.length(); i++)
    {
        // if we find an open or closed parentheses
        if (testString[i] == '(' || testString[i] == '[' || testString[i] == '{')
        {
            // push parentheses onto the stack
            parenVector.push_back(testString[i]);
        }

        // if we find a close parentheses while the stack is empty, then we know it is wrong and not balanced
        if (parenVector.size() == 0 && (testString[i] == ')' ||  testString[i] == ']' || testString[i] == '}'))
        {
            // exit the loop
            return false;
        }

        // now if we find a closing parentheses, then the parentheses before it MUST be a matching open parentheses to be a valid expression
        if (testString[i] == ')')
        {
            // store the top of the stack
            tempChar = parenVector.back();

            // if we find a non matching parentheses at the top of the stack, then the expression is imbalanced
            if (tempChar == '[' || tempChar == '{')
            {
                return false;
            }

            // if we make it here, then the expression is valid so far, so we
            // pop the open parentheses off of the top of the stack
            parenVector.pop_back();
        }
        else if (testString[i] == ']')
        {
            // store the top of the stack
            tempChar = parenVector.back();

            // if we find a non matching parentheses at the top of the stack, then the expression is imbalanced
            if (tempChar == '(' || tempChar == '{')
            {
                return false;
            }

            // if we make it here, then the expression is valid so far, so we
            // pop the open parentheses off of the top of the stack
            parenVector.pop_back();
        }
        else if (testString[i] == '}')
        {
            // store the top of the stack
            tempChar = parenVector.back();

            // if we find a non matching parentheses at the top of the stack, then the expression is imbalanced
            if (tempChar == '(' || tempChar == '[')
            {
                return false;
            }

            // if we make it here, then the expression is valid so far, so we
            // pop the open parentheses off of the top of the stack
            parenVector.pop_back();
        }
    }

    // if our balanced flag is still true AND our stack is completely empty, then the expression is balanced
    if (parenVector.size() == 0)
    {
        return true;
    }
    // else our expression is imbalanced
    else
    {
        return false;
    }
}

int main()
{
    string equation1 = "(x/(y+z))";     // equation1 should pass
    string equation2 = "(x/(y+z)";      // equation2 should fail
    string equation3 = "([)]";          // equation3 should fail
    string testString = equation2;      // set the test string to one of the test cases

    // if areParensBalanced() returns true, then the expression is BALANCED
    if (areParensBalanced(testString))
    {
        cout << testString << " is BALANCED" << endl;
    }
    // else if areParensBalanced() returns false, then the expression is NOT BALANCED
    else
    {
        cout << testString << " is NOT BALANCED" << endl;
    }

    return 0;
}
