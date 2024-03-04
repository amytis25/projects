/* 
 * Eval.cpp
 *
 * Description: Evaluation of infix expressions using two Stacks.
 *
 * Author: Amytis Saghafi and Simon Schaufele
 * Date: feb 16 2024
 */

#include <iostream>
#include <cmath>
#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

using std::cout;
using std::endl;
using std::cin;

// Function prototypes
int calculate(int firstNum, int secondNum, TokenType operation);
void popAndCalc(Stack<Token>& numstack, Stack<Token>& opstack);
int precedence(TokenType op);

int main() {
    // Create a Scanner object to read input from standard input
    Scanner S(cin);
    Token t;

    // Create two stacks, one for numbers and one for operators
    Stack<Token> numstack;
    Stack<Token> opstack;

    // Get the first token from the input
    t = S.getnext();

    // Loop until the end of the input
    while (t.tt != eof) {
        // If the token is a number, push it onto the number stack
        if (t.tt == integer) {
            //cout << "pushing " << t << " into number stack" << endl;
            numstack.push(t);
        } 
        // If the token is a left parenthesis, push it onto the operator stack
        else if (t.tt == lptok) {
            //cout << "pushing " << t << " into operation stack" << endl;
            opstack.push(t);
        } 
        // If the token is a right parenthesis
        else if (t.tt == rptok) {
            // Pop operators and perform calculations until a left parenthesis is encountered
            while (opstack.peek().tt != lptok) {
                popAndCalc(numstack, opstack);
            }
            opstack.pop(); // Pop the left parenthesis
        } 
        // If the token is an operator
        else if (t.tt == pltok || t.tt == mitok || t.tt == asttok || t.tt == slashtok) {
            // Pop operators with higher or equal precedence and perform calculations
            while (!opstack.isEmpty() && precedence(opstack.peek().tt) >= precedence(t.tt)) {
                popAndCalc(numstack, opstack);
            }
            //cout << "pushing " << t << " into operation stack" << endl;
            opstack.push(t); // Push the current operator onto the operator stack
        }
        t = S.getnext(); // Get the next token
    }

    // Pop remaining operators and perform calculations
    while (!opstack.isEmpty()) {
        popAndCalc(numstack, opstack);
    }

    // Output the final result
    cout << numstack.peek().val << endl;

    return 0;
}

// Function to pop operators and perform calculations
void popAndCalc(Stack<Token>& numstack, Stack<Token>& opstack) {
    int firstNum = numstack.peek().val;
    numstack.pop();

    int secondNum = numstack.peek().val;
    numstack.pop();

    TokenType operation = opstack.peek().tt;
    opstack.pop();

    int result = calculate(secondNum, firstNum, operation);

    Token tokenResult;
    tokenResult.val = result;
    numstack.push(tokenResult);
}

// Function to perform arithmetic calculations
int calculate(int firstNum, int secondNum, TokenType operation) {
    if (operation == pltok) {
        return firstNum + secondNum;
    } else if (operation == mitok) {
        return firstNum - secondNum;
    } else if (operation == asttok) {
        return firstNum * secondNum;
    } else if (operation == slashtok) {
        return firstNum / secondNum;
    }
    return 0; // Handle other cases
}

// Function to determine operator precedence
int precedence(TokenType op) {
    if (op == asttok || op == slashtok) {
        return 2; // Multiplication and division have higher precedence
    } else if (op == pltok || op == mitok) {
        return 1; // Addition and subtraction have lower precedence
    } else {
        return 0; // Parentheses have the highest precedence
    }
}