#include <iostream>
#include <stdlib.h>
#include <stack>

using namespace std;
//precedence check
int Precedence (char x){
    switch (x)
    {
        case '+' :
        case '-' : return 1;
        case '*' :
        case '/' : return 2;
        case '(' :
        case ')' : return 3;
        default : return -1;
    }
}

//check if the string is number//
bool isDigit(char x){
    return (x >= '0' && x <= '9');
}
//check if the string is Operator//
bool isOper(char x){
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' );
}
//mathematical expression
int calculate (int val1, int val2, char op) {
    if (op == '+'){
        return val1 + val2;
    }
    else if (op == '-') {
        return val1 - val2;
    }
    else if (op == '*') {
        return val1 * val2;
    }
    else if (op == '/') {
        return val1 / val2;
    }
    else {
        cout << "Wrong Operator Bro" << endl;
    }
}

int evaluate (string s){
    stack<int> vals;
    stack<char> ops;

    int val = 0;
    int pos = 0;

    while (pos < s.length()){
        char spot = s[pos];
        if (isDigit(spot)) {
            val = (val *10) + (int)(spot - '0');
        }
        else if (isOper(spot)) {
            if (spot == '('){
                ops.push (spot);
                val = 0;
            }
            else if (vals.empty()) {
                vals.push(val);
                ops.push(spot);
            }
            else if (spot == ')'){
                vals.push(val);
                while  (ops.top() != '(') {
                    spot = ops.pop();
                    val = vals.pop();
                    int prev = vals.pop();
                    val = calculate(prev, val, spot);
                    vals.push(val);
                }
                ops.pop();
                vals.pop();
            }
            else {
                char prev = ops.top();
                if (Precedence(spot) > Precedence(prev)) {
                    vals.push(val);
                    ops.push(spot);
                    val=0
                }
                else {
                    int prevval = vals.pop();
                    int prevop = ops.pop();
                    prevval = calculate(prevval, val, prevop);
                    vals.push(prevval);
                    ops.push(spot);
                    val=0;
                }
            }
        }
        pos ++;
    }
    while (!ops.empty()) {
        int prev = vals.pop();
        char spot = ops.pop();
        val = calculate(prev, val, spot);
    }
    return val;
}

int main () {
    string s = "(2+3)*3-(10/5)";
    evaluate (s);
    return 0;
}