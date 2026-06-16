#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

// Check if a word is one of our operators
bool isOperator(string w) {
    return w == "AND" || w == "OR" || w == "NOT" ||
           w == ">"  || w == "<"  || w == ">=" ||
           w == "<=" || w == "==" || w == "!=";
}

// Priority of an operator (a higher number is solved first)
int precedence(string op) {
    if (op == "NOT") return 4;
    if (op == ">" || op == "<" || op == ">=" ||
        op == "<=" || op == "==" || op == "!=") return 3;
    if (op == "AND") return 2;
    if (op == "OR")  return 1;
    return 0;
}

// STEP 1: split the rule into words (tokens)
vector<string> splitWords(string rule) {
    vector<string> words;
    stringstream ss(rule);
    string word;
    while (ss >> word) words.push_back(word);
    return words;
}

// STEP 2: convert infix to postfix (Shunting Yard algorithm)
vector<string> toPostfix(vector<string> words) {
    vector<string> output;   // the postfix result
    stack<string> ops;       // a stack to hold operators

    for (string w : words) {
        if (w == "(") {
            ops.push(w);
        } else if (w == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();          // remove the "("
        } else if (isOperator(w)) {
            while (!ops.empty() && ops.top() != "(" &&
                   precedence(ops.top()) >= precedence(w)) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(w);
        } else {
            output.push_back(w);                  // a number or sensor name
        }
    }
    while (!ops.empty()) {                         // empty the stack
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

// Get the value of a word: a sensor reading, or a plain number
double getValue(string w, map<string,double>& sensors) {
    if (sensors.count(w)) return sensors[w];      // it is a sensor name
    return stod(w);                               // it is a number
}

// STEP 3: solve the postfix using a stack -> true or false
bool evaluate(vector<string> postfix, map<string,double>& sensors) {
    stack<double> st;

    for (string w : postfix) {
        if (!isOperator(w)) {
            st.push(getValue(w, sensors));        // push the value
        } else if (w == "NOT") {
            double a = st.top(); st.pop();
            st.push(a == 0 ? 1 : 0);
        } else {
            double b = st.top(); st.pop();        // take two values
            double a = st.top(); st.pop();
            double r = 0;
            if (w == ">")  r = (a >  b);
            else if (w == "<")  r = (a <  b);
            else if (w == ">=") r = (a >= b);
            else if (w == "<=") r = (a <= b);
            else if (w == "==") r = (a == b);
            else if (w == "!=") r = (a != b);
            else if (w == "AND") r = (a && b);
            else if (w == "OR")  r = (a || b);
            st.push(r);                           // push the answer back
        }
    }
    return st.top() != 0;
}

// Run one rule and turn the device ON or OFF
void runRule(string device, string rule, map<string,double>& sensors) {
    vector<string> words   = splitWords(rule);
    vector<string> postfix = toPostfix(words);

    cout << "\n--- " << device << " ---\n";
    cout << "Rule (Infix): " << rule << "\n";
    cout << "Postfix     : ";
    for (string w : postfix) cout << w << " ";
    cout << "\n";

    bool on = evaluate(postfix, sensors);
    cout << "Result      : " << (on ? "TRUE" : "FALSE") << "\n";
    cout << device << " is turned " << (on ? "ON" : "OFF") << "\n";
}

int main() {
    // Current sensor readings (you can change these to test)
    map<string,double> sensors;
    sensors["temperature"] = 32;
    sensors["motion"]      = 1;
    sensors["light_level"] = 25;
    sensors["time"]        = 1900;

    cout << "===== SMART HOME AUTOMATION =====\n";
    cout << "temperature = " << sensors["temperature"] << "\n";
    cout << "motion      = " << sensors["motion"] << "\n";
    cout << "light_level = " << sensors["light_level"] << "\n";
    cout << "time        = " << sensors["time"] << "\n";

    // The rules set by the user
    runRule("FAN",   "temperature > 30 AND motion == 1", sensors);
    runRule("LIGHT", "light_level < 40 OR time > 1800", sensors);

    return 0;
}
